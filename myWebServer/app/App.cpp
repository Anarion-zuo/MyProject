//
// Created by anarion on 2019/10/22.
//

#include <regex>
#include <fcntl.h>
#include "App.h"
#include "../listener/Listener.h"
#include "../cookie/Cookie.h"
#include "../session/Session.h"
#include "AppNotImplemented.h"
#include "RedirectApp.h"
#include <iostream>
#include <zlib.h>
#include <sys/stat.h>
using std::cout, std::endl;

std::vector<App*> App::apps;
const std::string
App::WebInfoDir = "WebInfo",
App::appsDir = App::WebInfoDir + "/apps",
App::assetsDir = App::WebInfoDir + "/assets",
App::pagesDir = App::WebInfoDir + "/pages";

App &App::matchApp(const std::string& input_str) {
    for (auto app : apps) {
        if (app->matchMe(input_str)) {
            return *app;
        }
    }
    // TODO no match app
    cout << "[app] No matching app, 501 sent" << endl;
    return *AppNotImplemented::getInstance();
}

void App::runThis(Request &&request) {
    cout << "[app] Entered app: " << typeid(*this).name() << endl;
    std::string &requestType = request.type, &dir = request.dir;
    Cookie cookie(request);
//    Session session(cookie);
    Response response(200, request.cfd);
    if (requestType == "GET") {
        cout << "[" << typeid(*this).name() << "] GET handling..." << endl;
        onGet(request, response);
    } else if (requestType == "POST") {
        cout << "[" << typeid(*this).name() << "] POST handling..." << endl;
        onPost(request, response);
    }
    cout << "[" << typeid(*this).name() << "] Send response" << endl;
    Response::pushResponse(std::move(response));
}

bool App::matchMe(const std::string &str) {
    for (auto &item : patterns) {
        if (std::regex_match(str, std::regex(item))) {
            return true;
        }
    }
    return false;
}

void App::redirect(std::string &&location, Response &response) {
    response.addHeader("Location", std::forward<std::string>(location));
    response.setCode(302);
}

static void doCompress(int fd, int &cofd) {
    long file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    size_t bound_size = compressBound(file_size);
    unsigned char compress_buffer[bound_size], target_buffer[file_size];
    long ret;
    ret = ::read(fd, target_buffer, file_size);
    if (ret != file_size) {
        perror("[app] read file error");
        return;
    }
    // do compress
    ret = compress(compress_buffer, &bound_size, target_buffer, file_size);
    if (ret != Z_OK) {
        cout << "[app] Zlib compress error" << endl;
        return;
    }
    ret = ::write(cofd, compress_buffer, bound_size);
    if (ret != bound_size) {
        perror("[app] write file error");
        return;
    }
}

int App::compressFile(int fd, const std::string &target_dir) {
    // check the last altered date
    std::string compressed_dir = target_dir + ".zip";
    int cofd = ::open(compressed_dir.c_str(), O_RDWR);
    if (cofd == -1) {
        perror("[app] file open error");
        // file not created
        cofd = ::open(compressed_dir.c_str(), O_CREAT | O_TRUNC | O_RDWR, 0777);
        doCompress(fd, cofd);
        return cofd;
    }
    int ret;
    struct stat buf;
    ret = fstat(fd, &buf);
    if (ret) {
        perror("[app] stat function error");
        return -1;
    }
    long target_time = buf.st_mtim.tv_sec;
    ret = fstat(cofd, &buf);
    if (ret) {
        perror("[app] stat function error");
        return -1;
    }
    long compress_time = buf.st_mtim.tv_sec;
    if (target_time > compress_time) {
        doCompress(fd, cofd);
    }
    return cofd;
}
