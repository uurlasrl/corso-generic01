#include <iostream>
#include "constexpr_math.h"
#include "fp_math.h"
int main() {
    constexpr int precision = 10;
    constexpr auto c = constexpr_math::fast_cos<precision, double>{};
    constexpr auto c2 = constexpr_math::fast_cos<precision, float>{};
    std::cout << c.cos(60.1)<<std::endl;
    return 0;
}
