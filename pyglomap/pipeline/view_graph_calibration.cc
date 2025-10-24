#include "glomap/estimators/view_graph_calibration.h"
#include "pyglomap/pybind11_extension.h"
#include "pyglomap/scene/colmap_bindings.h"
#include "pyglomap/scene/types.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

py::dict RunViewGraphCalibration(
    ViewGraph& view_graph,
    std::unordered_map<camera_t, Camera>& cameras,
    std::unordered_map<image_t, Image>& images,
    const ViewGraphCalibratorOptions& options) {
  ViewGraphCalibrator vgcalib_engine(options);
  if (!vgcalib_engine.Solve(view_graph, cameras, images)) {
    throw std::runtime_error("Failed to solve view graph calibration.");
  }

  py::dict output;
  output["view_graph"] = view_graph;
  output["cameras"] = cameras;
  output["images"] = images;

  return output;
}

void BindViewGraphCalibration(py::module& m) {
  m.def("run_view_graph_calibration",
        &RunViewGraphCalibration,
        "view_graph"_a,
        "cameras"_a,
        "images"_a,
        py::arg_v("options",
                  ViewGraphCalibratorOptions(),
                  "ViewGraphCalibratorOptions()"),
        "Run view graph calibration");
}
