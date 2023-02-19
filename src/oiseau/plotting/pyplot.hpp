#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <xtensor/xarray.hpp>

namespace py = pybind11;
using namespace py::literals;

namespace pybind11::detail {
template <typename T>
struct type_caster<xt::xarray<T>> {
 public:
  PYBIND11_TYPE_CASTER(xt::xarray<T>, const_name("xarray"));
  static handle cast(xt::xarray<T> &src, return_value_policy, handle) {
    auto v = py::array(src.size(), src.data(), py::capsule([]() {}));
    v.resize(src.shape());
    return v.release();
  }
};
}  // namespace pybind11::detail

namespace plt {

using scoped_interpreter = py::scoped_interpreter;

inline auto plt() { return py::module_::import("matplotlib.pyplot"); }

#pragma GCC visibility push(hidden)

class AxesSubPlot {
 public:
  explicit AxesSubPlot(py::object axes) : m_obj(axes) {}

  template <typename... Args>
  auto scatter(Args &&...args) {
    return m_obj.attr("scatter")(std::forward<Args>(args)...);
  };

  template <typename... Args>
  auto plot(Args &&...args) {
    return m_obj.attr("plot")(std::forward<Args>(args)...);
  }

 private:
  py::object m_obj;
};

class Figure {
 public:
  explicit Figure(py::object fig) : m_obj(fig) {}

  template <typename... Args>
  AxesSubPlot add_subplot(Args &&...args) {
    return AxesSubPlot(m_obj.attr("add_subplot")(std::forward<Args>(args)...));
  }

 private:
  py::object m_obj;
};

#pragma GCC visibility pop

template <typename... Args>
auto scatter(Args &&...args) {
  return plt().attr("scatter")(std::forward<Args>(args)...);
};

template <typename... Args>
auto show(Args &&...args) {
  return plt().attr("show")(std::forward<Args>(args)...);
}

template <typename... Args>
auto plot(Args &&...args) {
  return plt().attr("plot")(std::forward<Args>(args)...);
}

template <typename... Args>
Figure figure(Args &&...args) {
  return Figure((plt().attr("figure")(std::forward<Args>(args)...)));
}

template <typename... Args>
std::pair<Figure, AxesSubPlot> subplots(Args &&...args) {
  py::tuple res = plt().attr("subplots")(std::forward<Args>(args)...);
  return {Figure(res[0]), AxesSubPlot(res[1])};
}

}  // namespace plt
