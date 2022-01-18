#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Maki {

// convert GLenums into legible output
class Stringifier {
public:
    static std::string gl_msg_severity(GLenum val);
    static std::string gl_msg_source(GLenum val);
    static std::string gl_msg_type(GLenum val);
};

} // namespace Maki
