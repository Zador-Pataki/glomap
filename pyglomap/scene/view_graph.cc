#include "glomap/scene/view_graph.h"

#include <memory>
#include <optional>
#include <sstream>

#include "pyglomap/helpers.h"
#include "pyglomap/pybind11_extension.h"
#include "pyglomap/scene/types.h"
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

void BindViewGraph(py::module& m) {
  py::class_<ViewGraph, std::shared_ptr<ViewGraph>> PyViewGraph(m, "ViewGraph");
  PyViewGraph.def(py::init<>())
      // Revert this back to readonly. This works.
      .def_property_readonly(
          "image_pairs",
          [](const ViewGraph& self)
              -> const std::unordered_map<image_pair_t, ImagePair>& {
            return self.image_pairs;
          },
          py::return_value_policy::reference_internal,
          "The (read-only) map of image pairs.")

      // VVV ADD THIS METHOD VVV
      .def("add_pair",
        [](ViewGraph& self, const ImagePair& pair) {
          self.image_pairs.emplace(pair.pair_id, pair); // <-- GOOD LINE
        },
        "pair"_a,
        "Add an ImagePair to the view graph.")
      // ^^^ ADD THIS METHOD ^^^

      .def("__repr__", [](const ViewGraph& self) {
        std::ostringstream ss;
        ss << "ViewGraph(" << self.num_images << ", " << self.num_pairs << ")";
        return ss.str();
      });
}