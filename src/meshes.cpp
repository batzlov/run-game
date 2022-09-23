#include "meshes.h"

#define _USE_MATH_DEFINES
#include <cmath>

const float TEX_MIN = 0.0f;
const float TEX_MAX = 1.0f;

const int INDICES_PER_TRIANGLE = 3;

void CreateMeshObj(int numOfVertices, float *vertices, int numOfTriangles, int *triangles, BHandle &material, BHandle &mesh) 
{
    SMeshInfo meshInfo;

    meshInfo.m_NumberOfVertices = numOfVertices;
    meshInfo.m_pVertices = vertices;

    meshInfo.m_NumberOfIndices = numOfTriangles * INDICES_PER_TRIANGLE;
    meshInfo.m_pIndices = triangles;
    
    meshInfo.m_pMaterial = material;

    CreateMesh(meshInfo, &mesh);
}

void CreateQuadMesh(float height, float width, float depth, BHandle &mesh, BHandle &material)
{
    float x = width / 2;
    float y = height / 2;
    float z = depth / 2;

    float vertices[][8] = {
        // front
        { -x, y,-z,  TEX_MIN, TEX_MIN,  0.0f, 0.0f,-1.0f },
        { -x,-y,-z,  TEX_MIN, TEX_MAX,  0.0f, 0.0f,-1.0f },
        {  x,-y,-z,  TEX_MAX, TEX_MAX,  0.0f, 0.0f,-1.0f },
        {  x, y,-z,  TEX_MAX, TEX_MIN,  0.0f, 0.0f,-1.0f },
        // back
        { -x,-y, z,  TEX_MIN, TEX_MIN,  0.0f, 0.0f, 1.0f },
        { -x, y, z,  TEX_MIN, TEX_MAX,  0.0f, 0.0f, 1.0f },
        {  x, y, z,  TEX_MAX, TEX_MAX,  0.0f, 0.0f, 1.0f },
        {  x,-y, z,  TEX_MAX, TEX_MIN,  0.0f, 0.0f, 1.0f },
        // top
        { -x, y, z,  TEX_MIN, TEX_MIN,  0.0f, 1.0f, 0.0f },
        { -x, y,-z,  TEX_MIN, TEX_MAX,  0.0f, 1.0f, 0.0f },
        {  x, y,-z,  TEX_MAX, TEX_MAX,  0.0f, 1.0f, 0.0f },
        {  x, y, z,  TEX_MAX, TEX_MIN,  0.0f, 1.0f, 0.0f },
        // bottom
        { -x,-y,-z,  TEX_MIN, TEX_MIN,  0.0f,-1.0f, 0.0f },
        { -x,-y, z,  TEX_MIN, TEX_MAX,  0.0f,-1.0f, 0.0f },
        {  x,-y, z,  TEX_MAX, TEX_MAX,  0.0f,-1.0f, 0.0f },
        {  x,-y,-z,  TEX_MAX, TEX_MIN,  0.0f,-1.0f, 0.0f },
        // right
        {  x, y,-z,  TEX_MIN, TEX_MIN,  1.0f, 0.0f, 0.0f },
        {  x,-y,-z,  TEX_MIN, TEX_MAX,  1.0f, 0.0f, 0.0f },
        {  x,-y, z,  TEX_MAX, TEX_MAX,  1.0f, 0.0f, 0.0f },
        {  x, y, z,  TEX_MAX, TEX_MIN,  1.0f, 0.0f, 0.0f },
        // left
        { -x, y, z,  TEX_MIN, TEX_MIN, -1.0f, 0.0f, 0.0f },
        { -x,-y, z,  TEX_MIN, TEX_MAX, -1.0f, 0.0f, 0.0f },
        { -x,-y,-z,  TEX_MAX, TEX_MAX, -1.0f, 0.0f, 0.0f },
        { -x, y,-z,  TEX_MAX, TEX_MIN, -1.0f, 0.0f, 0.0f },
    };

    int triangles[][3] = {
        {  0, 1, 2 }, {  0, 2, 3 },
        {  4, 5, 6 }, {  4, 6, 7 },
        {  8, 9,10 }, {  8,10,11 },
        { 12,13,14 }, { 12,14,15 },
        { 16,17,18 }, { 16,18,19 },
        { 20,21,22 }, { 20,22,23 },
    };

    CreateMeshObj(24, &vertices[0][0], 12, &triangles[0][0], material, mesh);
}

void CreateCubeMesh(BHandle &mesh, BHandle &material)
{
    CreateQuadMesh(1.0f, 1.0f, 1.0f, mesh, material);
}

const float RADIUS = 0.5f; // radius of sphere
const int N = 12; // number of vertical meridians
const int M = 8; // number of equatorial meridians

const float PI = float(M_PI);

void CreateCircleVertices(float radius, float height, float texHeight, float vertices[N][8]) 
{
    float texWidth = 0.0f;
    float texWidthStep = 1.0f / (N - 1);

    float angle = 0.0f;
    float angleStep = 2 * PI / (N - 1);

    for (int i = 0; i < N; i++) 
    {
        vertices[i][0] = cos(angle) * radius;
        vertices[i][1] = height;
        vertices[i][2] = sin(angle) * radius;

        vertices[i][3] = texWidth;
        vertices[i][4] = texHeight;

        texWidth += texWidthStep;
        angle += angleStep;
    }
}

void CreateSphereVertices(float vertices[][8]) 
{
    float angle = PI / 2.0f;
    float angleStep = PI / (M - 1);

    float texHeight = 0.0f;
    float texHeightStep = 1.0f / (M - 1);

    for (int i = 0; i < M; i++)
    {
        CreateCircleVertices(cos(angle) * RADIUS, sin(angle) * RADIUS, texHeight, &vertices[i * N]);

        angle -= angleStep;
        texHeight += texHeightStep;
    }
}

void AddNormalsFromPosition(float vertices[][8], size_t n) 
{
    for(unsigned int i = 0; i < n; i++) 
    {
        float normal[3] = { vertices[i][0], vertices[i][1], vertices[i][2] };

        gfx::GetNormalizedVector(normal, normal);

        vertices[i][5] = normal[0];
        vertices[i][6] = normal[1];
        vertices[i][7] = normal[2];
    }
}

void CreateSphereTriangles(int triangles[][3]) 
{
    int index = 0;

    for (int row = 0; row < (M - 1); row++) 
    {
        for (int i = 1; i < N; i++) 
        {
            triangles[index][0] = (row + 1) * N + i - 1;
            triangles[index][1] = (row + 1) * N + i;
            triangles[index][2] = row * N + i;
            index++;
            triangles[index][0] = (row + 1) * N + i - 1;
            triangles[index][1] = row * N + i;
            triangles[index][2] = row * N + i - 1;
            index++;
        }
    }
}

void CreateSphereMesh(BHandle &mesh, BHandle &material) 
{
    float vertices[N * M][8];

    CreateSphereVertices(vertices);

    AddNormalsFromPosition(vertices, N * M);

    int triangles[2 * N * (M - 1)][3];

    CreateSphereTriangles(triangles);

    CreateMeshObj(N * M, &vertices[0][0], 2 * N * (M - 1), &triangles[0][0], material, mesh);
}