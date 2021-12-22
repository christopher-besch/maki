#pragma once

namespace Maki {

class Shader {
public:
    static Shader* create();

public:
    virtual ~Shader() = default;
};

} // namespace Maki
