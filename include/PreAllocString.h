#include <stdlib.h>

#ifndef PREALLOCSTR_H

#define PREALLOCSTR_H

template <int size>
class PreAllocString {

    private:
        char text[size];

    public:
        PreAllocString();
        //~PreAllocString();

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
PreAllocString<size>::operator const char *() const {
    return text;
}

template <int size>
PreAllocString<size>::operator const void *() const {
    return text;
}

template <int size>
const char & PreAllocString<size>::operator [] (const int idx) {
    if (idx > 0 && idx < size) {
        return text[idx];
    } else {
        return text[0];
    }
}

template <int size>
PreAllocString<size>::PreAllocString() {
    Empty();
}

/*
template <int size>
PreAllocString<size>::~PreAllocString() {
    delete text;
}
*/
template <int size>
size_t PreAllocString<size>::GetLength() const {
    int l = 0;
    while (text[l] != '\0' && l < size) {
        l++;
    }
    return l;
}

template <int size>
constexpr size_t PreAllocString<size>::SizeOf() {
    return size;
}

template <int size>
void PreAllocString<size>::Empty() {
    for (int i = 0; i<size; i++) {
        text[i] = '\0';
    }
}

template <int size>
PreAllocString<size>& PreAllocString<size>::operator = (char rhs) {
    Empty();
    text[0] = rhs;
    return *this;
}

template <int size>
PreAllocString<size>& PreAllocString<size>::operator = (const char * rhs) {
    if (nullptr == rhs) {
        return *this;
    }
    Empty();
    int l = 0;
    while(rhs[l] != '\0' && l < size-1) {
        text[l] = rhs[l];
        l++;
    }
    return *this;
}


template <int size>
PreAllocString<size>& PreAllocString<size>::operator = (char * const rhs) {
    if (nullptr == rhs) {
        return *this;
    }
    Empty();
    int l = 0;
    while(rhs[l] != '\0' && l < size-1) {
        text[l] = rhs[l];
        l++;
    }
    return *this;
}

template <int size>
PreAllocString<size>& PreAllocString<size>::operator += (char rhs) {
    int len = GetLength();
    if (len < size-1) {
        text[len+1] = rhs;
    }
    return *this;
}


template <int size>
PreAllocString<size>& PreAllocString<size>::operator += (char const * rhs) {
    if (nullptr == rhs) {
        return *this;
    }
    int currentLength = GetLength();
    int index = 0;
    while (currentLength + index < size) {
        text[currentLength + index] = rhs[index];
        index++;
    }
    return *this;
}

template <int size>
void PreAllocString<size>::AddFormat(const char * format, ...) {

}

template <int size>
void PreAllocString<size>::AddWhiteSpace() {
    this += ' ';
}

#endif /* PREALLOCSTR_H */