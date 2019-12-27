#include <iostream>
#include <regex>
#include <fcntl.h>
#include "listener/Listener.h"
using namespace std;

const string &getstr() {
    return std::move(string());
}

int main() {
    Listener::startListening(22222, 1024, 1024);
    return 0;
}