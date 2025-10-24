// pyglomap/processors/image_pair_inliers.cc

#include "glomap/processors/image_pair_inliers.h" // The function declaration
#include "glomap/scene/types_sfm.h"               // Types like ViewGraph, Camera, Image
#include "glomap/types.h"            // InlierThresholdOptions

#include "pyglomap/helpers.h"
#include "pyglomap/pybind11_extension.h" // Assuming this is needed for custom types
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

// The function is a void function that modifies the ViewGraph in place.
void ImagePairsInlierCountWrapper(
    ViewGraph& view_graph,
    const std::unordered_map<camera_t, Camera>& cameras,
    const std::unordered_map<image_t, Image>& images,
    const InlierThresholdOptions& options,
    bool clean_inliers) {
  
  ImagePairsInlierCount(view_graph, cameras, images, options, clean_inliers);
}

void BindImagePairInliers(py::module& m) {
  m.def("image_pairs_inlier_count",
        &ImagePairsInlierCountWrapper,
        py::arg("view_graph"),
        py::arg("cameras"),
        py::arg("images"),
        py::arg("options"),
        py::arg("clean_inliers") = true, // Set default to true as per your typical needs
        "Computes the number of inliers for each image pair in the view graph, "
        "modifying the ViewGraph object in place.");
}