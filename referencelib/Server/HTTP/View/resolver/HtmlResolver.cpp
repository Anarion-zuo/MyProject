//
// Created by anarion on 2019/12/31.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "HtmlResolver.h"

void HtmlResolver::send(Pointer<TcpSocketChannel> channel) {
    if (input.isNull()) {
        return ;
    }
    channel->read(Pointer<Buffer>(&buffer));
}

HtmlResolver::HtmlResolver(Pointer<HtmlView> input, Pointer<ViewModel> model) : input(input), model(model) {

}

void HtmlResolver::loadView() {
    if (input.isNull()) {
        return ;
    }
    input->readFile();
    input->buffer->flip();
    Pointer<Buffer> temp;
    while (true) {
        temp = input->buffer->getUntil('$');
        buffer.put(temp);
        temp.release();
        if (input->buffer->unReadSize() == 0) {
            break;
        }
        input->buffer->get();
        char c = input->buffer->get();
        if (c != '{') {
            char __t = '$';
            buffer.put(__t);
            buffer.put(c);
            continue;
        }
        char *str = input->buffer->getUntil('}', nullptr);
        Pointer<SString> key = new SString(str);
        Pointer<SString> val = model->getKey(key);
        buffer.put(val);
        input->buffer->get();
        key.release();
    }
}

size_type HtmlResolver::getContentSize() {
    return buffer.writtenSize();
}

HtmlResolver::~HtmlResolver() {
}
