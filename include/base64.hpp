#ifndef BASE64_HPP
#define BASE64_HPP

#include <iostream>
#include <vector>

typedef unsigned char uchar;

class Base64
{
public:
    Base64();
    std::string base64_encode(const std::string& data);
    std::string base64_decode(const std::string& data);

private:
    std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//=
};

#endif // BASE64_HPP
