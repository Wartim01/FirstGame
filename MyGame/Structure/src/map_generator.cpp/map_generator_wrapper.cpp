#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "map_generator.h"

namespace py = pybind11;

PYBIND11_MODULE(map_generator, m) {
    py::class_<GameMap>(m, "GameMap")
        .def(py::init<int, int>())
        .def("generate_map", &GameMap::generateMap)
        .def("display_map", &GameMap::displayMap);
}