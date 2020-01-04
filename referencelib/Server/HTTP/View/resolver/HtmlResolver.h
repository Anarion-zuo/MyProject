//
// Created by anarion on 2019/12/31.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_HTMLRESOLVER_H
#define REFERENCELIB_HTMLRESOLVER_H


#include "../../../../base/Pointer.hpp"
#include "../HtmlView.h"
#include "ViewResolver.h"
#include "../model/ViewModel.h"

class HtmlResolver : public ViewResolver {
protected:
    Pointer<HtmlView> input;
    Pointer<ViewModel> model;
    Buffer buffer {1024};
public:
    explicit HtmlResolver(Pointer<HtmlView> input, Pointer<ViewModel> model);
    ~HtmlResolver();

    void send(Pointer<TcpSocketChannel> channel) override ;

    void loadView() override ;
    size_type getContentSize() override ;
};


#endif //REFERENCELIB_HTMLRESOLVER_H
