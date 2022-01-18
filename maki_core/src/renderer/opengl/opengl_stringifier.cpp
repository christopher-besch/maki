#include "pch.h"

#include "opengl_stringifier.h"

namespace Maki {

// Thanks to Light3039!!! ^^
std::string Stringifier::gl_msg_severity(GLenum val)
{
    switch(val) {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return "GL_DEBUG_SEVERITY_NOTIFICATION";
    case GL_DEBUG_SEVERITY_LOW:
        return "GL_DEBUG_SEVERITY_LOW";
    case GL_DEBUG_SEVERITY_MEDIUM:
        return "GL_DEBUG_SEVERITY_MEDIUM";
    case GL_DEBUG_SEVERITY_HIGH:
        return "GL_DEBUG_SEVERITY_HIGH";
    default:
        return "UNKNOWN";
    }
}
std::string Stringifier::gl_msg_source(GLenum val)
{
    switch(val) {
    case GL_DEBUG_SOURCE_API:
        return "GL_DEBUG_SOURCE_API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return "GL_DEBUG_SOURCE_SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "GL_DEBUG_SOURCE_THIRD_PARTY";
    case GL_DEBUG_SOURCE_APPLICATION:
        return "GL_DEBUG_SOURCE_APPLICATION";
    case GL_DEBUG_SOURCE_OTHER:
        return "GL_DEBUG_SOURCE_OTHER";
    default:
        return "UNKNOWN";
    }
}
std::string Stringifier::gl_msg_type(GLenum val)
{
    switch(val) {
    case GL_DEBUG_TYPE_ERROR:
        return "GL_DEBUG_TYPE_ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY:
        return "GL_DEBUG_TYPE_PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE:
        return "GL_DEBUG_TYPE_PERFORMANCE";
    case GL_DEBUG_TYPE_MARKER:
        return "GL_DEBUG_TYPE_MARKER";
    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "GL_DEBUG_TYPE_PUSH_GROUP";
    case GL_DEBUG_TYPE_POP_GROUP:
        return "GL_DEBUG_TYPE_POP_GROUP";
    case GL_DEBUG_TYPE_OTHER:
        return "GL_DEBUG_TYPE_OTHER";
    default:
        return "UNKNOWN";
    }
}

} // namespace Maki
