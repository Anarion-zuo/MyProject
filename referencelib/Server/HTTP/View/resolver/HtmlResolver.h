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
public:
    explicit HtmlResolver(Pointer<HtmlView> input, Pointer<ViewModel> model);
    void run(Pointer<SocketChannel> channel) override ;
};


#endif //REFERENCELIB_HTMLRESOLVER_H
