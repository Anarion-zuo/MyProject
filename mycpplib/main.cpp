
#include <iostream>
#include <concurrent/pool/ThreadPool.h>
#include <containers/Map/HashMap.hpp>
#include <io/Channel/Network/ServerSocketChannel.h>
#include <wrappers/Number.hpp>
#include <io/Channel/File/FileChannel.h>
#include <containers/Set/TreeSet.hpp>
#include <containers/Map/TreeMap.hpp>

using namespace std;

int main() {
    auto map = new TreeMap<Int, Int>();
    map->put(2, 4);
    return 0;
}
