// include everything often used and rarely or never changed -> speeds up compilation
#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>
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

// often used, rarely changing custom declarations
#include "core/definitions.h"
#include "core/log.h"
