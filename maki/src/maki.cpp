#include <pybind11/operators.h>
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
void init_glm_types(py::module& m)
{
    // TODO: remove these children's toys
    py::class_<Maki::vec3>(m, "vec3")
        .def(py::init<float, float, float>())
        .def(py::self * float());
    py::class_<Maki::vec4>(m, "vec4")
        .def(py::init<float, float, float, float>())
        .def(py::self * float());
}
void init_render_driver(py::module& m)
{
    py::class_<Maki::RenderDriver>(m, "RenderDriver")
        .def(py::init<const std::string&, uint32_t, uint32_t>())
        .def("await_termination", &Maki::RenderDriver::await_termination)
        .def("is_terminated", &Maki::RenderDriver::is_terminated)
        .def("add_cuboid_atom", &Maki::RenderDriver::add_atom<Maki::CuboidAtom>)
        .def("show_cuboid_atom", &Maki::RenderDriver::show_atom<Maki::CuboidAtom>)
        .def("translate_cuboid_atom", &Maki::RenderDriver::translate_atom<Maki::CuboidAtom>)
        .def("color_cuboid_atom", &Maki::RenderDriver::color_atom<Maki::CuboidAtom>)
        .def("set_target_frame", &Maki::RenderDriver::set_target_frame);
}

PYBIND11_MODULE(maki, m)
{
    m.doc() = "Experimental Rendering Backend for Manim.";
    init_interface(m);
    init_glm_types(m);
    init_render_driver(m);
}
