#include <iostream>
#include "base/Object.h"
#include "base/Pointer.hpp"
#include "container/List/Vector.hpp"
#include "container/Set/HashSet.hpp"
#include "base/Number.hpp"
#include "concurrent/base/Thread.h"
#include "container/Queue/BlockQueue.hpp"
#include <iostream>
#include "container/SString.h"
#include "io/Buffer/Buffer.h"
#include "io/Channel/Network/tcp/TcpServerSocketChannel.h"
#include "Server/Selector/EpollSelector.h"
#include "Server/HTTP/Request/Request.h"
#include "Server/HTTP/Controller/Controller.h"

using namespace std;

class printBuffer : public Thread {
protected:
    Pointer<EpollSelector> selector;
public:
    printBuffer(Pointer<EpollSelector> selector) : selector(selector) {}
    void run() override {
        Controller::init(selector);
    }
};

int main() {
    Pointer<Buffer> buffer = Buffer::allocate(1024);
    Pointer<TcpServerSocketChannel> channel = new TcpServerSocketChannel(23335);
    Pointer<EpollSelector> selector = new EpollSelector(channel);
    channel->listen();
    printBuffer th(selector);
    th.start();
    selector->run();
    return 0;
}
