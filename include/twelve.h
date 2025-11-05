#ifndef TWELVE_
#define TWELVE_

#include <string>
#include <stdlib.h>
#include <iostream>
#include <exception>

class Twelve {
    
    unsigned char* twelve_repr;
    size_t size;

public:

    Twelve();
    Twelve(const size_t &n, unsigned char t = 0);
    Twelve(const std::initializer_list<unsigned char> &t);
    Twelve(const std::string n);
    Twelve(const Twelve &other);
    Twelve(Twelve &&other) noexcept;
    virtual ~Twelve() noexcept;
    bool eq(Twelve &other);
    bool gt(Twelve &other);
    bool lt(Twelve &other);
    Twelve add(Twelve &other);
    Twelve sub(Twelve &other);
    void copy_from(Twelve &other);
    void move_from(Twelve &&other) noexcept;
    void print();

};

#endif