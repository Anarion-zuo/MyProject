
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

void parseParams(HashMap<SString, SString> &paramsMap, char *str) {
    SString key, val;
    while (true) {
        char *p = strchr(str, '=');
        if (p == nullptr) {
            return;
        }
        *p = 0;
        key = str;
        str = p + 1;
        p = strchr(str, '&');
        *p = 0;
        val = str;
        paramsMap.put(std::move(key), std::move(val));
        str = p + 1;
    }
}

int main() {
    HashMap<SString, SString> map;
    parseParams(map, "haha=gir&ckaj=iif&vla=f");
    return 0;
}
