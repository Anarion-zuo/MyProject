//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include <cstring>
#include "RequestType.h"


RequestType RequestType::makeType(const char *word) {
    int type;
    if (!strcmp(word, "GET")) {
        type = __http_get_type;
    } else if (!strcmp(word, "POST")) {
        type = __http_post_type;
    } else if (!strcmp(word, "PUT")) {
        type = __http_put_type;
    } else if (!strcmp(word, "DELETE")) {
        type = __http_del_type;
    } else {
        type = __http_others;
    }
    RequestType ret {};
    ret.type = type;
    return ret;
}

bool RequestType::isGet() {
    return type == __http_get_type;
}

bool RequestType::isPost() {
    return type == __http_post_type;
}

bool RequestType::isPut() {
    return type == __http_put_type;
}

bool RequestType::isDel() {
    return type == __http_del_type;
}

int RequestType::getNum() const {
    return type;
}
