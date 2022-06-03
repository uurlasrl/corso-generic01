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

        template<typename  float_type>
        constexpr number(const float_type &value) noexcept{
            value_ = static_cast<storage_type>(value) * offset;
            value_ += static_cast<storage_type >(
                    (value - static_cast<storage_type >(value))*offset
            );
        }

        constexpr storage_type int_part() const noexcept{
            return value_ / offset;
        }
        constexpr storage_type fract_part() const noexcept{
            return value_ % (int_part() * offset);
        }

        constexpr number() = default;
        constexpr auto operator==(const same_precision_number &other) const noexcept {
            return value_ == other.value_;
        }
        constexpr auto operator<(const same_precision_number &other) const noexcept{
            return value_ < other.value_;
        }
        constexpr auto operator>(const same_precision_number &other) const noexcept{
            return value_ > other.value_;
        }
        constexpr auto operator-() const noexcept{
            same_precision_number n;
            n.value_ = -value_;
            return n;
        }
        constexpr auto operator-(const same_precision_number &other) const noexcept{
            same_precision_number n;
            n.value_ = value_-other.value_;
            return n;
        }
        constexpr auto operator+(const same_precision_number &other) const noexcept{
            same_precision_number n;
            n.value_ = value_+other.value_;
            return n;
        }
    private:
        storage_type value_ = 0;
    };

} // fp_math

namespace fp_math::test{
    static_assert(number<4>::offset == 10000);
    using n4 = number<4>;
    static_assert(n4{-33.42}.int_part() == -33);
    static_assert(n4{-33.42}.fract_part() == -4200);

    static_assert(constexpr_math::abs(n4{-42})==n4{42});

    static_assert(constexpr_math::equal(n4{42},n4{42.00001}));
}

#endif //GENERIC01_FP_MATH_H
