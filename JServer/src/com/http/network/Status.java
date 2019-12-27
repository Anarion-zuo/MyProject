package com.http.network;

import java.util.HashMap;
import java.util.Map;

public class Status {
    static protected Map<Integer, String> statusMap = new HashMap<>();
    static {
        statusMap.put(100, "Continue");
        statusMap.put(101, "Switching Protocols");
        statusMap.put(200, "OK");
        statusMap.put(201, "Created");
        statusMap.put(202, "Accepted");
        statusMap.put(203, "Non-Authoritative Information");
        statusMap.put(204, "No Content");
        statusMap.put(205, "Reset Content");
        statusMap.put(206, "Partial Content");
        statusMap.put(300, "Multiple Choices");
        statusMap.put(301, "Moved Permanently");
        statusMap.put(302, "Found");
        statusMap.put(303, "See Other");
        statusMap.put(304, "Not Modified");
        statusMap.put(305, "Use Proxy");
        statusMap.put(306, "Unused");
        statusMap.put(307, "Temporary Redirect");
        statusMap.put(400, "Bad Request");
        statusMap.put(401, "Unauthorized");
        statusMap.put(402, "Payment Required");
        statusMap.put(403, "Forbidden");
        statusMap.put(404, "Not Found");
        statusMap.put(405, "Method Not Allowed");
        statusMap.put(406, "Not Acceptable");
        statusMap.put(407, "Proxy Authentication Required");
        statusMap.put(408, "Request Time-out");
        statusMap.put(409, "Conflict");
        statusMap.put(410, "Gone");
        statusMap.put(411, "Length Required");
        statusMap.put(412, "Precondition Failed");
        statusMap.put(413, "Request Entity Too Large");
        statusMap.put(414, "Request-URI Too Large");
        statusMap.put(415, "Unsupported Media Type");
        statusMap.put(416, "Requested range not satisfiable");
        statusMap.put(417, "Expectation Failed");
        statusMap.put(500, "Internal Server Error");
        statusMap.put(501, "Not Implemented");
        statusMap.put(502, "Bad Gateway");
        statusMap.put(503, "Service Unavailable");
        statusMap.put(504, "Gateway Time-out");
        statusMap.put(505, "HTTP Version not supported");
    }
    protected int code;

    public Status(int code) {
        this.code = code;
    }

    public int getCode() {
        return code;
    }

    public String getDiscription() {
        return statusMap.get(code);
    }

    public void setCode(int code) {
        this.code = code;
    }
}
