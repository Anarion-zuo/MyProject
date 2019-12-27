package com.http.network;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.*;
import java.util.concurrent.*;

public class Request {
    protected String type;
    protected String httpVersion;
    protected String dir;
    protected Map<String, String> headers = new HashMap<>();
    protected byte[] data;
    protected SocketChannel channel;

    static private BlockingQueue<Request> requests = new LinkedBlockingQueue<>();

    public static void pushNew(Request request) throws InterruptedException {
        requests.put(request);
    }

    public static Request popOne() throws InterruptedException {
        return requests.take();
    }

    public Request(SocketChannel channel) throws IOException {
        // drain channel
        this.channel = channel;
        ByteBuffer buffer = ByteBuffer.allocate(4096);
        StringBuilder str_buf = new StringBuilder();
        while (true) {
            buffer.clear();
            int len = channel.read(buffer);
            str_buf.append(new String(buffer.array(), 0, len));
            if (len < 4096) {
                break;
            }
        }
        // first line
        int index = str_buf.indexOf(" "), last = 0;
        type = str_buf.substring(last, index);
        last = index + 1;
        index = str_buf.indexOf(" ", last);
        dir = str_buf.substring(last, index);
        last = index + 1;
        index = str_buf.indexOf("\r\n");
        httpVersion = str_buf.substring(last, index);
        last = index + 2;
        // headers
        while (true) {
            // get the line
            index = str_buf.indexOf("\r\n", last);
            String line = str_buf.substring(last, index);
            last = index + 2;
            if (line.isEmpty()) {
                break;
            }
            int line_index = line.indexOf(": ", 0), line_last;
            line_last = line_index + 2;
            String key = line.substring(0, line_index);
            String val = line.substring(line_last);
            System.out.println(key + val);
        }
        // data
        data = str_buf.substring(last).getBytes();
    }

    public String getType() {
        return type;
    }

    public String getHttpVersion() {
        return httpVersion;
    }

    public String getDir() {
        return dir;
    }

    public Map<String, String> getHeaders() {
        return headers;
    }

    public byte[] getData() {
        return data;
    }

    public String getHeaderVal(String key) {
        return headers.get(key);
    }

}
