#include "http/HttpConn.h"

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cerrno>

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
            std::cout.write(buffer, ret);
        }
    }
    return true;
}

bool HttpConn::writeData() {
    const char* response =
        "HTTP/1.1 200 OK\r\n\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<h1>Hello HttpConn</h1>\r\n";

    int ret = write(m_fd, response, strlen(response));

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
