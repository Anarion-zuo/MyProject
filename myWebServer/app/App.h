//
// Created by anarion on 2019/10/22.
//

#ifndef MYWEBSERVER_APP_H
#define MYWEBSERVER_APP_H

#include <regex>
#include <list>
#include <utility>
#include "../request/Request.h"
#include "../response/Response.h"

/*
 * asset dir struct
 * asset
 *    -- [app name]
 *        -- xxx
 *        -- xxx
 *        -- xxx
 *    -- [app name]
 *        -- xxx
 *        -- xxx
 */

class PageApp;
class App {
    friend class Listener;
protected:

    static const std::string WebInfoDir, assetsDir, appsDir, modulesDir, pagesDir;
    std::list<std::string> patterns;
    static std::vector<App*> apps;

    // virtual ones
    virtual void onBoot() {}
    virtual void onClose() {}
    virtual void onGet(Request &request, Response &response) {}
    virtual void onPost(Request &request, Response &response) {}

    void runThis(Request &&request);

    // match app
    bool matchMe(const std::string &str);
    static App &matchApp(const std::string &str);

    // redirect & forward
    static void redirect(std::string &&location, Response &response);
    template <class T> static void forward(Request &&request) { T({}).runThis(std::forward<Request>(request)); }

    // compress
    static int compressFile(int fd, const std::string &target_dir);
public:
    explicit App(std::list<std::string> patterns) : patterns(std::move(patterns)) {
        onBoot();
    }

    virtual ~App() {onClose();}

    template <typename App_T>
    static void registerApp(const std::list<std::string> &new_patterns) {
        auto p = new App_T(new_patterns);
        apps.push_back(p);
    }
};


#endif //MYWEBSERVER_APP_H
