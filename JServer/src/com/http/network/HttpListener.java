package com.http.network;

import com.http.app.App;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.Iterator;
import java.util.Set;
import java.util.concurrent.*;

public class HttpListener {

    protected int portNum;
    protected Selector selector;
    protected ByteBuffer buffer = ByteBuffer.allocate(4096);
    protected ExecutorService threadPool;

    public HttpListener(int port_num, int concurrent_num) throws IOException {
        portNum = port_num;
        // concurrence controlled to a fixed value
        threadPool = Executors.newFixedThreadPool(concurrent_num);
        // get channel and bind to port
        var channel = ServerSocketChannel.open();
        channel.configureBlocking(false);    // non-block
        channel.socket().bind(new InetSocketAddress(port_num));
        // get selector
        selector = Selector.open();
        channel.register(selector, SelectionKey.OP_ACCEPT);
    }

    public void startup() throws IOException, InterruptedException {
        // start dispatcher
        threadPool.execute(()->{
            while (true) {
                Request request = null;
                try {
                    request = Request.popOne();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                App app = App.matchApp(request.dir);
                Response response = null;
                if (app == null) {
                    response = new Response(501);
                } else {
                    response = new Response(200);
                    app.run(request, response);
                }
                try {
                    response.sendToChannel(request.channel);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        // startup
        while (true) {
            while (selector.select() <= 0);
            Set<SelectionKey> keys = selector.selectedKeys();
            for (Iterator<SelectionKey> iterator = keys.iterator(); iterator.hasNext();) {
                SelectionKey key = iterator.next();
                iterator.remove();
                if (key.isAcceptable()) {
                    ServerSocketChannel channel = (ServerSocketChannel) key.channel();
                    SocketChannel acceptChannel = channel.accept();
                    acceptChannel.configureBlocking(false);
                    acceptChannel.register(selector, SelectionKey.OP_READ);
                } else if (key.isReadable()) {
                    SocketChannel client = (SocketChannel) key.channel();
                    // real stuff
                    threadPool.execute(()->{
                        Request request = null;
                        try {
                            request = new Request(client);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        Request finalRequest = request;
                        try {
                            Request.pushNew(finalRequest);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    });
                } else if (key.isWritable()) {
                    SocketChannel channel = (SocketChannel) key.channel();

                }
            }
        }
    }
}
