//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_REQUESTTYPE_H
#define REFERENCELIB_REQUESTTYPE_H

enum __request_type {
    __http_get_type,
    __http_post_type,
    __http_put_type,
    __http_del_type,
    __http_others,
};

class RequestType {
protected:
    int type;
public:
    static RequestType makeType(const char *word);

    bool isGet();
    bool isPost();
    bool isPut();
    bool isDel();

    int getNum() const ;
};


#endif //REFERENCELIB_REQUESTTYPE_H
