#include "Player.h"
#include <iostream>




float Player::GetA()
{
    return a;
}


void Player::DeleteVBOANDVAO()
{
	VAO1.Delete();
	VBO1.Delete();

}

void Player::UnbindVAO()
{
	VAO1.Unbind();
}

void Player::BindVAO()
{
	VAO1.Bind();
}

void Player::UpdateVertices(float Xspeed, float Yspeed, float Zspeed)
{
	glm::vec3 a = glm::vec3(Xspeed, 0, Zspeed);
	float speedMagnitude = glm::length(a);
	if (speedMagnitude > 0.0f) {
		a = glm::normalize(a);
	}
	
	/*position.x += Xspeed;
	position.y += Yspeed;
    position.z += Zspeed;*/
	position += a * speedMagnitude;
	cout << "current x speed: " << position.x << std::endl;
	
	
	
}

VBO Player::GetVBO()
{
	return VBO1;
}

void Player::inputs(GLFWwindow* window)
{
	float speed = 0.1f;
	float xSpeedVector = 0.0f;
	float zSpeedVector = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && up) {

		//UpdateVertices(0, 0, -speed, glm::vec3(0, 0, 1));
		//position.z -= translationSpeed;
		zSpeedVector = -speed;

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && down) {

		//UpdateVertices(0, 0, speed, glm::vec3(0, 0, 1));
		//position.z += translationSpeed;
		zSpeedVector = speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && left) {

		//UpdateVertices(-speed, 0, 0, glm::vec3(1, 0, 0));
		//position.x -= translationSpeed;
		xSpeedVector = -speed;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && right) {

		//UpdateVertices(speed, 0, 0, glm::vec3(1, 0, 0));
		//position.x += translationSpeed;
		xSpeedVector = speed;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {

		//UpdateVertices(0, speed * 50, 0, glm::vec3(0, 1, 0));
		
		//position.x += translationSpeed;
	}
	UpdateVertices(xSpeedVector, 0, zSpeedVector);
}





bool Player::CheckSphereCollision( Player& otherCube)
{
	float distance_centers = glm::length(position - otherCube.position);
		
	if (distance_centers <= (sphere_radius + otherCube.sphere_radius)) {

		float minimuntranslation = sphere_radius +otherCube.sphere_radius - distance_centers;
		auto dirvec = glm::normalize(position - otherCube.position);
		position += dirvec * minimuntranslation;
		//otherCube.position += dirvec * minimuntranslation;

		otherCube.move = false;
		return true; 

	}
	else {
;
		otherCube.move = true;
	}


	// No collision detected
	return false;
}

bool Player::AABBCollision(Player& otherCube)
{
	
	// collision x-axis?
	bool collisionX = position.x + size1 >= otherCube.position.x &&
		otherCube.position.x + otherCube.size1 >= position.x;
	// collision y-axis?
	bool collisionY = position.y + size1 >= otherCube.position.y &&
		otherCube.position.y + otherCube.size1 >= position.y;
	// collision z-axis?
	bool collisionZ = position.z + size1 >= otherCube.position.z &&
		otherCube.position.z + otherCube.size1 >= position.z;
	// collision only if on both axes
	return collisionX && collisionY && collisionZ;
}




std::vector<double> computeDerivative(const std::vector<double>& coefficients) {
	std::vector<double> derivativeCoefficients;

	// Compute derivative coefficients
	for (size_t i = 1; i < coefficients.size(); ++i) {
		derivativeCoefficients.push_back(i * coefficients[i]);
	}

	return derivativeCoefficients;
}

double evaluatePolynomial(const std::vector<double>& coefficients, double x) {
	double result = 0.0;
	double power = 1.0;
	for (size_t i = 0; i < coefficients.size(); ++i) {
		result += coefficients[i] * power;
		power *= x;
	}
	return result;
}

double computeDerivativeAtPoint(const std::vector<double>& coefficients, double x) {
	std::vector<double> derivativeCoefficients = computeDerivative(coefficients);
	return evaluatePolynomial(derivativeCoefficients, x);
}


void Player::Patrol(std::vector<double> coefficients)
{
	//if(move)
	//{
		double Derivative = computeDerivativeAtPoint(coefficients, xvalue) / 4096;
		for (Vertex& vertex : mVertecies) {
			position.x += xspeed / 2;
			
			if (xPositiveDir) position.z += Derivative;
			else position.z -= Derivative;
		}
		xvalue += xspeed;
		if (xvalue >= 1) {
			xspeed *= -1;
			xPositiveDir = false;
		}
		else if (xvalue <= -0.25) {
			xspeed *= -1;
			xPositiveDir = true;
		}
	//}
}



glm::vec3 Player::calculateBarycentricCoordinates(glm::vec3& cpoint, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, bool climbable)
{

	glm::vec3 point = cpoint;

	if (!climbable)
	{
		planePoints[0] = glm::vec3(-1, 1, 1) + position;
		planePoints[1] = glm::vec3(1, 1, 1) + position;
		planePoints[2] = glm::vec3(1, 1, -1) + position;
		planePoints[3] = glm::vec3(-1, 1, -1) + position;
		v0.y = 0;
		v1.y = 0;
		v2.y = 0;
		point.y = 0;


	}


	glm::vec3 v0v1(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
	glm::vec3 v0v2(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
	glm::vec3 v0p(point.x - v0.x, point.y - v0.y, point.z - v0.z);

	// Compute dot products
	float dot00 = glm::dot(v0v1, v0v1);
	float dot01 = glm::dot(v0v1, v0v2);
	float dot02 = glm::dot(v0v1, v0p);
	float dot11 = glm::dot(v0v2, v0v2);
	float dot12 = glm::dot(v0v2, v0p);

	// Compute barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	float w = 1 - u - v;
	if (u > 0 && v > 0 && w > 0) {
		if (climbable)
		{
			float heightV6 = v0.y * w + v1.y * u + v2.y * v;
			cpoint.y = heightV6 + 1; // -19 is planePosition.y -2, offset to have player above 
			//std::cout << "Collision " << u << std::endl;
		}
		else
		{
			cpoint.y += 2;
			//std::cout << "Collision " << u << std::endl;
		}
	}

	return glm::vec3(u, v, w);

	
}
