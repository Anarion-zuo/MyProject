package com.http.network;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.*;

public class Response {
    protected Status status;
    protected Map<String, String> headers = new HashMap<>();
    protected byte[] data;

    public Response(int code) {
        status = new Status(code);

    }

    public void addHeaders(String key, String val) {
        headers.put(key, val);
    }

    public String toString() {
        StringBuilder builder = new StringBuilder();
        // first line
        builder.append("Http/1.1 ");
        builder.append(status.getCode());
        builder.append(" ");
        builder.append(status.getDiscription());
        builder.append("\r\n");
        // headers
        for (Map.Entry<String, String> entry : headers.entrySet()) {
            builder.append(entry.getKey());
            builder.append(": ");
            builder.append(entry.getValue());
            builder.append("\r\n");
        }
        builder.append("\r\n");
        builder.append(Arrays.toString(data));
        return new String(builder);
    }

    synchronized void sendToChannel(SocketChannel channel) throws IOException {
        String ser = toString();
        ByteBuffer buffer = ByteBuffer.allocate(ser.length());
        buffer.put(ser.getBytes());
        channel.write(buffer);
    }
}
