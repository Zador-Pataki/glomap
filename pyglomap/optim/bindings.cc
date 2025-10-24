#include <pybind11/pybind11.h>

namespace py = pybind11;

void BindOptimizationBaseOptions(py::module& m);
void BindRotationAveragerOptions(py::module& m);
void BindTrackEstablishmentOptions(py::module& m);
void BindGlobalPositionerOptions(py::module& m);
void BindBundleAdjusterOptions(py::module& m);
void BindInlierThresholdOptions(py::module& m);
void BindGlobalMapperOptions(py::module& m);
void BindViewGraphCalibratorOptions(py::module& m);
void BindTriangulatorOptions(py::module& m);

void BindOptim(py::module& m) {
  BindOptimizationBaseOptions(m);
  BindRotationAveragerOptions(m);
  BindTrackEstablishmentOptions(m);
  BindGlobalPositionerOptions(m);
  BindBundleAdjusterOptions(m);
  BindInlierThresholdOptions(m);
  BindGlobalMapperOptions(m);
  BindViewGraphCalibratorOptions(m);
  BindTriangulatorOptions(m);
}
