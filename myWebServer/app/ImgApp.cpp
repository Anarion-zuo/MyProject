//
// Created by anarion on 2019/10/26.
//

#include <fcntl.h>
#include <zconf.h>
#include <iostream>
#include "ImgApp.h"

using std::cout, std::endl;

// set assets to be relative root to /assets
void ImgApp::onGet(Request &request, Response &response) {
    const std::string &dir = request.getDir();
    std::stringstream buffer;
    std::string targetDir = WebInfoDir + dir;
    int fd = ::open(targetDir.c_str(), O_RDONLY);
    if (fd < 0) {
        // TODO assets not found
    }
    fd = compressFile(fd, targetDir);
    response.addHeaderEncoding("deflate");
    response.ffd = fd;
    // make response
    // type
    size_t index = dir.rfind('.') + 1;
    std::string typeStr = dir.substr(index);
    if (typeStr == "jpg") {
        typeStr = "jpeg";
    }
    std::string contentType = "image/" + typeStr;
    response.addHeaderContentType(std::move(contentType));
    response.addHeaderAcceptRanges();
}
