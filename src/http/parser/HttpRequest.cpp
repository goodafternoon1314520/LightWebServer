#include "http/parser/HttpRequest.h"

#include <sstream>
#include <iostream>

bool HttpRequest::parse(const std::string& request) {
    /*
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
    */

    std::stringstream ss(request);
    std::string line;

    // 请求行
    std::getline(ss, line);

    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    std::stringstream lineStream(line);

    lineStream >> m_method
               >> m_path
               >> m_version;

    if (m_method.empty() || m_path.empty() || m_version.empty())
        return false;

    // header
    while (std::getline(ss, line)) {
        if (line == "\r" || line.empty())
            break;

        if (line.back() == '\r')
            line.pop_back();

        size_t pos = line.find(":");

        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);

        std::string value = line.substr(pos + 1);

        // 去掉前导空格
        while (!value.empty() && value[0] == ' ')
            value.erase(0, 1);

        m_headers[key] = value;
    }
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

std::string HttpRequest::header(const std::string& key) const {
    auto it = m_headers.find(key);

    if (it == m_headers.end())
        return "";

    return it -> second;
}
