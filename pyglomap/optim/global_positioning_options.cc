#include "glomap/estimators/global_positioning.h"

#include <memory>
#include <sstream>

#include "pyglomap/helpers.h"
#include "pyglomap/pybind11_extension.h"
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

using namespace glomap;
using namespace pybind11::literals;
namespace py = pybind11;

void BindGlobalPositionerOptions(py::module& m) {
  // Bind GlobalPositionerOptions
  py::class_<GlobalPositionerOptions, std::shared_ptr<GlobalPositionerOptions>>
      PyGlobalPositionerOptions(m, "GlobalPositionerOptions");

  PyGlobalPositionerOptions.def(py::init<>())
      .def_readwrite("thres_loss_function",
                     &GlobalPositionerOptions::thres_loss_function,
                     "The threshold for the loss function.")
      .def_readwrite("generate_random_positions",
                     &GlobalPositionerOptions::generate_random_positions,
                     "Whether initialize the reconstruction randomly.")
      .def_readwrite("generate_random_points",
                     &GlobalPositionerOptions::generate_random_points,
                     "Whether initialize the points randomly.")
      .def_readwrite("generate_scales",
                     &GlobalPositionerOptions::generate_scales,
                     "Whether initialize the scales randomly.")
      .def_readwrite("optimize_positions",
                     &GlobalPositionerOptions::optimize_positions,
                     "Whether optimize the positions.")
      .def_readwrite("optimize_points",
                     &GlobalPositionerOptions::optimize_points,
                     "Whether optimize the points.")
      .def_readwrite("optimize_scales",
                     &GlobalPositionerOptions::optimize_scales,
                     "Whether optimize the scales.")
      .def_readwrite("min_num_view_per_track",
                     &GlobalPositionerOptions::min_num_view_per_track,
                     "Constrain the minimum number of views per track.")
      .def_property(
          "max_num_iterations",
          [](const GlobalPositionerOptions& self) -> int {
            return self.solver_options.max_num_iterations;
          },
          [](GlobalPositionerOptions& self, const int value) {
            self.solver_options.max_num_iterations = value;
          })
      .def("__repr__", [](const GlobalPositionerOptions& self) {
        std::stringstream ss;
        ss << "GlobalPositionerOptions(" << std::endl
           << "  thres_loss_function=" << self.thres_loss_function << ","
           << std::endl
           << "  generate_random_positions=" << self.generate_random_positions
           << "," << std::endl
           << "  generate_random_points=" << self.generate_random_points << ","
           << std::endl
           << "  generate_scales=" << self.generate_scales << "," << std::endl
           << "  optimize_positions=" << self.optimize_positions << ","
           << std::endl
           << "  optimize_points=" << self.optimize_points << "," << std::endl
           << "  optimize_scales=" << self.optimize_scales << "," << std::endl
           << "  min_num_view_per_track=" << self.min_num_view_per_track << ","
           << std::endl
           << "  max_num_iterations=" << self.solver_options.max_num_iterations
           << std::endl
           << ")";
        return ss.str();
      });
  MakeDataclass(PyGlobalPositionerOptions);
}