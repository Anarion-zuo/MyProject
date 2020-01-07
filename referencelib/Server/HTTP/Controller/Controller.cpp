//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "Controller.h"
#include "../../../exceptions/Server/Http/RequestTypeUnsupportedException.h"
#include "../View/HtmlView.h"
#include "../View/resolver/HtmlResolver.h"
#include "HelloController.h"
#include "../../Selector/EpollSelector.h"
#include "IconController.h"

Pointer<HtmlResolver> Controller::run(Pointer<Request> request, Pointer<Response> response) {
    int type = request->getType().getNum();
    Pointer<SString> retStr;
    Pointer<HashMap<SString, SString>> map = new HashMap<SString, SString>;
    switch (type) {
        case __http_get_type:
            retStr = onGet(request, response, map);
            break;
        case __http_post_type:
            retStr = onPost(request, response, map);
            break;
        case __http_put_type:
            retStr = onPut(request, response, map);
            break;
        case __http_del_type:
            retStr = onDelete(request, response, map);
            break;
        default:
            throw RequestTypeUnsupportedException();
    }
    Pointer<HtmlView> view = new HtmlView(retStr);
    Pointer<ViewModel> model = new ViewModel(map);
    Pointer<HtmlResolver> resolver = new HtmlResolver(view, model);
    return resolver;
}

Pointer<Map<SString, Controller>> Controller::controls = new HashMap<SString, Controller>;

void Controller::init(Pointer<EpollSelector> selector) {
    controls->put(new SString("/hi"), new HelloController);
    controls->put(new SString("/favicon.ico"), new IconController);
    while (true) {
        auto packet = selector->pollPacket();
        auto request = Request::readFromBuffer(packet->buffer);
        request->setChannel(packet->channel);
        packet.release();
        dispatchOne(request);
    }
}

void Controller::dispatchOne(Pointer<Request> request) {
    Pointer<Controller> controller = controls->get(request->getDirectory());
    Pointer<Response> response = new Response;
    Pointer<HtmlResolver> resolver = controller->run(request, response);
    response->setViewResolver(resolver);
    response->send(request->getChannel());
    resolver.release();
    response.release();
}
