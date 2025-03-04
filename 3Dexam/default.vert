#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
//Texture
layout (location = 2) in vec2 aTex;

// Outputs the color for the Fragment Shader
out vec3 color;
//Texure coordinates
out vec2 texCoord;

// Controls the scale of the vertices
uniform float scale;

uniform mat4 camMatrix;




//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 proj;




void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(aPos,1.0);
	//gl_Position = proj * view * model * vec4(aPos,1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;

	texCoord = aTex;
}