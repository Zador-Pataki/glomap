#include "glomap/processors/relpose_filter.h"

#include "pyglomap/pybind11_extension.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

void BindRelPoseFilter(py::module& m) {
  m.def("filter_rotations",
        &RelPoseFilter::FilterRotations,
        "view_graph"_a,
        "images"_a,
        "max_angle"_a = 5.0,
        "Filter relative pose based on rotation angle");
  m.def("filter_inlier_num",
        &RelPoseFilter::FilterInlierNum,
        "view_graph"_a,
        "min_inlier_num"_a = 30,
        "Filter relative pose based on number of inliers");
  m.def("filter_inlier_ratio",
        &RelPoseFilter::FilterInlierRatio,
        "view_graph"_a,
        "min_inlier_ratio"_a = 0.25,
        "Filter relative pose based on rate of inliers");
}
