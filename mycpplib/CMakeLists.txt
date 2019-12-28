cmake_minimum_required(VERSION 3.15)
project(mycpplib)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(allocator)
include_directories(base-classes)
include_directories(concurrent)
include_directories(containers)
include_directories(exceptions)
include_directories(exceptions/Allocator)
include_directories(exceptions/containers)
include_directories(featurers)
include_directories(functors)
include_directories(io)

add_executable(mycpplib
        allocator/allocator.cpp
        allocator/Allocator.h
        allocator/Allocator.hpp
        wrappers/Double.cpp
        wrappers/Double.h
        wrappers/Integer.cpp
        wrappers/Integer.h
        base-classes/Object.cpp
        base-classes/Object.h
        containers/List/Deque.hpp
        containers/Map/HashMap.hpp
        containers/Set/HashSet.hpp
        containers/List/DoublyList.hpp
        containers/Map/Map.hpp
        containers/Base/RbTree_old.hpp
        containers/List/SinglyList.hpp
        containers/List/SString.cpp
        containers/List/SString.h
        containers/Base/Tree.hpp
        containers/List/Vector.hpp
        exceptions/Allocator/MemoryAllocationException.h
        exceptions/containers/EmptyContainerException.h
        exceptions/containers/IndexOutOfRangeException.h
        exceptions/MyException.hpp
        featurers/UnCopiable.h
        functors/binary_functor.hpp
        functors/functor.hpp
        functors/non_functor.hpp
        functors/unary_functor.h
        erronos.h
        main.cpp
        functors/ForEach.hpp containers/ContainerInterface.hpp containers/List/List.hpp containers/Set/Set.hpp wrappers/Pointer/Pointer.hpp numerical/CompGraph.cpp numerical/CompGraph.h numerical/variable/SingleParamVariable.cpp numerical/variable/SingleParamVariable.h featurers/UnMovable.h featurers/UseAllocator.h exceptions/containers/InvalidOperationException.h containers/Queue/Queue.hpp containers/Queue/ListQueue.hpp containers/Stack/Stack.hpp containers/Stack/ListStack.hpp concurrent/Callable/Callable.h concurrent/Callable/Thread.cpp concurrent/Callable/Thread.h concurrent/Mutex/Mutex.cpp concurrent/Mutex/Mutex.h concurrent/Mutex/AutoMutex.cpp concurrent/Mutex/AutoMutex.h concurrent/CondVar/CondVar.cpp concurrent/CondVar/CondVar.h concurrent/Semaphore/Semaphore.cpp concurrent/Semaphore/Semaphore.h concurrent/pool/ThreadPool.cpp concurrent/pool/ThreadPool.h containers/Queue/BlockQueue.hpp containers/Queue/PriorityQueue.hpp concurrent/Callable/Binded.hpp containers/Tuple.hpp concurrent/Callable/Callable.cpp io/Buffer/Pipe.cpp io/Buffer/Pipe.h io/Buffer/Buffer.cpp io/Buffer/Buffer.h io/Channel/Channel.cpp io/Channel/Channel.h io/Channel/File/FileChannel.cpp io/Channel/File/FileChannel.h exceptions/io/File/ReadFailedException.h exceptions/io/File/WriteFailedException.h io/Selector/Selector.h io/Channel/Network/SocketChannel.h io/Channel/Network/SocketChannel.cpp io/Channel/Network/ServerSocketChannel.cpp io/Channel/Network/ServerSocketChannel.h exceptions/io/SystemException.h exceptions/io/Network/ListenException.h exceptions/io/Network/ConnectException.h exceptions/io/Network/SocketCreateException.h exceptions/io/Network/ReceiveException.h exceptions/io/Network/SendException.h exceptions/io/Network/BindException.h exceptions/io/Network/SocketCloseException.h wrappers/Number.hpp featurers/Hashable.h exceptions/io/Network/EpollCreateException.h exceptions/io/Network/EpollConfigException.h exceptions/io/Network/EpollWaitException.h exceptions/io/Network/AcceptException.h exceptions/io/File/FileStatException.h featurers/Clonable.h io/Channel/File/FileStatus.cpp io/Channel/File/FileStatus.h featurers/UnConstructable.h exceptions/io/File/OpenFileException.h exceptions/io/File/FileRemoveException.h exceptions/io/File/CloseFileException.h exceptions/io/File/FileRenameException.h containers/Base/RedBlackTree.hpp containers/Set/TreeSet.hpp wrappers/Pointer/Reference.hpp containers/Map/TreeMap.hpp mylib.h Server/Http/Request.cpp Server/Http/Request.h Server/Http/Response.cpp Server/Http/Response.h io/Selector/Selector.cpp exceptions/io/Network/EpollException.h exceptions/io/fd/FcntlException.h Server/Http/RequestType/RequestType.cpp Server/Http/RequestType/RequestType.h exceptions/Server/Http/HttpFormatException.h)

target_link_libraries(mycpplib pthread)