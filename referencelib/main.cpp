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
#include "io/Channel/Network/ServerSocketChannel.h"
#include "Server/Selector/EpollSelector.h"
#include "Server/HTTP/Request/Request.h"

using namespace std;

class printBuffer : public Thread {
protected:
    Pointer<EpollSelector> selector;
public:
    printBuffer(Pointer<EpollSelector> selector) : selector(selector) {}
    void run() override {
        while (true) {
            auto packet = selector->pollPacket();
            Pointer<Request> request = Request::readFromBuffer(packet->buffer);
            request->print();
            request.release();
        }
    }
};

int main() {
    Pointer<Buffer> buffer = Buffer::allocate(1024);
    Pointer<ServerSocketChannel> channel = new ServerSocketChannel(9988);
    Pointer<EpollSelector> selector = new EpollSelector(channel);
    channel->listen();
    printBuffer th(selector);
    th.start();
    selector->run();
    return 0;
}
