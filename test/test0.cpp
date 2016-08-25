/* Copyright 2009-2016 Francesco Biscani (bluescarni@gmail.com)

This file is part of the mp++ library.

The mp++ library is free software; you can redistribute it and/or modify
it under the terms of either:

  * the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.

or

  * the GNU General Public License as published by the Free Software
    Foundation; either version 3 of the License, or (at your option) any
    later version.

or both in parallel, as here.

The mp++ library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received copies of the GNU General Public License and the
GNU Lesser General Public License along with the mp++ library.  If not,
see https://www.gnu.org/licenses/. */

#include <atomic>
#include <limits>
#include <random>
#include <thread>
#include <tuple>
#include <type_traits>

#include <mp++.hpp>

#include "test_utils.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

static int ntries = 1000;

using namespace mppp;
using namespace mppp_test;

using int_types = std::tuple<char, signed char, unsigned char, short, unsigned short, int, unsigned, long,
                             unsigned long, long long, unsigned long long>;

struct int_ctor_tester {
    template <typename Int>
    inline void operator()(const Int &) const
    {
        REQUIRE((std::is_constructible<integer, Int>::value));
        REQUIRE(lex_cast(Int(0)) == lex_cast(integer{Int(0)}));
        auto constexpr min = std::numeric_limits<Int>::min(), max = std::numeric_limits<Int>::max();
        REQUIRE(lex_cast(min) == lex_cast(integer{min}));
        REQUIRE(lex_cast(max) == lex_cast(integer{max}));
        std::atomic<bool> fail(false);
        auto f = [&fail](unsigned n) {
            std::uniform_int_distribution<Int> dist(min, max);
            std::mt19937 eng(static_cast<std::mt19937::result_type>(n));
            for (auto i = 0; i < ntries; ++i) {
                auto tmp = dist(eng);
                if (lex_cast(tmp) != lex_cast(integer{tmp})) {
                    fail.store(false);
                }
            }
        };
        std::thread t0(f, 0u), t1(f, 1u), t2(f, 2u), t3(f, 3u);
        t0.join();
        t1.join();
        t2.join();
        t3.join();
        REQUIRE(!fail.load());
    }
};

TEST_CASE("integral constructors")
{
    tuple_for_each(int_types{}, int_ctor_tester{});
    // Some testing for bool.
    REQUIRE((std::is_constructible<integer, bool>::value));
    REQUIRE((lex_cast(integer{false}) == "0"));
    REQUIRE((lex_cast(integer{true}) == "1"));
}

using fp_types = std::tuple<float, double
#if defined(MPPP_WITH_LONG_DOUBLE)
                            ,
                            long double
#endif
                            >;

struct fp_ctor_tester {
    template <typename Float>
    inline void operator()(const Float &) const
    {
        REQUIRE((std::is_constructible<integer, Float>::value));
        REQUIRE(lex_cast(Float(0)) == lex_cast(integer{Float(0)}));
    }
};

TEST_CASE("floating-point constructors")
{
    tuple_for_each(fp_types{}, fp_ctor_tester{});
}