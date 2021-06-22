#pragma once
#include "Primitive.h"


class Cube : public Primitive
{
public:
    Cube();
    void Draw(const class Camera& camera);

private:
    void GenVertices();
     void EnableAttribs() override;
     void CreateVertexArray() override;
     void CreateVertexBuffer() override;
     void CreateIndexBuffer() override;
private:
    std::vector<vec4> m_VertexPositions;
    int m_UniformLocation;
    int m_MvpLocation;
};