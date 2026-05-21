#ifndef HTTP_CONN_H
#define HTTPCONN_H

#include "http/parser/HttpRequest.h"

#include <string>

class HttpConn {
public:
    HttpConn();

    void init(int fd);

    bool readData();

    bool writeData();

    void closeConn();

    int getFd() const;

private:
    int m_fd;

    std::string m_readBuffer;
    HttpRequest m_request;
};

#endif