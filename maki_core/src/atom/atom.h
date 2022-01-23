#pragma once

namespace Maki {

// smallest renderable unit
// implementation inheritance -> Atom* never used <- using templated programming
// abstract
struct Atom {
    bool render {false};

    // to be defined by implementation:
    // static constexpr const char* type_name {"AtomType"};
};

} // namespace Maki
