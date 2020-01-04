//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "HtmlView.h"
#include "../../../container/SString.h"

Pointer<SString> HtmlView::prefix = new SString("../WEB/views/");
Pointer<SString> HtmlView::suffix = new SString(".html");

void HtmlView::send() {

}

Pointer<SString> HtmlView::getSuffix() {
    return suffix;
}

Pointer<SString> HtmlView::getPrefix() {
    return prefix;
}

HtmlView::HtmlView(Pointer<SString> name) {
    if (name.isNull()) {
        return;
    }
    if (name->length() == 0) {
        return;
    }
    dir = prefix->clone();
    dir->append(name);
    dir->append(suffix);
    // open file
    channel = FileChannel::open(dir);

}

void HtmlView::readFile() {
    if (dir.isNull()) {
        return;
    }
    channel->write(buffer);
}

void HtmlView::send(Pointer<TcpSocketChannel> socket) {
    socket->read(buffer);
}

size_type HtmlView::fileSize() {
    return channel->fileSize();
}
