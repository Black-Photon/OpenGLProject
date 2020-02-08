#pragma once

// Standard Library
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include <memory>
#include <map>
#include <tgmath.h>

// OpenGL
#include "glad/glad.h"
#include <GLFW/glfw3.h>

// STB Image
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// -------------------- MODULE FILES --------------------

#include "core/core.hpp"

// ----------- ALL PROJECT INCLUDES BELOW HERE -----------

// Include Class Headers
#include "Lightning-Borders/Lightning.h"
#include "Lightning-Borders/Renderer.h"

// Include Helper Headers

// Include Class Files
#include "Lightning-Borders/Lightning.cpp"
#include "Lightning-Borders/Renderer.cpp"

// Include Helper Files