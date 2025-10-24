#include "glomap/processors/view_graph_manipulation.h"
#include "pyglomap/pybind11_extension.h"
#include "pyglomap/scene/colmap_bindings.h"
#include "pyglomap/scene/types.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

py::dict RunUpdateImagePairsConfig(
    ViewGraph& view_graph,
    const std::unordered_map<camera_t, Camera>& cameras,
    const std::unordered_map<image_t, Image>& images) {
  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  py::dict output;
  output["view_graph"] = view_graph;
  output["cameras"] = cameras;
  output["images"] = images;

  return output;
}

py::dict RunDecomposeRelPose(
    ViewGraph& view_graph,
    std::unordered_map<camera_t, Camera>& cameras,
    std::unordered_map<image_t, Image>& images) {
  ViewGraphManipulater::DecomposeRelPose(view_graph, cameras, images);

  py::dict output;
  output["view_graph"] = view_graph;
  output["cameras"] = cameras;
  output["images"] = images;

  return output;
}

void BindViewGraphManipulation(py::module& m) {
  m.def("update_image_pairs_config",
        &RunUpdateImagePairsConfig,
        "view_graph"_a,
        "cameras"_a,
        "images"_a,
        "Update image pairs config");

  m.def("decompose_rel_pose",
        &RunDecomposeRelPose,
        "view_graph"_a,
        "cameras"_a,
        "images"_a,
        "Decompose relative pose");
}
