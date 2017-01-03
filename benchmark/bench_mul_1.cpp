/* Copyright 2016-2017 Francesco Biscani (bluescarni@gmail.com)

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

#include <mp++.hpp>
#include <random>

#include "benchmark_utils.hpp"

using namespace mppp;
using namespace mppp_bench;

using integer = mp_integer<1>;

std::mt19937 rng;

NONIUS_BENCHMARK("mppp half-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_mppp_half<integer>(meter, rng); });
NONIUS_BENCHMARK("mppp half-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_mppp_half<integer>(meter, rng); });
NONIUS_BENCHMARK("mppp 1-1-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_mppp<integer>(meter, rng, 1, 1); });
NONIUS_BENCHMARK("mppp 2-1-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_mppp<integer>(meter, rng, 2, 1); });
NONIUS_BENCHMARK("mppp 2-2-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_mppp<integer>(meter, rng, 2, 2); });
NONIUS_BENCHMARK("mppp 1-1-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_mppp<integer>(meter, rng, 1, 1); });
NONIUS_BENCHMARK("mppp 2-1-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_mppp<integer>(meter, rng, 2, 1); });
NONIUS_BENCHMARK("mppp 2-2-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_mppp<integer>(meter, rng, 2, 2); });

NONIUS_BENCHMARK("flint half-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_fmpz_half(meter, rng); });
NONIUS_BENCHMARK("flint half-limb signed vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_fmpz_half(meter, rng); });

NONIUS_BENCHMARK("piranha half-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_piranha_half(meter, rng); });
NONIUS_BENCHMARK("piranha half-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_piranha_half(meter, rng); });
NONIUS_BENCHMARK("piranha 1-1-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_piranha(meter, rng, 1, 1); });
NONIUS_BENCHMARK("piranha 2-1-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_piranha(meter, rng, 2, 1); });
NONIUS_BENCHMARK("piranha 2-2-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_piranha(meter, rng, 2, 2); });
NONIUS_BENCHMARK("piranha 1-1-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_piranha(meter, rng, 1, 1); });
NONIUS_BENCHMARK("piranha 2-1-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_piranha(meter, rng, 2, 1); });
NONIUS_BENCHMARK("piranha 2-2-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_piranha(meter, rng, 2, 2); });

NONIUS_BENCHMARK("gmp half-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_gmp_half(meter, rng); });
NONIUS_BENCHMARK("gmp half-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_gmp_half(meter, rng); });
NONIUS_BENCHMARK("gmp 1-1-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_gmp(meter, rng, 1, 1); });
NONIUS_BENCHMARK("gmp 2-1-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_gmp(meter, rng, 2, 1); });
NONIUS_BENCHMARK("gmp 2-2-limb unsigned vector multiplication",
                 [](nonius::chronometer meter) { umul_vec_gmp(meter, rng, 2, 2); });
NONIUS_BENCHMARK("gmp 1-1-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_gmp(meter, rng, 1, 1); });
NONIUS_BENCHMARK("gmp 2-1-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_gmp(meter, rng, 2, 1); });
NONIUS_BENCHMARK("gmp 2-2-limb signed vector multiplication",
                 [](nonius::chronometer meter) { smul_vec_gmp(meter, rng, 2, 2); });
