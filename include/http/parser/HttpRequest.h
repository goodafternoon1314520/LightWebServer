#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <unordered_map>

enum ParseState {
  REQUEST_LINE,
  HEADERS,
  BODY,
  FINISH  
};

class HttpRequest {
public:
    bool parse(const std::string& request);

    std::string method() const;

    std::string path() const;

    std::string version() const;

    std::string header(const std::string& key) const;

private:
    ParseState m_state;

    std::string m_method;

    std::string m_path;

    std::string m_version;

    std::unordered_map<std::string, std::string> m_headers;
};

#endif