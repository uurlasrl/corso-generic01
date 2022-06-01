//
// Created by Domenico Neri on 01/06/22.
//

#ifndef GENERIC01_CONSTEXPR_MATH_H
#define GENERIC01_CONSTEXPR_MATH_H

#include <cstdlib>
#include <stdexcept>
#include <type_traits>

namespace constexpr_math{
    constexpr auto pi = 3.14159265358979323846264;
    constexpr auto epsilon = 0.0001;

    template<typename number_t>
    constexpr number_t abs(const number_t &value){
        return value > number_t{0} ? value : -value;
    }

    template<typename number_t> //number_t epsilon_v = number_t{epsilon}
    constexpr bool equal(const number_t &a, const number_t &b){
        return abs(a - b) < epsilon;
    }

    template<typename number_t>
    constexpr number_t rad(const number_t &deg){
        return deg * number_t{pi} / number_t{180.0};
    }
    static_assert(equal(rad(90.0), pi / 2));

    template<typename number_t>
    constexpr number_t cos(const number_t &rad){
        const auto n = 20; // higher n = better precision
        number_t sum = 1;
        number_t t = 1;

        // Approximate using Taylor series
        for (auto i = 1; i <= n; ++i){
            t *= -rad * rad / (2 * i * (2 * i - 1));
            sum += t;
        }

        return sum;
    }

    static_assert(equal(cos(0), 1));
    static_assert(equal(cos(rad(60.0)), 0.5));

    template<unsigned short precision_v, typename number_t>
    class fast_cos{
    public:
        static constexpr auto precision = precision_v;
        static constexpr auto nof_values = precision * 360;

        number_t cos_table[nof_values];

        constexpr fast_cos() : cos_table() {
            for (auto i = size_t{0}; i < nof_values; ++i){
                cos_table[i] = constexpr_math::cos(rad(static_cast<number_t>(i) / precision));
            }
        }

        constexpr number_t value_at(unsigned table_index) const {
            if (table_index / precision > 360)
                throw std::runtime_error ("Angle must be under 360 degrees");

            return cos_table[table_index];
        }

        constexpr number_t cos(const number_t &deg) const {
            // todo: error checking!
            return value_at(static_cast<unsigned>(deg * precision));
        }
    };

    static_assert(equal(fast_cos<10, double>{}.cos(60), 0.5));

    template<typename number_t>
    constexpr decltype(auto) pow(number_t &&value, unsigned exp){
        typename std::remove_cvref<number_t>::type result = 1;
        for (auto i = unsigned{0}; i < exp; ++i){
            result *= value;
        }
        return result;
    }
}


#endif //GENERIC01_CONSTEXPR_MATH_H
