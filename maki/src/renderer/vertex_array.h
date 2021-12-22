#pragma once

namespace Maki {

class VertexArray {
public:
    static VertexArray* create();

public:
    virtual ~VertexArray() = default;
};

} // namespace Maki
