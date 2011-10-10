#ifndef COOKIE_H
#define COOKIE_H

#include <string>

class Cookie {
public:
    Cookie();
    virtual ~Cookie();

    static Cookie parse(const std::string& cookieString);
    std::string build() const;
    bool isValid(const std::string& path, const std::string& domain) const;

private:
    std::string name;
    std::string value;
    std::string comment;
    std::string domain;
    std::string maxAge;
    std::string path;
    std::string secure;
    std::string version;
    std::string expires;
};

#endif // COOKIE_H
