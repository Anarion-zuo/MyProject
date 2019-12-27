cmake_minimum_required(VERSION 3.15)
project(myWebServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(myWebServer main.cpp listener/Listener.cpp listener/Listener.h request/Request.cpp request/Request.h app/App.cpp app/App.h response/Response.cpp response/Response.h status/Status.cpp status/Status.h app/PageApp.cpp app/PageApp.h session/Session.cpp session/Session.h cookie/Cookie.cpp cookie/Cookie.h app/JsonApp.cpp app/JsonApp.h app/ImgApp.cpp app/ImgApp.h app/AppNotImplemented.cpp app/AppNotImplemented.h app/TextApp.cpp app/TextApp.h app/RedirectApp.cpp app/RedirectApp.h)

target_link_libraries(myWebServer pthread z boost_system boost_thread)