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

using namespace std;


int main() {
    Pointer<Object> o = new Object;
    Vector<Object> v;
    v.add(new Int(3));
    v.add(new Int(3));
    v.add(new Int(3));
    v.add(new Int(3));
    v.add(new Int(3));
    v.add(new Int(3));
    v.add(new Int(3));

    cout << v.toString()->cstr() << endl;
    return 0;
}
