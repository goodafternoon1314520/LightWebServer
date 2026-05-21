#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>

class HttpRequest {
public:
    bool parse(const std::string& request);

    std::string method() const;

    std::string path() const;

    std::string version() const;

private:
    std::string m_method;

    std::string m_path;

    std::string m_version;
};

#endif