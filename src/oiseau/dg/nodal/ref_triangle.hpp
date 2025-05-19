#pragma once

#include "oiseau/dg/nodal/ref_element.hpp"
#include "xtensor/core/xtensor_forward.hpp"

/**
 * @file ref_triangle.hpp
 * @brief Defines the reference triangle element used in nodal Discontinuous Galerkin methods.
 *
 * This file contains the declaration of the `RefTriangle` class, which represents
 * a reference triangular element, and associated helper functions in the `detail`
 * namespace for generating nodes, basis functions, and performing coordinate transformations.
 */

namespace oiseau::dg::nodal {

/**
 * @class RefTriangle
 * @brief Represents a reference triangular element for Discontinuous Galerkin methods.
 *
 * The reference triangle is defined in (r,s) coordinates with vertices at
 * (-1,-1), (1,-1), and (-1,1). This class computes and stores properties
 * like nodal distribution, Vandermonde matrix, and differentiation matrices
 * for a given polynomial order.
 */
class RefTriangle : public RefElement {
 public:
  /**
   * @brief Constructs a RefTriangle object of a specific polynomial order.
   * @param order The polynomial order for the basis functions on the triangle.
   *              This determines the number of nodes and the accuracy of the approximation.
   */
  explicit RefTriangle(unsigned order);

 private:
  /**
   * @brief Computes the Vandermonde matrix for the reference triangle.
   *
   * The Vandermonde matrix V has entries V_ij = phi_j(r_i, s_i), where
   * (r_i, s_i) are the nodal points and phi_j are the basis functions.
   *
   * @param rs An xt::xarray<double> of shape (N_points, 2) containing the (r,s) coordinates
   *           of the points at which to evaluate the basis functions.
   * @return An xt::xarray<double> of shape (N_points, N_basis) representing the Vandermonde matrix.
   *         N_basis is the number of basis functions, (order+1)*(order+2)/2.
   */
  xt::xarray<double> vandermonde(const xt::xarray<double> &rs) const;

  /**
   * @brief Computes the gradient of the Vandermonde matrix.
   *
   * This matrix contains the gradients of the basis functions evaluated at the given points.
   * The output G_V has entries G_V_ijk = d(phi_j)/dx_k (r_i, s_i), where k corresponds to
   * derivatives with respect to r (k=0) and s (k=1).
   *
   * @param rs An xt::xarray<double> of shape (N_points, 2) containing the (r,s) coordinates
   *           of the points at which to evaluate the gradients of the basis functions.
   * @return An xt::xarray<double> of shape (N_points, N_basis, 2) representing the
   *         gradient of the Vandermonde matrix. The last dimension corresponds to dr and ds.
   */
  xt::xarray<double> grad_vandermonde(const xt::xarray<double> &rs) const;

  /**
   * @brief Computes the differentiation matrices (gradient operator) Dr and Ds.
   *
   * These matrices allow computing the derivatives of a function (represented by its
   * nodal values) with respect to r and s.
   * Dr = V_r * V_inv and Ds = V_s * V_inv, where V_r and V_s are parts of the
   * gradient Vandermonde matrix at the element nodes, and V_inv is the inverse
   * of the Vandermonde matrix at the element nodes.
   * The implementation computes Dr^T = V_inv^T * V_r^T and Ds^T = V_inv^T * V_s^T.
   *
   * @param v The Vandermonde matrix (xt::xarray<double> of shape (N_nodes, N_basis)).
   * @param gv The gradient Vandermonde matrix (xt::xarray<double> of shape (N_nodes, N_basis, 2)).
   * @return An xt::xarray<double> of shape (N_nodes, N_basis, 2) where the slices
   *         [:, :, 0] and [:, :, 1] are the differentiation matrices Dr and Ds, respectively.
   *         Note: The returned matrices are such that (Dr * u)_i approximates d(u)/dr at node i.
   *         Here, N_nodes = N_basis = (order+1)*(order+2)/2.
   */
  xt::xarray<double> grad_operator(const xt::xarray<double> &v, const xt::xarray<double> &gv);
};

/**
 * @namespace detail
 * @brief Contains internal helper functions for RefTriangle implementation.
 *
 * These functions are not intended for direct use outside of the RefTriangle class
 * and its associated implementation files.
 */
namespace detail {

/**
 * @brief Converts points from (r,s) coordinates to (a,b) collapsed coordinates.
 *
 * The (r,s) coordinates define a bi-unit right triangle with vertices at
 * (-1,-1), (1,-1), (-1,1). The (a,b) coordinates are often used for
 * constructing basis functions on triangles, e.g., via a Duffy-like transformation.
 * a = 2*(1+r)/(1-s) - 1
 * b = s
 * Special handling for s=1 singularity (a=-1).
 *
 * @param rs An xt::xarray<double> of shape (N_points, 2) containing (r,s) coordinates.
 * @return An xt::xarray<double> of shape (N_points, 2) containing the corresponding (a,b)
 * coordinates.
 */
xt::xarray<double> rs_to_ab(const xt::xarray<double> &rs);

/**
 * @brief Generates nodal points on an equilateral triangle using a Warp & Blend technique.
 *
 * These points are then typically transformed to the (r,s) reference triangle.
 * The method aims to provide well-conditioned nodal sets.
 *
 * @param order The polynomial order, determining the number of points.
 *              Number of points generated is (order+1)*(order+2)/2.
 * @return An xt::xarray<double> of shape (N_points, 2) containing (x,y) coordinates
 *         of the nodes on an equilateral triangle.
 */
xt::xarray<double> generate_triangle_nodes(unsigned order);

/**
 * @brief Converts (x,y) coordinates from an equilateral triangle to (r,s) reference coordinates.
 *
 * The specific equilateral triangle definition used in `generate_triangle_nodes` is assumed.
 * The (r,s) coordinates are for the bi-unit right triangle with vertices (-1,-1), (1,-1), (-1,1).
 *
 * @param xy An xt::xarray<double> of shape (N_points, 2) containing (x,y) coordinates
 *           on the equilateral triangle.
 * @return An xt::xarray<double> of shape (N_points, 2) containing the corresponding (r,s)
 * coordinates.
 */
xt::xarray<double> equilateral_xy_to_rs(const xt::xarray<double> &xy);

/**
 * @brief Computes a 1D warp factor used in the Warp & Blend node generation.
 *
 * This function is part of the `generate_triangle_nodes` algorithm. It warps
 * equispaced points towards Gauss-Lobatto-Legendre points to improve node distribution.
 *
 * @param order The polynomial order.
 * @param rs An xt::xarray<double> of shape (N_points_1D) representing 1D coordinates
 *           (typically along an edge or median direction) to be warped.
 * @return An xt::xarray<double> of shape (N_points_1D) containing the warp values.
 */
xt::xarray<double> warp_factor(unsigned order, const xt::xarray<double> &rs);

/**
 * @brief Computes the value of a 2D orthonormal basis function on the reference triangle.
 *
 * The basis function is defined using (a,b) collapsed coordinates and Jacobi polynomials.
 * Formula: sqrt(2) * P_i^{0,0}(a) * P_j^{2i+1,0}(b) * (1-b)^i
 * (Note: (1-b)^i is equivalent to (2 * (1-b)/2)^i, matching common forms with ((1-b)/2)^i with a
 * 2^i factor)
 *
 * @param ab An xt::xarray<double> of shape (N_points, 2) containing (a,b) coordinates.
 * @param i The polynomial degree index for the 'a' coordinate component.
 * @param j The polynomial degree index for the 'b' coordinate component.
 * @return An xt::xarray<double> of shape (N_points) containing the basis function values.
 */
xt::xarray<double> basis_function(const xt::xarray<double> &ab, int i, int j);

/**
 * @brief Computes the gradient (dr, ds components) of a 2D orthonormal basis function.
 *
 * The gradient is computed with respect to the (r,s) coordinates of the reference triangle.
 * It uses the chain rule, transforming derivatives from (a,b) coordinates to (r,s) coordinates.
 * The basis functions and their derivatives are consistent with those in Hesthaven & Warburton,
 * "Nodal Discontinuous Galerkin Methods" (scaled by sqrt(2)*2^i).
 *
 * @param ab An xt::xarray<double> of shape (N_points, 2) containing (a,b) coordinates.
 *           These are derived from (r,s) coordinates via `rs_to_ab`.
 * @param i The polynomial degree index for the 'a' coordinate component.
 * @param j The polynomial degree index for the 'b' coordinate component.
 * @return An xt::xarray<double> of shape (N_points, 2) containing the (d/dr, d/ds)
 *         gradients of the basis function.
 */
xt::xarray<double> grad_basis_function(const xt::xarray<double> &ab, int i, int j);

};  // namespace detail
}  // namespace oiseau::dg::nodal
