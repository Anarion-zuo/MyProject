//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "Controller.h"
#include "../../../exceptions/Server/Http/RequestTypeUnsupportedException.h"
#include "../View/HtmlView.h"
#include "../View/resolver/HtmlResolver.h"

Pointer<HtmlResolver> Controller::run(Pointer<Request> request, Pointer<Response> response) {
    int type = request->getType().getNum();
    Pointer<SString> retStr;
    switch (type) {
        case __http_get_type:
            retStr = onGet(request, response);
            break;
        case __http_post_type:
            retStr = onPost(request, response);
            break;
        case __http_put_type:
            retStr = onPut(request, response);
            break;
        case __http_del_type:
            retStr = onDelete(request, response);
            break;
        default:
            throw RequestTypeUnsupportedException();
    }
    Pointer<HtmlView> view = new HtmlView(retStr);
    Pointer<ViewModel> model = new ViewModel(new HashMap<SString, SString>);
    Pointer<HtmlResolver> resolver = new HtmlResolver(view, model);
    return resolver;
}

Pointer<Map<Request, Controller>> Controller::controls = new HashMap<Request, Controller>;

void Controller::init() {

}

void Controller::dispatchOne(Pointer<Request> request) {
    Pointer<Controller> controller = controls->get(request);
    Pointer<Response> response = new Response;
    Pointer<HtmlResolver> resolver = controller->run(request, response);
    response->addView
}
