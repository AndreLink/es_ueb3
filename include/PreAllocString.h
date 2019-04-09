#ifndef PREALLOCSTR_H
#define PREALLOCSTR_H

#include "Printf.h"
#include <stdlib.h>

#define CREATE(varname, size) PreAllocString<size> varname
#define NULL_TERMINATOR_SIZE 1
#define NULL_TERMINATOR '\0'
#define WHITESPACE ' '

template <size_t size>
class PreAllocString
{
    static_assert(size > 0);

  private:
    char text[size];
    size_t length;
    PreAllocString &addString(const char *rhs);
    bool addChar(const char c);

  public:
    PreAllocString();

    operator const char *() const;
    operator const void *() const;
    const char &operator[](const int idx);

    size_t GetLength() const;

    constexpr size_t SizeOf();

    void Empty();

    PreAllocString &operator=(char rhs);
    PreAllocString &operator=(const char *rhs);
    PreAllocString &operator=(char *const rhs);

    PreAllocString &operator+=(char rhs);
    PreAllocString &operator+=(char const *rhs);

    void AddFormat(const char *format, ...);
    void AddWhiteSpace();
};

template <size_t size>
bool PreAllocString<size>::addChar(const char c)
{
    if (length + NULL_TERMINATOR_SIZE < size)
    {
        text[length] = c;
        length++;
        return true;
    }
    return false;
}

template <size_t size>
PreAllocString<size> &PreAllocString<size>::addString(const char *rhs)
{
    if (nullptr != rhs)
    {
        int index = 0;
        while (NULL_TERMINATOR != rhs[index] && addChar(rhs[index]))
        {
            index++;
        }
    }
    return *this;
}

template <size_t size>
PreAllocString<size>::PreAllocString() { Empty(); }

template <size_t size>
PreAllocString<size>::operator const char *() const
{
    return text;
}

template <size_t size>
PreAllocString<size>::operator const void *() const
{
    return static_cast<void *>(text);
}

template <size_t size>
const char &PreAllocString<size>::operator[](const int idx)
{
    int index = idx % size;
    if (index < 0)
        index += size;
    return text[index];
}

template <size_t size>
size_t PreAllocString<size>::GetLength() const
{
    return length;
}

template <size_t size>
constexpr size_t PreAllocString<size>::SizeOf()
{
    return size;
}

template <size_t size>
void PreAllocString<size>::Empty()
{
    length = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        text[i] = NULL_TERMINATOR;
    }
}

template <size_t size>
PreAllocString<size> &PreAllocString<size>::operator=(char rhs)
{
    Empty();
    addChar(rhs);
    return *this;
}

template <size_t size>
PreAllocString<size> &PreAllocString<size>::operator=(const char *rhs)
{
    Empty();
    return addString(rhs);
}

template <size_t size>
PreAllocString<size> &PreAllocString<size>::operator=(char *const rhs)
{
    Empty();
    return addString(rhs);
}

template <size_t size>
PreAllocString<size> &PreAllocString<size>::operator+=(char rhs)
{
    addChar(rhs);
    return *this;
}

template <size_t size>
PreAllocString<size> &PreAllocString<size>::operator+=(char const *rhs)
{
    return addString(rhs);
}

template <size_t size>
void PreAllocString<size>::AddFormat(const char *format, ...)
{
    va_list vl;
    va_start(vl, format);
    char *dst = text + length;
    const void *end = text + size - NULL_TERMINATOR_SIZE;
    length += Printf(dst, end, format, vl);
    va_end(vl);
}

template <size_t size>
void PreAllocString<size>::AddWhiteSpace()
{
    addChar(WHITESPACE);
}

#endif /* PREALLOCSTR_H */