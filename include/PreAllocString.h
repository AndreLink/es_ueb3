#include <stdlib.h>

#ifndef PREALLOCSTR_H

#define PREALLOCSTR_H

template <int size>
class PreAllocString {

    private:
        char text[size+1];

    public:
        PreAllocString();
        ~PreAllocString();

        operator const char *() const;
        operator const void *() const;
        const char & operator [] (const int idx);

        size_t GetLength() const;

        constexpr size_t SizeOf();

        void Empty();

        PreAllocString& operator =(char rhs);
        PreAllocString& operator =(const char * rhs);
        PreAllocString& operator =(char * const rhs);

        PreAllocString& operator +=(char rhs);
        PreAllocString& operator +=(char const * rhs);

        void AddFormat(const char * format, ...);
        void AddWhiteSpace();

};

template <int size>
constexpr size_t PreAllocString<size>::SizeOf() {
    return size;
}

#endif /* PREALLOCSTR_H */