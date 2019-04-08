#include "PreAllocString.h"

/* TODO x
    operator const char *() const;
    operator const void *() const;
    const char & operator [] (const int idx);
*/

template <int size>
PreAllocString<size>::PreAllocString() {
    if (size <= 0) {
        size = 1;
    }
    this->text = new char[size+1];
    this->Empty();
    this->text[size+1] = '\0';
}

template <int size>
PreAllocString<size>::~PreAllocString() {
    delete(text);
}

template <int size>
size_t PreAllocString<size>::GetLength() const {
    int l = 0;
    while (text[l] != '\0') {
        l++;
    }
    return l;
}

template <int size>
void PreAllocString<size>::Empty() {
    for (int i = 0; i<size; i++) {
        this->text[i] = '\0';
    }
}

template <int size>
PreAllocString<size>& PreAllocString<size>::operator = (char rhs) {
    this->Empty();
    this->text[0] = rhs;
    return this;
}

template <int size>
PreAllocString<size>& PreAllocString<size>::operator = (const char * rhs) {
    this->Empty();
    int l = 0;
    while(rhs[l] != '\0') {
        this->text[l] = rhs[l];
    }
    return this;
}


template <int size>
PreAllocString<size>& PreAllocString<size>::operator = (char * const rhs) {
    this->Empty();
    int l = 0;
    while(rhs[l] != '\0') {
        this->text[l] = rhs[l];
    }
    return this;
}

template <int size>
PreAllocString<size>& PreAllocString<size>::operator += (char rhs) {
    int len = this->GetLength();
    if (len < size) {
        this->text[len+1] = rhs;
    }
    return this;
}


template <int size>
PreAllocString<size>& PreAllocString<size>::operator += (char const *rhs) {
    int currentLength = this->GetLength();
    int index = 0;
    while (currentLength + index < size) {
        this->text[currentLength + index] = rhs[index];
        index++;
    }
    return this;
}

template <int size>
void PreAllocString<size>::AddFormat(const char * format, ...) {

}

template <int size>
void PreAllocString<size>::AddWhiteSpace() {

}



