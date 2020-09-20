
#include "requestParser.h"
#include "request.h"

namespace DBProject
{
    RequestParser::RequestParser()
        : state_(method_start)
    {
    }

    void RequestParser::reset()
    {
        state_ = method_start;
    }

    RequestParser::result_type RequestParser::consume(Request& req, char input)
    {
        return result_type::good;
    }

    bool RequestParser::is_char(int c)
    {
        return c >= 0 && c <= 127;
    }

    bool RequestParser::is_ctl(int c)
    {
        return (c >= 0 && c <= 31) || (c == 127);
    }

    bool RequestParser::is_tspecial(int c)
    {
        switch (c)
        {
        case '(': case ')': case '<': case '>': case '@':
        case ',': case ';': case ':': case '\\': case '"':
        case '/': case '[': case ']': case '?': case '=':
        case '{': case '}': case ' ': case '\t':
            return true;
        default:
            return false;
        }
    }

    bool RequestParser::is_digit(int c)
    {
        return c >= '0' && c <= '9';
    }
}
