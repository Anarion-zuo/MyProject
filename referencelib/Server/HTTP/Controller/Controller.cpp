//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "Controller.h"
#include "../../../exceptions/Server/Http/RequestTypeUnsupportedException.h"

void Controller::run() {
    int type = request->getType().getNum();
    Pointer<SString> retStr;
    switch (type) {
        case __http_get_type:
            retStr = onGet();
            break;
        case __http_post_type:
            retStr = onPost();
            break;
        case __http_put_type:
            retStr = onPut();
            break;
        case __http_del_type:
            retStr = onDelete();
            break;
        default:
            throw RequestTypeUnsupportedException();
    }

}
