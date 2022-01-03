#include <pybind11/pybind11.h>

#include "maki.h"

namespace py = pybind11;

void init_interface(py::module& m)
{
    m.def("init", &Maki::init, "Initialize Maki; to be called once and only once");
    py::enum_<Maki::Renderer::Implementation>(m, "RendererImplementation")
        .value("none", Maki::Renderer::Implementation::none)
        .value("opengl", Maki::Renderer::Implementation::opengl)
        .export_values();
}
void init_render_driver(py::module& m)
{
    py::class_<Maki::RenderDriver>(m, "RenderDriver")
        .def(py::init<const std::string&, uint32_t, uint32_t>())
        .def("await_termination", &Maki::RenderDriver::await_termination)
        .def("is_terminated", &Maki::RenderDriver::is_terminated);
}

PYBIND11_MODULE(maki, m)
{
    m.doc() = "Experimental Rendering Backend for Manim.";
    init_interface(m);
    init_render_driver(m);
}
