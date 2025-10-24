#include "glomap/types.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>

#include "pyglomap/helpers.h"

namespace py = pybind11;

using namespace glomap;

void BindInlierThresholdOptions(py::module& m) {
  py::class_<InlierThresholdOptions, std::shared_ptr<InlierThresholdOptions>>
      PyInlierThresholdOptions(m, "InlierThresholdOptions");
  PyInlierThresholdOptions.def(py::init<>())
      .def_readwrite("max_angle_error",
                     &InlierThresholdOptions::max_angle_error,
                     "Threshold in degrees for global positioning (3D-2D matches).")
      .def_readwrite(
          "max_reprojection_error",
          &InlierThresholdOptions::max_reprojection_error,
          "Threshold for bundle adjustment (3D-2D matches).")
      .def_readwrite(
          "min_triangulation_angle",
          &InlierThresholdOptions::min_triangulation_angle,
          "Threshold in degrees for triangulation (3D-2D matches).")
      .def_readwrite("max_epipolar_error_E",
                     &InlierThresholdOptions::max_epipolar_error_E,
                     "Threshold for epipolar error with Essential matrix.")
      .def_readwrite("max_epipolar_error_F",
                     &InlierThresholdOptions::max_epipolar_error_F,
                     "Threshold for epipolar error with Fundamental matrix.")
      .def_readwrite("max_epipolar_error_H",
                     &InlierThresholdOptions::max_epipolar_error_H,
                     "Threshold for epipolar error with Homography matrix.")
      .def_readwrite("min_inlier_num",
                     &InlierThresholdOptions::min_inlier_num,
                     "Minimum number of inliers for edges.")
      .def_readwrite("min_inlier_ratio",
                     &InlierThresholdOptions::min_inlier_ratio,
                     "Minimum ratio of inliers for edges.")
      .def_readwrite("max_rotation_error",
                     &InlierThresholdOptions::max_rotation_error,
                     "Threshold in degrees for rotation averaging.")
      .def("__repr__", [](const InlierThresholdOptions& opts) {
        std::stringstream ss;
        ss << "InlierThresholdOptions(" << std::endl
           << "  max_angle_error=" << opts.max_angle_error << "," << std::endl
           << "  max_reprojection_error=" << opts.max_reprojection_error << ","
           << std::endl
           << "  min_triangulation_angle=" << opts.min_triangulation_angle
           << "," << std::endl
           << "  max_epipolar_error_E=" << opts.max_epipolar_error_E << ","
           << std::endl
           << "  max_epipolar_error_F=" << opts.max_epipolar_error_F << ","
           << std::endl
           << "  max_epipolar_error_H=" << opts.max_epipolar_error_H << ","
           << std::endl
           << "  min_inlier_num=" << opts.min_inlier_num << "," << std::endl
           << "  min_inlier_ratio=" << opts.min_inlier_ratio << "," << std::endl
           << "  max_rotation_error=" << opts.max_rotation_error << std::endl
           << ")";
        return ss.str();
      });

  MakeDataclass(PyInlierThresholdOptions);
}
