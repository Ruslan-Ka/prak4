#include <iostream>
#include <iostream>
#include <cmath>
#include <new>
#include <vector>
#include <map>
#include <functional>

namespace numbers {
    class complex {
        double re_, im_;
    public:
        complex(double re = 0, double im = 0)
        {
            re_ = re;
            im_ = im;
        }
        explicit complex(std::string str)
        {
            char *end;
            re_ = std::strtod(&str[1], &end);
            end++;
            im_ = std::strtod(end, &end);
        }
        double re() const
        {
            return re_;
        }
        double im() const
        {
            return im_;
        }
        double abs() const
        {
            return sqrt (re_ * re_ + im_ * im_);
        }
        double abs2() const
        {
            return re_ * re_ + im_ * im_;
        }
        std::string to_string() const
        {
            char buf[100];
            snprintf(buf, 100, "%c%.10g%c%.10g%c", '(', re_, ',', im_, ')');
            std::string s(buf);
            return s;
        }
        complex &operator += (const complex &c)
        {
            re_ += c.re_;
            im_ += c.im_;
            return *this;
        }
        complex &operator -= (const complex &c)
        {
            re_ -= c.re_;
            im_ -= c.im_;
            return *this;
        }
        complex &operator *= (const complex &c)
        {
            double tmp_re = re_;
            re_ = re_ * c.re_ - im_ * c.im_;
            im_ = tmp_re * c.im_ + im_ * c.re_;
            return *this;
        }
        complex &operator /= (const complex &c)
        {
            double tmp_re = re_;
            re_ = (re_ * c.re_ + im_ * c.im_) / (c.re_ * c.re_ + c.im_ * c.im_);
            im_ = (im_ * c.re_ - tmp_re * c.im_) / (c.re_ * c.re_ + c.im_ * c.im_);
            return *this;
        }
        complex operator ~() const
        {
            complex c(*this);
            c.im_ *= -1;
            return c;
        }
        complex operator -() const
        {
            complex c(*this);
            c.im_ *= -1;
            c.re_ *= -1;
            return c;
        }
    };

    complex operator + (complex b, const complex &c)
    {
        return b += c;

    }
    complex operator - (complex b, const complex &c)
    {
        return b -= c;
    }
    complex operator * (complex b, const complex &c)
    {
        return b *= c;
    }
    complex operator / (complex b, const complex &c)
    {
        return b /= c;
    }
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
    complex eval(const std::vector<std::string> &argc, const complex &z) {
        complex_stack A;
        std::map<std::string, std::function < void(std::string)> > mm;
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("+", [&](std::string str)
            {
                complex tmp = A[A.size() - 1] + A[A.size() - 2];
                A = ~~A;
                A = A << tmp;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("-", [&](std::string str)
            {
                complex tmp = A[A.size() - 2] - A[A.size() - 1];
                A = ~~A;
                A = A << tmp;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("*", [&](std::string str)
            {
                complex tmp = A[A.size() - 2] * A[A.size() - 1];
                A = ~~A;
                A = A << tmp;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("/", [&](std::string str)
            {
                complex tmp = A[A.size() - 2] / A[A.size() - 1];
                A = ~~A;
                A = A << tmp;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("z", [&](std::string str)
            {
                A = A << z;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("(", [&](std::string str)
            {
                complex tmp(str);
                A = A << tmp;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("!", [&](std::string str)
            {
                complex tmp = +A;
                A = A << tmp;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>(";", [&](std::string str)
            {
                A = ~A;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("#", [&](std::string str)
            {
                complex tmp = +A;
                A = ~A;
                A = A << -tmp;
            })
        );
        mm.insert(std::pair<std::string, std::function<void(std::string) >>("~", [&](std::string str)
            {
                complex tmp = +A;
                A = ~A;
                A = A << ~tmp;
            })
        );
        for (size_t i = 0; i < argc.size(); i++)
        {
            char c = argc[i][0];
            std::string s = "";
            s += c;
            mm[s](argc[i]);
        }
        return +A;
    }
}

int main ()
{
    std::vector<std::string> v = {"z", "!"};
    numbers::complex z(1,0);
    z = numbers::eval(v,z);
    std::cout << z.re() << z.im();

}