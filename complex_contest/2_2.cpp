#include <iostream>
#include <cmath>
#include <new>

namespace numbers
{
    class complex_stack
    {
        size_t size_;
        complex *arr;
    public:
        complex_stack(int size = 0): size_(size), arr(new complex[size]) {}
        complex_stack(const complex_stack & A): size_(A.size_), arr(new complex[size_])
        {
            for (size_t i = 0; i < size_; i++)
            {
                arr[i] = A[i];
            }
        }
        complex_stack(complex_stack && A): size_(A.size_), arr(A.arr)
        {
            A.size_ = 0;
            A.arr = nullptr;
        }
        ~complex_stack()
        {
            delete[] arr;
        }
        complex_stack & operator =(const complex_stack &a)
        {
            this->~complex_stack();
            new(this) complex_stack(a);
            return *this;
        }
        complex_stack & operator =(complex_stack &&a)
        {
            this->~complex_stack();
            arr = a.arr;
            size_ = a.size_;
            a.arr = nullptr;
            return *this;
        }
        size_t size() const
        {
            return size_;
        }
        complex operator [] (size_t size) const
        {
            return arr[size];
        }
        complex operator +() const
        {
            return arr[size_-1];
        }
        friend complex_stack operator << (const complex_stack &a, const complex &b);
        friend complex_stack operator << (complex_stack &&a, const complex &b);
        friend complex_stack operator ~(const complex_stack &a);
        friend complex_stack operator ~(complex_stack &&a);

    };
    complex_stack operator ~(const complex_stack &a)
    {
        complex_stack tmp(a.size_ - 1);
        for (size_t i = 0; i < a.size_ - 1; i++)
        {
            tmp.arr[i] = a.arr[i];
        }
        return tmp;
    }
    complex_stack operator ~(complex_stack &&a)
    {
        complex_stack tmp(a.size_ - 1);
        for (size_t i = 0; i < a.size_ - 1; i++)
        {
            tmp.arr[i] = a.arr[i];
        }
        a.size_ = 0;
        delete [] a.arr;
        a.arr = nullptr;
        return tmp;
    }
    complex_stack operator << (const complex_stack &a, const complex &b)
    {
        complex_stack tmp(a.size() + 1);
        for (size_t i = 0; i < a.size(); i++)
        {
            tmp.arr[i] = a.arr[i];
        }
        tmp.arr[a.size()] = b;
        return  tmp;
    }
    complex_stack operator << (complex_stack &&a, const complex &b)
    {
        complex_stack tmp(a.size() + 1);
        for (size_t i = 0; i < a.size(); i++)
        {
            tmp.arr[i] = a.arr[i];
        }
        tmp.arr[a.size()] = b;
        a.size_ = 0;
        delete [] a.arr;
        a.arr = nullptr;
        return  tmp;
    }
}