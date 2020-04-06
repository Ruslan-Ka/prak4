#include <iostream>

template<typename T>
auto process(const T &a)
{
    typename T::value_type res{};
    auto it = a.rbegin();
    int i = 0;
    while (it != a.rend()) {
        if (i == 0) {
            res += *it;
        }
        else if (i == 2) {
            res += *it;
        }
        else if (i == 4) {
            res += *it;
            break;
        }
        ++i;
        ++it;
    }
    return res;
}