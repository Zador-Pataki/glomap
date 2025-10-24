#include "glomap/processors/image_undistorter.h"
#include "glomap/scene/types_sfm.h"
#include "pyglomap/pybind11_extension.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <unordered_map>
#include <memory>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

void BindImageUndistorter(py::module& m) {
  m.def("undistort_images",
        [](std::unordered_map<camera_t, Camera>& cameras,
           std::unordered_map<image_t, Image>& images,
           bool clean_points) {
          UndistortImages(cameras, images, clean_points);
        },
        py::arg("cameras"),
        py::arg("images"),
        py::arg("clean_points") = true,
        "Undistorts feature points for all images using camera parameters, "
        "populating the 'features_undist' field on the Image objects.");
}