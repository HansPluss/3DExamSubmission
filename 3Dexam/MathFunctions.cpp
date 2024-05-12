#include "MathFunctions.h"

glm::vec4 MathFunctions::CubicInterpolation(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
	glm::mat<4, 4, double> A(
		powf(x0, 3), powf(x1, 3), powf(x2, 3), powf(x3, 3),
		powf(x0, 2), powf(x1, 2), powf(x2, 2), powf(x3, 2),
		powf(x0, 1), powf(x1, 1), powf(x2, 1), powf(x3, 1),
		1, 1, 1, 1
	);

	glm::vec<4, double> y(y0, y1, y2, y3);

	glm::mat<4, 4, double>inverseA = glm::inverse(A);

	glm::vec<4, double> x = inverseA * y;
	return x;
}

glm::vec4 MathFunctions::CubicHermiteFunction(float inx0, float inx1, float iny0, float iny1, float derivativeY0, float derivativeY1)
{
	float x0, x1, y0, y1;
	x0 = inx0;
	x1 = inx1;
	y0 = iny0;
	y1 = iny1;

	float derY0, derY1;
	derY0 = derivativeY0;
	derY1 = derivativeY1;

	float func = powf(1, 1);
	glm::mat<4, 4, float> A
	(powf(x0, 3), powf(x0, 2), x0, 1,
		powf(x1, 3), powf(x1, 2), x1, 1,
		powf(x0, 2), x0, 1, 0,
		powf(x0, 2), x0, 1, 1);

	glm::vec4 y(y0, y1, derivativeY0, derivativeY1);

	glm::mat4 inverseA = glm::inverse(A);

	glm::vec4 x = inverseA * y;
	return x;
}

void MathFunctions::writeToFile(const char* fileName, double x, double y, double z, double r, double g, double b)
{
	std::ofstream outputFile(fileName, std::ios::app);  // Open the file in append mode
	if (outputFile.is_open()) {
		outputFile << std::fixed << std::setprecision(3);
		outputFile << x << " , " << y << " , " << z << " , " << r << " , " << g << " , " << b;


	}
	else {
		std::cerr << "Unable to open the output file for writing." << std::endl;
	}
	outputFile << std::endl;
	outputFile.close();

}

void MathFunctions::Readfile(const char* fileName, std::vector<Vertex>& vertices)
{
	std::ifstream inputFile(fileName);
	if (inputFile.is_open()) {


		std::string line;
		std::getline(inputFile, line);
		Vertex vertex;
		char comma; // to capture the commas in the file

		while (inputFile >> vertex.x >> comma >> vertex.y >> comma >> vertex.z >> comma
			>> vertex.r >> comma >> vertex.g >> comma >> vertex.b) {
			vertices.push_back(vertex);
		}

		inputFile.close();
	}
	else {
		std::cerr << "Unable to open the input file for reading." << std::endl;
	}
}
