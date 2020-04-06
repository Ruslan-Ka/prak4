#include <iostream>
#include <iostream>
#include <cmath>
#include <new>
#include <vector>
#include <map>
#include <functional>
#include <cmath>
#include <cmc_complex.h>
#include <cmc_complex_stack.h>
#include <cmc_complex_eval.h>

int main (int argc, char *argv[])
{
    numbers::complex C(argv[1]);
    double  R;
    sscanf(argv[2], "%lf", &R);
    int N;
    sscanf(argv[3], "%d", &N);
    std::vector<std::string> str;
    for (int i = 4; i < argc; i++) {
        str.push_back(argv[i]);
    }
    numbers::complex ans;
    for (int i = 1; i < N + 1; i++) {
        double zi_re = C.re() + R * cos(2*M_PI * i / N);
        double zi_im = C.im() + R * sin(2 * M_PI  * i / N);
        double zj_re = C.re() + R * cos(2*M_PI * (i - 1) / N);
        double zj_im = C.im() + R * sin(2 * M_PI  * (i - 1) / N);
        numbers::complex zi(zi_re, zi_im);
        numbers::complex zj(zj_re, zj_im);
        ans += numbers::eval(str, zi) * (zi - zj);
    }
    std::cout << ans.to_string() << std::endl;
    return 0;
}