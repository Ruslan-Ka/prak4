#include <iostream>
#include <vector>
#include <cstdint>

void process(std::vector<int64_t> &v, int64_t a)
{
    std::vector<int64_t>::reverse_iterator vit;
    int num = 0;
    auto incr = v.begin();
    while (incr != v.end()) {
        if (*incr >= a) {
            num++;
        }
        ++incr;
    }
    v.reserve(v.size() + num);
    vit = v.rbegin();
    while (vit < v.rend()) {
        if (*vit >= a) {
            v.push_back(*vit);
        }
        ++vit;
    }
}