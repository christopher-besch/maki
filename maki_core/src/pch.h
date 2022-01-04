#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

// has to be included before gl.h and glfw3.h
#include <GL/glew.h>

#if PROJECT == glfw
#include <GLFW/glfw3.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <imgui.h>
#if PROJECT == glfw
#include <imgui_impl_glfw.h>
#endif
#include <imgui_impl_opengl3.h>

// often used custom declarations
#include "core/definitions.h"
#include "core/log.h"
