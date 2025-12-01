// Sphere: example of computing it's vertices and indices....

// from : https://songho.ca/opengl/gl_sphere.html

// The definition of sphere is a 3D closed surface where every point on the sphere is same distance (radius) from a given point. The equation of a sphere at the origin is equation of sphere.

// Since we cannot draw all the points on a sphere, we only sample a limited amount of points by dividing the sphere by sectors (longitude) and stacks (latitude). Then connect these sampled points together to form surfaces of the sphere.

// Sectors and stacks of a sphere
// Sectors and stacks of a sphere
// Parametric equation of a sphere
// A point on a sphere using sector and stack angles
// An arbitrary point (x, y, z) on a sphere can be computed by parametric equations with the corresponding sector angle θ and stack angle ϕ.

// formula to find a point on a sphere

// The range of sector angles is from 0 to 360 degrees, and the stack angles are from 90 (top) to -90 degrees (bottom). The sector and stack angle for each step can be calculated by the following;
// angles of per sector/stack

// The following C++ code generates all vertices of the sphere for the given radius, sectors and stacks. It also creates other vertex attributes; surface normals and texture coordinates. For more details, please refer to buildVerticesSmooth() or buildVerticesFlat() functions in Sphere.cpp class.


// clear memory of prev arrays
std::vector<float>().swap(vertices);
std::vector<float>().swap(normals);
std::vector<float>().swap(texCoords);

float x, y, z, xy;                              // vertex position
float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
float s, t;                                     // vertex texCoord

float sectorStep = 2 * PI / sectorCount;
float stackStep = PI / stackCount;
float sectorAngle, stackAngle;

for(int i = 0; i <= stackCount; ++i)
{
    stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
    xy = radius * cosf(stackAngle);             // r * cos(u)
    z = radius * sinf(stackAngle);              // r * sin(u)

    // add (sectorCount+1) vertices per stack
    // first and last vertices have same position and normal, but different tex coords
    for(int j = 0; j <= sectorCount; ++j)
    {
        sectorAngle = j * sectorStep;           // starting from 0 to 2pi

        // vertex position (x, y, z)
        x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
        y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);

        // normalized vertex normal (nx, ny, nz)
        nx = x * lengthInv;
        ny = y * lengthInv;
        nz = z * lengthInv;
        normals.push_back(nx);
        normals.push_back(ny);
        normals.push_back(nz);

        // vertex tex coord (s, t) range between [0, 1]
        s = (float)j / sectorCount;
        t = (float)i / stackCount;
        texCoords.push_back(s);
        texCoords.push_back(t);
    }
}

// vertex indices of sphere
// vertex indices to draw triangles of a sphere
// In order to draw the surface of a sphere in OpenGL, you must triangulate adjacent vertices to form polygons. It is possible to use a single triangle strip to render the whole sphere. However, if the shared vertices have different normals or texture coordinates, then a single triangle strip cannot be used.

// Each sector in a stack requires 2 triangles. If the first vertex index in the current stack is k1 and the next stack is k2, then the counterclockwise orders of vertex indices of 2 triangles are;
// k1 ⟶ k2 ⟶ k1+1
// k1+1 ⟶ k2 ⟶ k2+1

// But, the top and bottom stacks require only one triangle per sector. The code snippet to generate all triangles of a sphere may look like;


// generate CCW index list of sphere triangles
// k1--k1+1
// |  / |
// | /  |
// k2--k2+1
std::vector<int> indices;
std::vector<int> lineIndices;
int k1, k2;
for(int i = 0; i < stackCount; ++i)
{
    k1 = i * (sectorCount + 1);     // beginning of current stack
    k2 = k1 + sectorCount + 1;      // beginning of next stack

    for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
    {
        // 2 triangles per sector excluding first and last stacks
        // k1 => k2 => k1+1
        if(i != 0)
        {
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);
        }

        // k1+1 => k2 => k2+1
        if(i != (stackCount-1))
        {
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }

        // store indices for lines
        // vertical lines for all stacks, k1 => k2
        lineIndices.push_back(k1);
        lineIndices.push_back(k2);
        if(i != 0)  // horizontal lines except 1st stack, k1 => k+1
        {
            lineIndices.push_back(k1);
            lineIndices.push_back(k1 + 1);
        }
    }
}