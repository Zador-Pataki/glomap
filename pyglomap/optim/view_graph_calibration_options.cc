#include "glomap/estimators/view_graph_calibration.h"

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

void BindViewGraphCalibratorOptions(py::module& m) {
  py::class_<ViewGraphCalibratorOptions,
             OptimizationBaseOptions,
             std::shared_ptr<ViewGraphCalibratorOptions>>
      PyViewGraphCalibratorOptions(m, "ViewGraphCalibratorOptions");

  PyViewGraphCalibratorOptions.def(py::init<>())
      .def_readwrite("thres_lower_ratio",
                     &ViewGraphCalibratorOptions::thres_lower_ratio)
      .def_readwrite("thres_higher_ratio",
                     &ViewGraphCalibratorOptions::thres_higher_ratio)
      .def_readwrite("thres_two_view_error",
                     &ViewGraphCalibratorOptions::thres_two_view_error)
      .def_readwrite("thres_loss_function",
                     &ViewGraphCalibratorOptions::thres_loss_function)
      .def("__repr__", [](const ViewGraphCalibratorOptions& self) {
        std::stringstream ss;
        ss << "ViewGraphCalibratorOptions(" << std::endl
           << "  thres_lower_ratio=" << self.thres_lower_ratio << ","
           << std::endl
           << "  thres_higher_ratio=" << self.thres_higher_ratio << ","
           << std::endl
           << "  thres_two_view_error=" << self.thres_two_view_error << ","
           << std::endl
           // Also include base class options
           << "  thres_loss_function=" << self.thres_loss_function << ","
           << std::endl
           << "  max_num_iterations=" << self.solver_options.max_num_iterations
           << "," << std::endl
           << "  num_threads=" << self.solver_options.num_threads << ","
           << std::endl
           << "  minimizer_progress_to_stdout="
           << self.solver_options.minimizer_progress_to_stdout << ","
           << std::endl
           << "  function_tolerance=" << self.solver_options.function_tolerance
           << std::endl
           << ")";
        return ss.str();
      });

  MakeDataclass(PyViewGraphCalibratorOptions);
}
