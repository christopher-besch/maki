#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

// has to be included before gl.h and glfw3.h
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

using vec4 = glm::vec4;
using mat4 = glm::mat4;
using vec3 = glm::vec3;
using mat3 = glm::mat3;

constexpr float PI     = 3.14f;
constexpr int   WIDTH  = 1024;
constexpr int   HEIGHT = 768;
