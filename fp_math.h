//
// Created by Domenico Neri on 01/06/22.
//

#ifndef GENERIC01_FP_MATH_H
#define GENERIC01_FP_MATH_H
#include "constexpr_math.h"

namespace fp_math {
    template<unsigned short precision_v = 4 >
    class number {
    public:
        using storage_type = long long;
        using same_precision_number = number<precision_v>;

        constexpr static auto precision = precision_v;
        constexpr static auto offset = static_cast<storage_type >(
                constexpr_math::pow(decltype(precision){10},precision_v)
                );

        constexpr storage_type int_part() const noexcept{
            return value_ / offset;
        }
        constexpr storage_type fract_part() const noexcept{
            return value_ % (int_part() * offset);
        }

        constexpr number() = default;
    private:
        storage_type value_ = 0;
    };

} // fp_math

#endif //GENERIC01_FP_MATH_H
