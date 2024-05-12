#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Resources/ImportedCode/Construct.h"
#include <string>
class MathFunctions {
public:

	glm::vec4 CubicInterpolation(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
	glm::vec4 CubicHermiteFunction(float inx0, float inx1, float iny0, float iny1, float derivativeY0, float derivativeY1);
	void writeToFile(const char* fileName, double x, double y, double z, double r, double g, double b);
	void Readfile(const char* fileName, std::vector<Vertex>& vertices);
};