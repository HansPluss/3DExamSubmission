#pragma once
#include "Resources/Shaders/VBO.h"
#include "Resources/Shaders/VAO.h"
#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Resources/ImportedCode/Construct.h"



using namespace std;
class Player {
private:


public:
std::array<Vertex, 36> mVertecies;
std::array<Vertex, 6> mPlaneVertecies;
std::array<Vertex, 48> mHouseVertecies;
	glm::vec3 position;
	float r, g, b;
	glm::vec3 velocity;
	glm::vec3 PointPosition;
	float sphere_radius = 0;
	float size1 = 1.0f;
	bool up = true;
	bool down = true;
	bool left = true;
	bool right = true;
	bool move = true; 
	
	
	VAO VAO1;
	VBO VBO1;
	Construct con;
	std::array<glm::vec3, 4> planePoints;
	
	
	Player(float scale, const glm::vec3& initialPosition, float red = 1.0f, float green = 1.0f, float blue = 1.0f, float figure = 1.f)
		: a(scale), position(initialPosition), velocity(glm::vec3(0.0f)), r(red), g(green), b(blue), VBO1()
	{
		


		//Cube
		if (figure == 1)
		{
			mVertecies = con.Cube(glm::vec3(red, green, blue));

			VAO1.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		
			VAO1.Unbind();
			VBO1.Unbind();
			planePoints[0] = glm::vec3(scale, -scale, scale) + position;
			planePoints[1] = glm::vec3(scale, scale, scale) + position;
			planePoints[2] = glm::vec3(scale, scale, -scale) + position;
			planePoints[3] = glm::vec3(-scale, scale, -scale) + position;
		}
		else if (figure == 2)
		{
			
			VAO1.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mPlaneVertecies.size() * sizeof(Vertex), mPlaneVertecies.data(), GL_STATIC_DRAW);
			VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO1.Unbind();
			VBO1.Unbind();
			
		}

		else if (figure == 3)
		{
			
		
		}
		else if (figure == 4) {

			PointPosition = glm::vec3(10.0f, 0.0f, 0.0f);
			mPlaneVertecies = con.Plane(glm::vec3(red, green, blue), PointPosition);

			VAO1.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mPlaneVertecies.size() * sizeof(Vertex), mPlaneVertecies.data(), GL_STATIC_DRAW);
			VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO1.Unbind();
			VBO1.Unbind();
			planePoints[0] = glm::vec3(-scale, scale, scale) + position;
			planePoints[1] = glm::vec3(scale, scale * 1.5, scale) + position;
			planePoints[2] = glm::vec3(scale, scale * 1.5, -scale) + position;
			planePoints[3] = glm::vec3(-scale, scale * 2, -scale) + position;

		}
		else
		{
			mVertecies = con.Cube(glm::vec3(red, green, blue));

			VAO1.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO1.Unbind();
			VBO1.Unbind();
			planePoints[0] = glm::vec3(-scale, -scale, -scale) + position;
			planePoints[1] = glm::vec3(scale, -scale, -scale) + position;
			planePoints[2] = glm::vec3(scale, -scale, scale) + position;
			planePoints[3] = glm::vec3(-scale, -scale, scale) + position;
		}
		
		sphere_radius = a; 
		size1 = scale;

		
	}
	float GetA();
	void DeleteVBOANDVAO();
	void UnbindVAO();
	void BindVAO();
	void UpdateVertices(float Xspeed, float Yspeed, float Zspeed);
	VBO GetVBO();
	void inputs(GLFWwindow* window);

	void Patrol(std::vector<double> coefficients);
	
	bool CheckSphereCollision( Player& otherCube);
	bool AABBCollision(Player& othercube);
	
	glm::vec3 calculateBarycentricCoordinates(glm::vec3& cpoint, glm::vec3 v0,glm::vec3 v1, glm::vec3 v2, bool climbable);

public:
	float a{ 1.0f };
	double xvalue = 0;
	double xspeed = 0.001;
	bool xPositiveDir = true;


};