//
// Created by anarion on 2019/12/28.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef MYCPPLIB_REQUESTTYPE_H
#define MYCPPLIB_REQUESTTYPE_H

class RequestType {
protected:
    int type;
public:
    static RequestType makeType(const char *word);

    bool isGet();
    bool isPost();
    bool isPut();
    bool isDel();
};


#endif //MYCPPLIB_REQUESTTYPE_H
