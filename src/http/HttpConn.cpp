#include "http/HttpConn.h"
#include "http/utils/MimeType.h"

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <fstream>
#include <sstream>

HttpConn::HttpConn() : m_fd(-1) {}

void HttpConn::updateActiveTime() {
    m_lastActive = std::chrono::steady_clock::now();
}

void HttpConn::init(int fd) {
    m_fd = fd;

    updateActiveTime();
}

bool HttpConn::readData() {
    char buffer[4096];

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        int ret = read(m_fd, buffer, sizeof(buffer));

        if (ret < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            return false;
        }
        else if (ret == 0) {
            return false;
        }
        else {
            m_readBuffer.append(buffer, ret);
        }
    }
    std::cout << "===== Raw Request =====\n";

    std::cout << m_readBuffer << std::endl;

    std::cout << "========================\n";

    // HTTP解析
    if (!m_request.parse(m_readBuffer)) {
        std::cout << "parse request failed\n";

        return false;
    }

    std::cout << "Method: " << m_request.method() << std::endl;

    std::cout << "Path: " << m_request.path() << std::endl;

    std::cout << "Version: " << m_request.version() << std::endl;

    updateActiveTime();

    return true;
}

bool HttpConn::writeData() {
    /*
    std::string body;

    if (m_request.path() == "/")
        body = "<h1>Welcome LightWebServer</h1>";
    else if (m_request.path() == "/hello")
        body = "<h1>Hello Page</h1>";
    else
        body = "<h1>404 Not Found</h1>";

    std::string response =
        "HTTP/1.1 200 OK\r\n" +
        connectionType +
        "Content-Type: " + mimeType + "\r\n" +
        "Content-Length: " +
        std::to_string(body.size()) +
        "\r\n" +
        "\r\n" +
        body;

    int ret = write(m_fd, response.c_str(), response.size());

    return ret > 0;
    */

    std::string filePath;

    if (m_request.path() == "/") {
        filePath = "../webroot/index.html";
    }
    else {
        filePath = "../webroot" + m_request.path();
    }

    std::string body = readFile(filePath);

    std::string response;

    // 文件不存在
    if (body.empty()) {
        body = "<h1>404 Not Found</h1>";

        response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " +
            std::to_string(body.size()) +
            "\r\n"
            "\r\n" +
            body;
    }
    else {
        std::string connectionType;

        if (isKeepAlive())
            connectionType = "Connection: Keep-Alive\r\n";
        else
            connectionType = "Connection: close\r\n";

        std::string mimeType = MimeType::getType(filePath);

        response =
            "HTTP/1.1 200 OK\r\n" + connectionType +
            "Content-Type:" + mimeType + "\r\n" +
            "Content-Length: " + std::to_string(body.size()) +
            "\r\n" +
            "\r\n" +
            body;
    }

    int ret = write(m_fd, response.c_str(), response.size());

    m_readBuffer.clear();

    return ret > 0;
}

void HttpConn::closeConn() {
    if (m_fd != -1) {
        close(m_fd);
        m_fd = -1;
    }
}

int HttpConn::getFd() const {
    return m_fd;
}

std::string HttpConn::readFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open())
        return "";

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

bool HttpConn::isKeepAlive() const {
    std::string connection = m_request.header("Connection");

    return connection == "keep-alive";
}

bool HttpConn::isTimeout(int timeoutSec) {
    auto now = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - m_lastActive);

    return duration.count() >= timeoutSec;
}