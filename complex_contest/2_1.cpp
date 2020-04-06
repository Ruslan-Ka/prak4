#include <iostream>
#include <cmath>

namespace numbers
{
    class complex {
        double re_, im_;
    public:
        complex(double re = 0, double im = 0) : re_(re), im_(im) {}
        explicit complex(const std::string & str)
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
}