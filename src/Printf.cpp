#include "Printf.h"

int Printf(char *dst, const void *end, const char *fmt, va_list vl)
{
    char *start = dst;
    // check arguments
    if (nullptr == dst || nullptr == end || nullptr == fmt || dst >= end)
    {
        return 0;
    }

    char currentSymbol;
    bool run = true;

    while (run && (currentSymbol = *fmt) != '\0')
    {
        switch (currentSymbol)
        {
        case '%':
            switch (
                *(fmt +
                  1)) // always a legal char, worst case '\0’ if the input is faulty
            {
            case 'd':
                run = writeSignedToBuffer(&dst, va_arg(vl, signed int), end);
                break;
            case 'u':
                run = writeConvertedToBuffer(&dst, va_arg(vl, unsigned int), 10, end);
                break;
            case 'c':
                run = writeCharToBuffer(&dst, va_arg(vl, int), end);
                break;
            case 's':
                run = writeStringToBuffer(&dst, va_arg(vl, char *), end);
                break;
            case 'x':
                run = writeHexToBuffer(&dst, va_arg(vl, int), end);
                break;
            case 'b':
                run = writeBinToBuffer(&dst, va_arg(vl, int), end);
                break;
            case '%':
                run = writeCharToBuffer(&dst, '%', end);
                break;
            default:
                run = false; // unsupported format symbol, better stop here
            }
            fmt += 2;
            break;
        default:
            run = writeCharToBuffer(&dst, currentSymbol, end);
            fmt += 1;
        }
    }
    return dst - start;
}

bool writeCharToBuffer(char **dst, int ch, const void *end)
{
    if (end <= *dst)
    {
        return false;
    }
    **(dst) = ch;
    *dst += 1;
    return true;
}

bool writeStringToBuffer(char **dst, char *ch, const void *end)
{
    char currentStringSymbol;
    bool run = true;
    for (int i = 0; run && (currentStringSymbol = *(ch + i)) != '\0'; ++i)
    {
        run = writeCharToBuffer(dst, currentStringSymbol, end);
    }
    return run;
}

bool writeSignedToBuffer(char **dst, signed int n, const void *end)
{
    bool run = true;
    if (n < 0)
    {
        n = n * -1;
        run = writeCharToBuffer(dst, '-', end);
    }
    return run && writeConvertedToBuffer(dst, n, 10, end);
}

bool writeBinToBuffer(char **dst, int n, const void *end)
{
    return writeCharToBuffer(dst, '0', end) && writeCharToBuffer(dst, 'b', end) &&
           writeConvertedToBuffer(dst, n, 2, end);
}

bool writeHexToBuffer(char **dst, int n, const void *end)
{
    return writeCharToBuffer(dst, '0', end) && writeCharToBuffer(dst, 'x', end) &&
           writeConvertedToBuffer(dst, n, 16, end);
}

bool writeConvertedToBuffer(char **dst, int n_raw, int base, const void *end)
{
    unsigned int n = static_cast<unsigned int>(n_raw);
    int len = 0;
    int j = n;
    do
    {
        len++;
        j /= base;
    } while (0 != j);
    char result[len + 1] = {'\0'};
    while (0 != len)
    {
        int current = n % base;
        if (current < 10)
        {
            result[len - 1] = '0' + current;
        }
        else
        {
            result[len - 1] = 'a' + current - 10;
        }
        n /= base;
        len -= 1;
    }
    return writeStringToBuffer(dst, result, end);
}