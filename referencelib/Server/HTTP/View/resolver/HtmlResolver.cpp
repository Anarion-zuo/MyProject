//
// Created by anarion on 2019/12/31.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "HtmlResolver.h"

void HtmlResolver::run(Pointer<SocketChannel> channel) {
    Pointer<Buffer> buffer;
    while (true) {
        buffer = input->buffer->getUntil('$');
        channel->read(buffer);
        buffer.release();
        if (input->buffer->unReadSize() == 0) {
            break;
        }
        input->buffer->get();
        char c = input->buffer->get();
        if (c != '{') {
            char __t = '$';
            channel->read(&__t, 1);
            channel->read(&c, 1);
            continue;
        }
        char *str = input->buffer->getUntil('}', nullptr);
        Pointer<SString> key = new SString(str);
        Pointer<SString> val = model->getKey(key);
        channel->read(val);
        c = '}';
        channel->read(&c, 1);
        key.release();
    }
}

HtmlResolver::HtmlResolver(Pointer<HtmlView> input, Pointer<ViewModel> model) : input(input), model(model) {

}
