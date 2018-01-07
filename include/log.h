#ifndef __LOG_H__
#define __LOG_H__

#include <vector>
#include <cstdio>
#include <cstdarg>
#include <ctime>

void debug_log(const char *fmt, ...) {
    static FILE* fp = stdout;
    std::time_t t = std::time(nullptr);
    char time_buf[100];
    std::strftime(time_buf, sizeof time_buf, "%D %T", std::gmtime(&t));
    va_list args1;
    va_start(args1, fmt);
    va_list args2;
    va_copy(args2, args1);
    std::vector<char> buf(1+std::vsnprintf(NULL, 0, fmt, args1));
    va_end(args1);
    std::vsnprintf(buf.data(), buf.size(), fmt, args2);
    va_end(args2);
    std::fprintf(fp, "%s [debug]: %s\n", time_buf, buf.data());
}

#endif // !__LOG_H__
