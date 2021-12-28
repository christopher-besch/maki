#include <pybind11/pybind11.h>

#include "maki.h"

namespace py = pybind11;

void init_interface(py::module& m)
{
    m.def("init", &Maki::init, "Initialize Maki; to be called once and only once");
}
void init_render_driver(py::module& m)
{
    py::class_<Maki::RenderDriver>(m, "RenderDriver")
        .def(py::init<const std::string&, uint32_t, uint32_t>())
        .def("run", &Maki::RenderDriver::run);
}

PYBIND11_MODULE(maki, m)
{
    m.doc() = "Experimental Rendering Backend for Manim.";
    init_interface(m);
    init_render_driver(m);
}
