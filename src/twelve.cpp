#include "../include/twelve.h"

Twelve::Twelve()
{
    size = 1;
    twelve_repr = new unsigned char[1];
    twelve_repr[0] = '0';
}

Twelve::Twelve(const size_t &n, unsigned char t)
{
    if((t < '0') || ((t > '9') && (t != 'A') && (t != 'B')))
        throw std::exception();
    size = n;
    twelve_repr = new unsigned char[n];
    for(size_t i = 0; i < n; ++i)
        twelve_repr[i] = t;
}

Twelve::Twelve(const std::initializer_list<unsigned char> &t)
{
    size = t.size();
    size_t i = size - 1;
    twelve_repr = new unsigned char[size];
    for(auto num: t)
    {
        if((num < '0') || ((num > '9') && (num != 'A') && (num != 'B')))
            throw std::exception();
        twelve_repr[i] = num;
        i--;
    }
}

Twelve::Twelve(const std::string n)
{
    size = n.length();
    twelve_repr = new unsigned char[size];
    for(size_t i = 0; i < size; ++i)
    {
        if((n[i] < '0') || ((n[i] > '9') && (n[i] != 'A') && (n[i] != 'B')))
            throw std::exception();
        twelve_repr[size - i - 1] = n[i];
    }
}

Twelve::Twelve(const Twelve &other)
{
    size = other.size;
    twelve_repr = new unsigned char[size];
    for(size_t i = 0; i < size; ++i)
        twelve_repr[i] = other.twelve_repr[i];
}

Twelve::Twelve(Twelve &&other) noexcept
{
    size = other.size;
    twelve_repr = other.twelve_repr;
    other.size = 0;
    other.twelve_repr = nullptr;
}

bool Twelve::eq(Twelve &other)
{
    if(size != other.size) return false;
    for(size_t i = 0; i < size; ++i)
        if(twelve_repr[i] != other.twelve_repr[i])
            return false;
    return true;
}

bool Twelve::gt(Twelve &other)
{
    if(size > other.size) return true;
    if(size < other.size) return false;
    for(size_t i = size - 1; i >= 0; --i)
    {
        if(twelve_repr[i] > other.twelve_repr[i])
            return true;
        if(twelve_repr[i] < other.twelve_repr[i])
            return false;
    }
    return false;
}

bool Twelve::lt(Twelve &other)
{
    if(size > other.size) return false;
    if(size < other.size) return true;
    for(size_t i = size - 1; i >= 0; --i)
    {
        if(twelve_repr[i] > other.twelve_repr[i])
            return false;
        if(twelve_repr[i] < other.twelve_repr[i])
            return true;
    }
    return false;
}

Twelve Twelve::add(Twelve &other)
{
    size_t result_size = std::max(size, other.size), rvsize;
    unsigned char* res = new unsigned char[result_size + 1];
    unsigned char *lvalue, *rvalue;

    if(size < other.size)
    {
        lvalue = new unsigned char[other.size];
        for(size_t i = 0; i < other.size; ++i)
            lvalue[i] = other.twelve_repr[i];
        rvalue = new unsigned char[size];
        for(size_t i = 0; i < size; ++i)
            rvalue[i] = twelve_repr[i];
        rvsize = size;
    }
    else
    {
        rvalue = new unsigned char[other.size];
        for(size_t i = 0; i < other.size; ++i)
            rvalue[i] = other.twelve_repr[i];
        rvsize = other.size;
        lvalue = new unsigned char[size];
        for(size_t i = 0; i < size; ++i)
            lvalue[i] = twelve_repr[i];
    }

    unsigned char rem = 0;
    for(size_t i = 0; i < result_size; ++i)
    {
        if((lvalue[i] == 'A') || (lvalue[i] == 'B'))
            lvalue[i] = lvalue[i] - '0' - 7;
        else lvalue[i] = lvalue[i] - '0';
        if((i < rvsize) && ((rvalue[i] == 'A') || (rvalue[i] == 'B')))
            rvalue[i] = rvalue[i] - '0' - 7;
        else rvalue[i] = rvalue[i] - '0';
        if(i < rvsize)
        {
            unsigned char sum = lvalue[i] + rvalue[i] + rem;
            res[i] = sum % 12;
            rem = sum / 12;
        }
        else
        {
            unsigned char sum = lvalue[i] + rem;
            res[i] = sum % 12;
            rem = sum / 12;
        }
    }


    if(rem == 1)
        res[result_size] = 1;
    std::string ans = "";
    if(res[result_size] == 1)
        ans += '1';
    for(int i = result_size - 1; i >= 0; --i)
    {
        if(res[i] >= 10)
            ans += (res[i] + '0' + 7);
        else
            ans += (res[i] + '0');
    }
    
    Twelve result(ans);
    delete[] rvalue;
    delete[] lvalue;
    delete[] res; 
    return result;   
}

Twelve Twelve::sub(Twelve &other) 
{
    if (!this->gt(other))
        throw std::exception(); 

    size_t result_size = size, rvsize;
    unsigned char* res = new unsigned char[result_size];
    unsigned char *lvalue, *rvalue;
    rvalue = new unsigned char[other.size];
    for(size_t i = 0; i < other.size; ++i)
        rvalue[i] = other.twelve_repr[i];
    rvsize = other.size;
    lvalue = new unsigned char[size];
    for(size_t i = 0; i < size; ++i)
        lvalue[i] = twelve_repr[i];


    for(size_t i = 0; i < result_size; ++i)
    {
        if((lvalue[i] == 'A') || (lvalue[i] == 'B'))
            lvalue[i] = lvalue[i] - '0' - 7;
        else lvalue[i] = lvalue[i] - '0';
        
        if((i < rvsize) && ((rvalue[i] == 'A') || (rvalue[i] == 'B')))
            rvalue[i] = rvalue[i] - '0' - 7;
        else if(i < rvsize)
            rvalue[i] = rvalue[i] - '0';
    }

    unsigned char borrow = 0;
    for(size_t i = 0; i < result_size; ++i)
    {
        int left_val = lvalue[i];
        int right_val = (i < rvsize) ? rvalue[i] : 0;
        int diff = left_val - right_val - borrow;
        if (diff < 0)
        {
            diff += 12;
            borrow = 1;
        } 
        else
            borrow = 0;
        res[i] = diff;
    }

    int first_non_zero = result_size - 1;
    while (first_non_zero > 0 && res[first_non_zero] == 0)
        first_non_zero--;

    std::string ans = "";
    for(int i = first_non_zero; i >= 0; --i)
    {
        if(res[i] >= 10)
            ans += (res[i] + '0' + 7);
        else
            ans += (res[i] + '0');
    }
    
    Twelve result(ans);
    delete[] rvalue;
    delete[] lvalue;
    delete[] res; 
    return result;   
}

void Twelve::copy_from(Twelve &other)
{
    if (this == &other) return;
    delete[] twelve_repr;
    size = other.size;
    twelve_repr = new unsigned char[size];
    for(size_t i = 0; i < size; ++i) {
        twelve_repr[i] = other.twelve_repr[i];
    }
}

void Twelve::move_from(Twelve &&other) noexcept
{
    if (this == &other) return;
    delete[] twelve_repr;
    size = other.size;
    twelve_repr = other.twelve_repr;
    other.size = 0;
    other.twelve_repr = nullptr;
}

void Twelve::print()
{
    for(int i = size - 1; i >= 0; --i)
        std::cout << twelve_repr[i];
    std::cout << std::endl;
}

Twelve::~Twelve() noexcept
{ 
    delete[] twelve_repr;
}

