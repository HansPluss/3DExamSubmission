#include "Construct.h"

std::array<Vertex, 36> Construct::Cube(glm::vec3 Color)
{
    std::array<Vertex, 36> CubeArray;
    glm::vec3 sizeXYZ = glm::vec3(1.f, 1.f, 1.f);

    // Front face vertices
    Vertex v0{ -sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v1{ sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v2{ sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v3{ -sizeXYZ.x, sizeXYZ.y, sizeXYZ.z ,  Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Right face vertices
    Vertex v4{ sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v5{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v6{ sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7{ sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Back face vertices
    Vertex v8{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v9{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v10{ -sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v11{ sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Left face vertices
    Vertex v12{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v13{ -sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v14{ -sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v15{ -sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Top face vertices
    Vertex v16{ -sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v17{ sizeXYZ.x, sizeXYZ.y, sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v18{ sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v19{ -sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Bottom face vertices
    Vertex v20{ -sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v21{ sizeXYZ.x, -sizeXYZ.y, -sizeXYZ.z, Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v22{ sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v23{ -sizeXYZ.x, -sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    // Assign vertices to CubeArray
    CubeArray[0] = v0;
    CubeArray[1] = v1;
    CubeArray[2] = v2;
    CubeArray[3] = v2;
    CubeArray[4] = v3;
    CubeArray[5] = v0;

    CubeArray[6] = v4;
    CubeArray[7] = v5;
    CubeArray[8] = v6;
    CubeArray[9] = v6;
    CubeArray[10] = v7;
    CubeArray[11] = v4;

    CubeArray[12] = v8;
    CubeArray[13] = v9;
    CubeArray[14] = v10;
    CubeArray[15] = v10;
    CubeArray[16] = v11;
    CubeArray[17] = v8;

    CubeArray[18] = v12;
    CubeArray[19] = v13;
    CubeArray[20] = v14;
    CubeArray[21] = v14;
    CubeArray[22] = v15;
    CubeArray[23] = v12;

    CubeArray[24] = v16;
    CubeArray[25] = v17;
    CubeArray[26] = v18;
    CubeArray[27] = v18;
    CubeArray[28] = v19;
    CubeArray[29] = v16;

    CubeArray[30] = v20;
    CubeArray[31] = v21;
    CubeArray[32] = v22;
    CubeArray[33] = v22;
    CubeArray[34] = v23;
    CubeArray[35] = v20;

    return CubeArray;
}





std::array<Vertex, 6> Construct::Plane(glm::vec3 Color, glm::vec3 PointPosition)
{
    std::array<Vertex, 6> PlaneArray;
    glm::vec3 sizeXYZ = glm::vec3(1.0f, 1.0f, 1.0f);
   
      //  = glm::vec3(sizeXYZ.x / 4, sizeXYZ.x / 2, 0);
    Vertex v2{ sizeXYZ.x, sizeXYZ.y, sizeXYZ.z , Color.x, Color.y, Color.z, 1.0f, 1.0f };
    Vertex v3{ -sizeXYZ.x, sizeXYZ.y, sizeXYZ.z ,  Color.x, Color.y, Color.z, 0.0f, 1.0f };
    Vertex v6{ sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z ,  Color.x, Color.y, Color.z, 1.0f, 0.0f };
    Vertex v7{ -sizeXYZ.x, sizeXYZ.y, -sizeXYZ.z , Color.x, Color.y, Color.z, 0.0f, 0.0f };

    
    v6.y += 0.5;
    v2.y += 0.5;
    v7.y += 1.0;
    PlaneArray[0] = v3;
    PlaneArray[1] = v2;
    PlaneArray[2] = v6;
    PlaneArray[3] = v6;
    PlaneArray[4] = v7;
    PlaneArray[5] = v3;

    return PlaneArray;
}

std::array<Vertex, 100> Construct::Graph(glm::vec4 CubicFunc, float c, int iterations, const char* filename, int start)
{
    std::array<Vertex, 100> GraphArray;
    for (int i = start; i < iterations; ++i) {
        int index = start - i;
        float t = static_cast<float>(i);
        float n = 1.00f;
        float x = i * n;
        float y = ((CubicFunc.x) * (x * x * x)) + (CubicFunc.y) * (x * x) + (1 * CubicFunc.z * x) + CubicFunc.w;

        float z = 0.0f;


        //derivative
        float df = 3 * (CubicFunc.x) * x * x + 2 * CubicFunc.y * x + 1 * CubicFunc.z;


        
        GraphArray[i].x = x;
        GraphArray[i].y = y;
        GraphArray[i].z = z;

        if (df < 0) {
            GraphArray[i].r = 1.0f;
            GraphArray[i].g = 0.0f;
        }
        else {
            GraphArray[i].r = 0.0f;
            GraphArray[i].g = 1.0f;
        }


        GraphArray[i - start].b = std::abs(z) / (c * iterations); // Adjust for coloring effect
      
        //writeToFile(filename, vertex.x, vertex.y, vertex.z,vertex.r, vertex.g, vertex.b);

    }
    
    return GraphArray;
}







