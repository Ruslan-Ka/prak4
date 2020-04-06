#include <vector>
#include <functional>

template <typename T1, typename T2>
void myapply(T1 it1, T1 it2, T2 f)
{
    while (it1 != it2) {
        f(*it1);
        it1++;
    }
}

template <typename T2, typename T3>
auto myfilter2(T2 it1, T2 it2, T3 f)
{
    std::vector<std::reference_wrapper<typename std::iterator_traits<T2>::value_type>> tmp;
    while (it1 != it2) {
        if(f(*it1)) {
            tmp.insert(tmp.end(), std::ref(*it1));
        }
        it1++;
    }
    return tmp;
}