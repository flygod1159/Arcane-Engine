#pragma once

#include <cmath>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <unordered_map>
#include <array>
#include <iterator>
#include <filesystem>

// Check for the platform we are using
#ifdef DEBUG
#include <vendor/renderdoc-1.x/renderdoc/api/app/renderdoc_app.h>

#ifdef _WIN32
#include <Windows.h>
#elif (__linux__)
#include <dlfcn.h>
#endif
#endif

#include <gl/glew.h>

#include <GLFW/glfw3.h>

#include <stb_image_aug.h>

#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Defs.h"
#include "utils/Logger.h"
