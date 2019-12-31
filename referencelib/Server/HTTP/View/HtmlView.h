//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_HTMLVIEW_H
#define REFERENCELIB_HTMLVIEW_H


#include "View.h"
#include "../../../io/Channel/File/FileChannel.h"
#include "../../../io/Channel/Network/SocketChannel.h"

class HtmlView : public View {
    friend class HtmlResolver;
public:
    explicit HtmlView(Pointer<SString> name);
    void send() override;

    void readFile();
    void send(Pointer<SocketChannel> socket);
protected:
    HtmlView() = default;
    static Pointer<SString> suffix, prefix;
    Pointer<FileChannel> channel;
    Pointer<Buffer> buffer = Buffer::allocate(4096);
    Pointer<SString> dir;

    Pointer<SString> getSuffix() override;
    Pointer<SString> getPrefix() override;

};


#endif //REFERENCELIB_HTMLVIEW_H
