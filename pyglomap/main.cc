#include "glomap/scene/types_sfm.h"

#include "pyglomap/helpers.h"
#include "pyglomap/pybind11_extension.h"
#include <ceres/version.h>
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

// using namespace glomap;
namespace py = pybind11;
using namespace glomap;

// Opaque types
using ImageMap = std::unordered_map<image_t, Image>;
PYBIND11_MAKE_OPAQUE(ImageMap);
using TrackMap = std::unordered_map<track_t, Track>;
PYBIND11_MAKE_OPAQUE(TrackMap);
using ImagePairMap = std::unordered_map<image_pair_t, ImagePair>;
PYBIND11_MAKE_OPAQUE(ImagePairMap);
using CameraMap = std::unordered_map<camera_t, glomap::Camera>;
PYBIND11_MAKE_OPAQUE(CameraMap);


void BindOptim(py::module& m);
void BindScene(py::module& m);
void BindPipelines(py::module& m);
void BindDatabaseConverter(py::module& m);
void BindProcessors(py::module& m);

PYBIND11_MODULE(pyglomap, m) {
  m.doc() = "GLOMAP plugin";
  // #ifdef VERSION_INFO
  //   m.attr("__version__") = py::str(VERSION_INFO);
  // #else
  // #endif
  m.attr("__version__") = py::str("dev");

  BindOptim(m);
  BindScene(m);
  BindPipelines(m);
  BindDatabaseConverter(m);
  BindProcessors(m);
}
