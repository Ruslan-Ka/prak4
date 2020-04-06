#include <vector>
#include <algorithm>

template <typename T1, typename T2, typename S1 = typename std::iterator_traits<T1>::value_type>
auto myremove(T1 it1, T1 it2, T2 del1, T2 del2)
{
    std::vector<S1> tmp;
    while(it1 != it2) {
        tmp.push_back(*it1);
        it1++;
    }
    std::sort(tmp.begin(), tmp.end());
    auto last = std::unique(tmp.begin(), tmp.end());
    tmp.erase(last, tmp.end());
    auto iter = tmp.begin();
    while (iter != tmp.end() && *iter < 0 ) {
        ++iter;
    }
    auto start = del1;
    int size = std::distance(del1, del2);
    auto sw = del1;
    while (iter != tmp.end() && *iter < size) {
        if (start + *iter == del1) {
            ++del1;
            ++iter;
        } else {
            std::iter_swap(sw,del1);
            ++sw;
            ++del1;
        }
    }
    while (del1 != del2) {
        std::iter_swap(del1, sw);
        ++sw;
        ++del1;
    }
    return sw;
}