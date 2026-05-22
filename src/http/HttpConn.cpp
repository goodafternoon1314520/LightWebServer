#include "http/HttpConn.h"
#include "http/utils/MimeType.h"

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <fstream>
#include <sstream>

HttpConn::HttpConn() : m_fd(-1) {}

void HttpConn::init(int fd) {
    m_fd = fd;
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
        "HTTP/1.1 200 OK\r\n\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
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
            "\r\n" +
            body;
    }
    else {
        std::string mimeType = MimeType::getType(filePath);

        response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type:" + mimeType + "\r\n"
            "\r\n" +
            body;
    }

    int ret = write(m_fd, response.c_str(), response.size());

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