package com.test;

import com.http.network.HttpListener;
import org.junit.Test;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class testMain {
    @Test
    public void listener() throws IOException, InterruptedException {
        HttpListener listener = new HttpListener(12222, 10);
        listener.startup();
        while(true);
    }

    @Test
    public void readfirstline() {

    }
}
