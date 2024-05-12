#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <array>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct Vertex
{
	float x, y, z;
	float r, g, b;
	float u, v;


};
class Construct
{
public:
	std::vector<Vertex> Cube(glm::vec3 Color);
	std::array<Vertex, 6> Plane(glm::vec3 Color, glm::vec3 PointPosition);
	std::vector<Vertex> Terrain(glm::vec3 Color, int terrainWidth, int terrainDepth, float terrainScale);
	std::array<Vertex,100> Graph(glm::vec4 CubicFunc, float c, int iterations, const char* filename, int start);
};

