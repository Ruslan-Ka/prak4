#include <iostream>
#include <vector>
#include <cstdint>

void process(std::vector<uint64_t > const &v, std::vector<uint64_t > &l, int st)
{
    std::vector<uint64_t >::const_iterator vit;
    std::vector<uint64_t >::reverse_iterator lit;
    vit = v.begin();
    lit = l.rbegin();
    while (vit < v.end() && lit != l.rend())
    {

        *lit += *vit;
        ++lit;
        if (v.end() - vit > st) {
            vit += st;
        } else {
            break;
        }
    }
}