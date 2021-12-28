#include <pybind11/pybind11.h>

#include "maki.h"

namespace py = pybind11;

void init(py::module& m)
{
}

PYBIND11_MODULE(maki, m)
{
    m.doc() = "Experimental Rendering Backend for Manim.";
    init(m);
}
