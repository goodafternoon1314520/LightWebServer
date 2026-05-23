#ifndef HTTP_CONN_H
#define HTTPCONN_H

#include "http/parser/HttpRequest.h"

#include <string>
#include <chrono>

class HttpConn {
public:
    HttpConn();

    void init(int fd);

    bool readData();

    bool writeData();

    bool sendData();

    void closeConn();

    int getFd() const;

    std::string readFile(const std::string& path);

    bool isKeepAlive() const;

    void updateActiveTime();

    bool isTimeout(int timeoutSec);

    size_t bytesToSend() const;

private:
    int m_fd;

    std::string m_readBuffer;
    std::string m_writeBuffer;

    size_t m_bytesToSend;

    HttpRequest m_request;

    std::chrono::steady_clock::time_point m_lastActive;
};

#endif