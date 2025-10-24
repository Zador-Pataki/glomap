#include "glomap/estimators/relpose_estimation.h"
#include "glomap/processors/image_undistorter.h"
#include "pyglomap/pybind11_extension.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <PoseLib/types.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

py::dict RunEstimateRelativePoses(
    ViewGraph& view_graph,
    std::unordered_map<camera_t, Camera>& cameras,
    std::unordered_map<image_t, Image>& images) {
  // Construct the options with default values
  RelativePoseEstimationOptions options;

  // Undistort images
  UndistortImages(cameras, images, true);

  // Estimate relative poses
  EstimateRelativePoses(view_graph, cameras, images, options);

  py::dict output;
  output["view_graph"] = view_graph;
  output["cameras"] = cameras;
  output["images"] = images;

  return output;
}

void BindRelativePoseEstimation(py::module& m) {
  m.def("run_relative_pose_estimation",
        &RunEstimateRelativePoses,
        "view_graph"_a,
        "cameras"_a,
        "images"_a,
        "Run relative pose estimation with default options");
}
