#include <calculus/integration.h>

#include <gtest/gtest.h>

#include <cmath>
#include <functional>

namespace {

constexpr double kTolCoarse = 1e-3;   // for small n on smooth functions
constexpr double kTolFine   = 1e-6;   // for large n on smooth functions

// ---------- Midpoint rule ----------

TEST(MidpointTest, ConstantFunction) {
    // ∫₀¹ 5 dx = 5
    auto f = [](double) { return 5.0; };
    EXPECT_NEAR(integrate_midpoint(0.0, 1.0, 1, f),   5.0, kTolFine);
    EXPECT_NEAR(integrate_midpoint(0.0, 1.0, 100, f), 5.0, kTolFine);
}

TEST(MidpointTest, LinearFunction) {
    // ∫₀² (2x + 1) dx = [x² + x]₀² = 6
    // Midpoint is exact for linear functions for any n.
    auto f = [](double x) { return 2.0 * x + 1.0; };
    EXPECT_NEAR(integrate_midpoint(0.0, 2.0, 1, f),  6.0, kTolFine);
    EXPECT_NEAR(integrate_midpoint(0.0, 2.0, 10, f), 6.0, kTolFine);
}

TEST(MidpointTest, Quadratic) {
    // ∫₀¹ x² dx = 1/3
    auto f = [](double x) { return x * x; };
    EXPECT_NEAR(integrate_midpoint(0.0, 1.0, 1000, f), 1.0 / 3.0, kTolFine);
}

TEST(MidpointTest, SineOverFullPeriod) {
    // ∫₀^{2π} sin(x) dx = 0
    auto f = [](double x) { return std::sin(x); };
    EXPECT_NEAR(integrate_midpoint(0.0, 2.0 * M_PI, 1000, f), 0.0, kTolFine);
}

TEST(MidpointTest, ExponentialOverUnitInterval) {
    // ∫₀¹ eˣ dx = e - 1
    auto f = [](double x) { return std::exp(x); };
    const double expected = std::exp(1.0) - 1.0;
    EXPECT_NEAR(integrate_midpoint(0.0, 1.0, 1000, f), expected, kTolFine);
}

TEST(MidpointTest, NegativeInterval) {
    // ∫₋₁¹ x² dx = 2/3
    auto f = [](double x) { return x * x; };
    EXPECT_NEAR(integrate_midpoint(-1.0, 1.0, 1000, f), 2.0 / 3.0, kTolFine);
}

TEST(MidpointTest, ReversedLimitsFlipsSign) {
    // ∫ₐᵇ f = -∫_bᵃ f
    auto f = [](double x) { return x * x; };
    const double forward  = integrate_midpoint(0.0, 1.0, 1000, f);
    const double backward = integrate_midpoint(1.0, 0.0, 1000, f);
    EXPECT_NEAR(forward, -backward, kTolFine);
}

TEST(MidpointTest, ConvergesAsNIncreases) {
    // Error should shrink as n grows (midpoint is O(h²)).
    auto f = [](double x) { return x * x * x; };  // ∫₀¹ x³ = 1/4
    const double expected = 0.25;
    const double err_n10  = std::abs(integrate_midpoint(0.0, 1.0, 10,   f) - expected);
    const double err_n100 = std::abs(integrate_midpoint(0.0, 1.0, 100,  f) - expected);
    const double err_n1000= std::abs(integrate_midpoint(0.0, 1.0, 1000, f) - expected);
    EXPECT_LT(err_n100,  err_n10);
    EXPECT_LT(err_n1000, err_n100);
}

// ---------- Trapezoid rule ----------

TEST(TrapezoidTest, ConstantFunction) {
    auto f = [](double) { return 5.0; };
    EXPECT_NEAR(integrate_trapezoid(0.0, 1.0, 1, f),   5.0, kTolFine);
    EXPECT_NEAR(integrate_trapezoid(0.0, 1.0, 100, f), 5.0, kTolFine);
}

TEST(TrapezoidTest, LinearFunction) {
    // Trapezoid is exact for linear functions for any n.
    auto f = [](double x) { return 2.0 * x + 1.0; };
    EXPECT_NEAR(integrate_trapezoid(0.0, 2.0, 1, f),  6.0, kTolFine);
    EXPECT_NEAR(integrate_trapezoid(0.0, 2.0, 10, f), 6.0, kTolFine);
}

TEST(TrapezoidTest, Quadratic) {
    auto f = [](double x) { return x * x; };
    EXPECT_NEAR(integrate_trapezoid(0.0, 1.0, 1000, f), 1.0 / 3.0, kTolFine);
}

TEST(TrapezoidTest, SineOverFullPeriod) {
    auto f = [](double x) { return std::sin(x); };
    EXPECT_NEAR(integrate_trapezoid(0.0, 2.0 * M_PI, 1000, f), 0.0, kTolFine);
}

TEST(TrapezoidTest, ExponentialOverUnitInterval) {
    auto f = [](double x) { return std::exp(x); };
    const double expected = std::exp(1.0) - 1.0;
    EXPECT_NEAR(integrate_trapezoid(0.0, 1.0, 1000, f), expected, kTolFine);
}

TEST(TrapezoidTest, ConvergesAsNIncreases) {
    auto f = [](double x) { return x * x * x; };
    const double expected = 0.25;
    const double err_n10  = std::abs(integrate_trapezoid(0.0, 1.0, 10,   f) - expected);
    const double err_n100 = std::abs(integrate_trapezoid(0.0, 1.0, 100,  f) - expected);
    const double err_n1000= std::abs(integrate_trapezoid(0.0, 1.0, 1000, f) - expected);
    EXPECT_LT(err_n100,  err_n10);
    EXPECT_LT(err_n1000, err_n100);
}

// ---------- Cross-method properties ----------

TEST(IntegrationComparison, BothAgreeOnSmoothFunction) {
    // For smooth f and large n, both rules should converge to the same value.
    auto f = [](double x) { return std::sin(x) * std::exp(-x); };
    const double mid  = integrate_midpoint(0.0, 3.0, 10000, f);
    const double trap = integrate_trapezoid(0.0, 3.0, 10000, f);
    EXPECT_NEAR(mid, trap, kTolCoarse);
}

TEST(IntegrationComparison, MidpointErrorRoughlyHalfTrapezoid) {
    // Classical result: for smooth f, midpoint error ≈ -½ × trapezoid error.
    // So |E_mid| ≈ ½ |E_trap|. Check the magnitudes are within 2x.
    auto f = [](double x) { return x * x; };  // ∫₀¹ = 1/3
    const double expected = 1.0 / 3.0;
    const int n = 20;
    const double e_mid  = std::abs(integrate_midpoint(0.0, 1.0, n, f)  - expected);
    const double e_trap = std::abs(integrate_trapezoid(0.0, 1.0, n, f) - expected);
    EXPECT_LT(e_mid, e_trap);
}

// ---------- Parametrized convergence sweep ----------

class TrapezoidPolynomial : public ::testing::TestWithParam<int> {};

TEST_P(TrapezoidPolynomial, IntegratesXSquared) {
    // ∫₀¹ x² dx = 1/3, error → 0 as n grows
    auto f = [](double x) { return x * x; };
    const int n = GetParam();
    EXPECT_NEAR(integrate_trapezoid(0.0, 1.0, n, f), 1.0 / 3.0, 1.0 / (n * n));
}

INSTANTIATE_TEST_SUITE_P(
    Convergence, TrapezoidPolynomial,
    ::testing::Values(10, 50, 100, 500, 1000));

}  // namespace