//
// Created by anarion on 2019/10/23.
//

#include <fcntl.h>
#include <zconf.h>

#include <utility>
#include <iostream>
#include "PageApp.h"

using std::cout, std::endl;

void PageApp::onGet(Request &request, Response &response) {
    const std::string &dir = request.getDir();
    std::stringstream buffer;
    std::string targetDir = pagesDir + pageFile;
    int fd = ::open(targetDir.c_str(), O_RDONLY);
    if (fd < 0) {
        // TODO assets not found
    }
    int size = 4096;
    int cofd = compressFile(fd, targetDir);
    response.ffd = cofd;
    response.addHeaderEncoding("deflate");
    response.addHeaderContentType("text/html; charset=UTF-8");
    response.addHeaderDate();
}
