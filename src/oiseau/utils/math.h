#pragma once

#include <algorithm>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/jacobi.hpp>
#include <concepts>
#include <ranges>
#include <vector>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xmath.hpp>

namespace oiseau::utils {

template <class Container>
concept FloatingArrayLike =
    std::ranges::contiguous_range<Container> && std::is_floating_point_v<typename Container::value_type>;

template <std::floating_point Real, FloatingArrayLike Container>
Container jacobi_p(unsigned n, Real alpha, Real beta, Container v) {
    using boost::math::tgamma, boost::math::jacobi;
    Real norm = std::pow(2, alpha + beta + 1) / (2 * n + alpha + beta + 1);
    norm *= tgamma(n + alpha + 1) * tgamma(n + beta + 1);
    norm /= (tgamma(n + 1) * tgamma(n + alpha + beta + 1));
    auto partial = [n, alpha, beta, norm](auto &k) { k = jacobi(n, alpha, beta, k) / std::sqrt(norm); };
    std::for_each(v.begin(), v.end(), partial);
    return v;
}

template <std::floating_point Real, FloatingArrayLike Container>
Container grad_jacobi_p(int n, Real alpha, Real beta, Container v) {
    if (n == 0) {
        std::for_each(v.begin(), v.end(), [](auto &elm) { elm = 0; });
        return v;
    }
    double norm = std::sqrt(n * (n + alpha + beta + 1));
    auto output = jacobi_p(n - 1, alpha + 1, beta + 1, v);
    std::for_each(output.begin(), output.end(), [norm](auto &k) { k *= norm; });
    return output;
}

template <std::floating_point T = double, std::floating_point Real>
std::pair<xt::xarray<T>, xt::xarray<T>> jacobi_gq(unsigned n, Real alpha, Real beta) {
    if (n == 0) {
        xt::xarray<T> x = {(alpha - beta) / (alpha + beta + 2)};
        xt::xarray<T> w = {2};
        return make_pair(std::move(w), std::move(x));
    }
    xt::xarray<T> h1 = 2 * xt::linspace<Real>(0, n, n + 1) + alpha + beta;
    auto h1s = xt::view(h1, xt::range(0, n));
    auto lins = xt::arange<Real>(1, n + 1);
    xt::xarray<T> m =
        xt::diag(-1.0 / 2.0 * (std::pow(alpha, 2) - std::pow(beta, 2)) / (h1 + 2) / h1) +
        xt::diag(2. / (h1s + 2) *
                     xt::sqrt(lins * (lins + alpha + beta) * (lins + alpha) * (lins + beta) / (h1s + 1) / (h1s + 3)),
                 1);
    if (alpha + beta == 0)
        m(0, 0) = 0;
    m += xt::transpose(m);
    auto [d, v] = xt::linalg::eigh(m);
    using boost::math::tgamma;
    Real cte = std::pow(2, (alpha + beta + 1)) / (alpha + beta + 1) * tgamma(alpha + 1) * tgamma(beta + 1) /
               tgamma(alpha + beta + 1);
    xt::xarray<T> w = cte * xt::square(xt::view(v, 0, xt::all())), x = d;
    return make_pair(std::move(x), std::move(w));
}

template <std::floating_point T = double, std::floating_point Real>
xt::xarray<T> jacobi_gl(unsigned n, Real alpha, Real beta) {
    auto [x, _] = jacobi_gq(n - 2, alpha + 1.0, beta + 1.0);
    return xt::concatenate(xt::xtuple(-xt::ones<T>({1}), x, xt::ones<T>({1})));
}

} // namespace oiseau::utils
