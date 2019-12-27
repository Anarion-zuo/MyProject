package com.spring.helloworld;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class SpringmvcHandler {

    @RequestMapping("/hello/{id}")
    public String handleHello(@PathVariable("id") Integer id) {
        System.out.println("Hello Spring MVC" + id);
        return "hello";
    }
}
