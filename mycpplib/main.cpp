
#include <iostream>
#include <concurrent/pool/ThreadPool.h>
#include <containers/Map/HashMap.hpp>
#include <io/Channel/Network/ServerSocketChannel.h>
#include <wrappers/Number.hpp>
#include <io/Channel/File/FileChannel.h>
#include <containers/Set/TreeSet.hpp>
#include <containers/Map/TreeMap.hpp>
#include <io/Selector/Selector.h>

using namespace std;

class printRe : public Thread {
    Selector &selector;
public:
    printRe(Selector &selector) : selector(selector) {}

    void run() override {
        while (true) {
            Selector::packet p = selector.pollPacket();
            p.buffer.print();
        }
    }
};

int main() {
    ServerSocketChannel channel(23333);
    Selector selector(&channel);
    channel.listen();
    printRe f(selector);
    f.start();
    selector.run();
    return 0;
}
