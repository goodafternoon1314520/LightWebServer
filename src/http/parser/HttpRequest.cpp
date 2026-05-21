#include "http/parser/HttpRequest.h"

#include <sstream>
#include <iostream>

bool HttpRequest::parse(const std::string& request) {
    std::stringstream ss(request);
    std::string line;

    // 读取请求行
    std::getline(ss, line);

    // 去掉 \r
    if (!line.empty() && line.back() == '\r')
        line.pop_back();

    std::stringstream lineStream(line);

    lineStream >> m_method
                >> m_path
                >> m_version;

    if (m_method.empty() || m_path.empty() || m_version.empty())
        return false;

    return true;
}

std::string HttpRequest::method() const {
    return m_method;
}

std::string HttpRequest::path() const {
    return m_path;
}

std::string HttpRequest::version() const {
    return m_version;
}
