#include "glomap/estimators/optimization_base.h"

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

void BindOptimizationBaseOptions(py::module& m) {
  py::class_<OptimizationBaseOptions, std::shared_ptr<OptimizationBaseOptions>>
      PyOptimizationBaseOptions(m, "OptimizationBaseOptions");

  PyOptimizationBaseOptions.def(py::init<>())
      .def_readwrite("thres_loss_function",
                     &OptimizationBaseOptions::thres_loss_function)
      .def_property(
          "max_num_iterations",
          [](const OptimizationBaseOptions& self) {
            return self.solver_options.max_num_iterations;
          },
          [](OptimizationBaseOptions& self, int value) {
            self.solver_options.max_num_iterations = value;
          })
      .def_property(
          "num_threads",
          [](const OptimizationBaseOptions& self) {
            return self.solver_options.num_threads;
          },
          [](OptimizationBaseOptions& self, int value) {
            self.solver_options.num_threads = value;
          })
      .def_property(
          "minimizer_progress_to_stdout",
          [](const OptimizationBaseOptions& self) {
            return self.solver_options.minimizer_progress_to_stdout;
          },
          [](OptimizationBaseOptions& self, bool value) {
            self.solver_options.minimizer_progress_to_stdout = value;
          })
      .def_property(
          "function_tolerance",
          [](const OptimizationBaseOptions& self) {
            return self.solver_options.function_tolerance;
          },
          [](OptimizationBaseOptions& self, double value) {
            self.solver_options.function_tolerance = value;
          })
      .def("__repr__", [](const OptimizationBaseOptions& self) {
        std::stringstream ss;
        ss << "OptimizationBaseOptions(" << std::endl
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

  MakeDataclass(PyOptimizationBaseOptions);
}
