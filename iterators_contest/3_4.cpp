#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class A
{
    double res_;
public:
    A() : res_(0) {};
    void operator () (const double &num)
    {
        res_ += num;
    }
    double answer () const
    {
        return res_;
    }
};

int main() {
    A ans;
    std::vector<double>v;
    double num;
    while (std:: cin >> num) {
        v.push_back(num);
    }
    int a = v.size();
    v.erase(v.begin(), v.begin() + a / 10);
    v.erase(v.end() - a / 10, v.end());
    std::sort(v.begin(), v.end());
    a = v.size();
    v.erase(v.begin(), v.begin() + a / 10);
    v.erase(v.end() - a / 10, v.end());
    ans = std::for_each(v.begin(), v.end(), ans);
    std::cout << std::setprecision(10) << ans.answer() / v.size() << std::endl;
    return 0;
}