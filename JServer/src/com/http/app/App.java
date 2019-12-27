package com.http.app;

import com.http.network.Request;
import com.http.network.Response;

import java.util.LinkedList;
import java.util.List;
import java.util.regex.Pattern;

public class App {
    protected List<String> patterns;
    protected static List<App> apps = new LinkedList<>();

    public App(List<String> patterns) {
        this.patterns = patterns;
    }

    static {
        apps.add(new App(List.of("*")));

    }

    static public void onBoot() {}
    public void onGet(Request request, Response response) {}
    public void onPost(Request request, Response response) {}
    public void onShut() {}

    boolean matchMe(String input) {
        for (var item : patterns) {
            if (Pattern.matches(input, item)) {
                return true;
            }
        }
        return false;
    }

    static public App matchApp(String input) {
        for (var app : apps) {
            if (app.matchMe(input)) {
                return app;
            }
        }
        return null;
    }

    public void run(Request request, Response response) {
        switch (request.getType()) {
            case "GET":
                onGet(request, response);
                break;
            case "POST":
                onPost(request, response);
                break;
        }
    }
}
