#include <calculus/integration.h>

#include <gtest/gtest.h>

#include <cmath>
#include <functional>

namespace {

constexpr double kTolCoarse = 1e-3;   // for small n on smooth functions
constexpr double kTolFine   = 1e-6;   // for large n on smooth functions

// ---------- Midpoint rule ----------

TEST(SimpsonTest, ConstantFunction) {
    // ∫₀¹ 5 dx = 5
    auto f = [](double) { return 5.0; };
    EXPECT_NEAR(integrate_simpsons(0.0, 1.0, 1, f),   5.0, kTolFine);
    EXPECT_NEAR(integrate_simpsons(0.0, 1.0, 100, f), 5.0, kTolFine);
}

}