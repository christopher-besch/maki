#include <algorithm>

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
py::class_<Maki::RenderDriver> init_render_driver(py::module& m)
{
    return py::class_<Maki::RenderDriver>(m, "RenderDriver")
        .def(py::init<const std::string&, uint32_t, uint32_t>())
        .def("await_termination", &Maki::RenderDriver::await_termination)
        .def("is_terminated", &Maki::RenderDriver::is_terminated)
        .def("set_target_frame", &Maki::RenderDriver::set_target_frame);
}
template<typename AtomType>
void init_atom(py::class_<Maki::RenderDriver>& render_driver)
{
    std::string type_name {AtomType::type_name};
    std::transform(type_name.begin(), type_name.end(), type_name.begin(), [](unsigned char c) { return std::tolower(c); });
    render_driver
        .def(("add_" + type_name + "_atom").c_str(),
             &Maki::RenderDriver::add_atom<AtomType>)
        .def(("show_" + type_name + "_atom").c_str(),
             &Maki::RenderDriver::show_atom<AtomType>)
        .def(("translate_" + type_name + "_atom").c_str(),
             &Maki::RenderDriver::translate_atom<AtomType>)
        .def(("color_" + type_name + "_atom").c_str(),
             &Maki::RenderDriver::color_atom<AtomType>);
}

PYBIND11_MODULE(maki, m)
{
    m.doc() = "Experimental Rendering Backend for Manim.";
    init_interface(m);
    init_glm_types(m);
    auto render_driver = init_render_driver(m);
    init_atom<Maki::QuadrilateralAtom>(render_driver);
    init_atom<Maki::CuboidAtom>(render_driver);
}
