
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

int main() {
    ServerSocketChannel channel(9898);
    Selector aSelector(&channel);
    return 0;
}
