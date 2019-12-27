//
// Created by anarion on 2019/10/22.
//

#include "Listener.h"
#include "../app/App.h"
#include "../app/PageApp.h"
#include "../app/ImgApp.h"
#include "../app/TextApp.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <cstring>
#include <sys/epoll.h>
#include <arpa/inet.h>
using std::cout, std::endl;

Listener *Listener::instance = nullptr;
boost::threadpool::pool Listener::threadPool(10);


Listener::Listener(int port_num, int back_log, int max_conn) : portNum(port_num), backlog(back_log), maxConnNum(max_conn) {
    chdir("..");  // change working dir outside of cmake-build-debug
    cout << "[tcp] Starting at port " << portNum << " max connection number " << maxConnNum << " backlog " << backlog << endl;
    // initialize listen fd
    lfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (lfd == 1) {
//        // TODO socket init failed
//    }
    cout << "[tcp] Listening socket created " << lfd << endl;
    // set to nonblock state
    int flag = fcntl(lfd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(lfd, F_SETFL, flag);
    // bind
    sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htons(INADDR_ANY);
    server.sin_port = htons(portNum);  // set port number
    int ret = bind(lfd, (struct sockaddr *) &server, sizeof(server));
    if (ret == -1) {
        // TODO bind failed
    }
    cout << "[tcp] Bounded to port " << portNum << endl;
    // listen
    ret = ::listen(lfd, backlog);  // set max size of pending queue
    if (ret == -1) {
        // TODO listen failed
    }
    cout << "[tcp] Start listening..." << endl;
    // init epoll
    epfd = epoll_create(maxConnNum);  // max number of connection

    // start rolling
    threadPool.schedule(dispatch);
    threadPool.schedule(sendBack);
    threadPool.schedule([this] {
        int ret, flag;

        sockaddr_in client_addr;
        socklen_t cli_len = sizeof(client_addr);
        epoll_event event, all[getInstance().maxConnNum];
        event.events = EPOLLIN;
        event.data.fd = lfd;
        event.events |= EPOLLET;    // edge trigger
        ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &event);  // attach listen socket to the tree
        if (ret == -1) {
            perror("epoll error");
            // epoll error
        }
        cout << "[tcp] Epoll roll started..." << endl;
        while (true) {
            int size = epoll_wait(epfd, all, maxConnNum, -1);
            if (size < 0 && errno == EINTR) {
                perror("[tcp] epoll wait");
                continue;
            }
            for (int i = 0; i < size; ++i) {
                if (all[i].data.fd == lfd) {
                    // incoming new connection
                    int cfd = accept(lfd, (struct sockaddr *)&client_addr, &cli_len);
                    if (cfd == -1) {
                        // TODO accept error
                    }
                    cout << "[tcp] Incoming new connection from IP " << inet_ntoa(client_addr.sin_addr) << " , created socket " << cfd << endl;
                    // nonblock
                    flag = fcntl(cfd, F_GETFL);
                    flag |= O_NONBLOCK;
                    fcntl(cfd, F_SETFL, flag);
                    event.data.fd = cfd;
                    event.events = EPOLLIN | EPOLLET;    // read event

                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &event);  // add to the tree
                    if (ret == -1) {
                        // TODO epoll error
                    }
                } else {  // existing connection giving new data
                    if (!(all[i].events & EPOLLIN)) {  // no data to be read
                        continue;
                    }
                    cout << "[tcp] Manage incoming data..." << endl;
                    // normal handling
                    threadPool.schedule(boost::bind(readPipe, all[i].data.fd));
                }
            }
        }
    });


}

void Listener::readPipe(int fd) {
    int size = 4096, res = 0;
    std::stringstream buffer;
    char *b = new char[size];
    int len;
    cout << "[request] Read incoming data..." << endl;
    len = recv(fd, b, size, 0);
    if (len <= 0) {
        // delete node
        cout << "[tcp] Connection closed at " << fd << endl;
        epoll_ctl(getInstance().epfd, EPOLL_CTL_DEL, fd, nullptr);
        close(fd);
        return;
    }
    buffer << b;
    res += len;
    while ((len = recv(fd, b, size, 0)) > 0) {
        buffer << b;
        res += len;
    }
    delete[] b;
    cout << "[request] Read done." << endl;

    Request::pushRequest(Request(std::move(buffer), fd));
}

Listener::~Listener() {
    threadPool.wait();
}



const Listener &Listener::getInstance() {
    return *instance;
}

void Listener::dispatch() {
    Request request(Request::popRequest());
    while (true) {
        std::string &dir = request.dir;
        App &app = App::matchApp(dir);
        threadPool.schedule([&] {
            app.runThis(std::move(request));
        });
        request = Request::popRequest();
    }
}

void Listener::sendBack() {
    while (true) {
        Response response = Response::popResponse();
        Response::sendResponse(response);
    }
}

void Listener::startListening(int port_num, int back_log, int max_conn) {
    // default apps
    App::registerApp<App>({"/root.*"});
    App::registerApp<PageApp>({"/hello"});
    App::registerApp<ImgApp>({"/assets.*"});
    App::registerApp<TextApp>({"/pages.*"});
    registerApps();
    instance = new Listener(port_num, back_log, max_conn);
    threadPool.wait();
}

void Listener::registerApps() {

}
