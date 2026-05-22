#ifndef MIMETYPE_H
#define MIMETYPE_H

#include <string>

class MimeType {
public:
    static std::string getType(const std::string& path);
};

#endif