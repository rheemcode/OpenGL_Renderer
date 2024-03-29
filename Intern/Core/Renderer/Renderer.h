#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Camera.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffers/UniformBuffer.h"
#include <Tests/Sprite.h>
#include <Tests/Cube.h>
#include <memory>
#include <array>
#include <Tests/Sphere.h>

struct RenderCommand
{
	static void Init();
	static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	static void SetClearColor(float r, float g, float b, float a);
	static void Clear();
	static void DrawIndexed(const VertexArray& vertexArray);
	static void DrawIndexed(const uint32_t& p_indices);
	static void RenderLines(const VertexArray& vertexArray);
};

struct VertexAttribs
{
	Vector3 Position;
	Vector2 texCoord;
	float texIndex = 0;
};

struct Renderer2DData {

	static const uint32_t MaxQuads = 3;
	static const uint32_t MaxVertices = MaxQuads * 4;
	static const uint32_t MaxIndices = MaxQuads * 6;
	static const uint32_t MaxTextureSlots = 1;

	std::unique_ptr<VertexArray> m_vao;
	std::unique_ptr<VertexBuffer> m_vb;
	std::unique_ptr<Shader> shader;

	std::array<std::unique_ptr<Texture>, 32> textures;

	VertexAttribs* vertexAttribBase = nullptr;
	VertexAttribs* vertexAttribPtr = nullptr;

	Vector4 vertexPositions[4];

	uint32_t quadIndexCount = 0;
	uint32_t textureSlotIndex = 0;
	uint32_t textureSlotIndexCount = 0;

	struct CameraData
	{
		Matrix4x4 ViewProjection;
	};

};

struct RendererData
{
	std::unique_ptr<UniformBuffer> ubo;
	std::unique_ptr<VertexArray> m_aabbVertexArray;
	std::unique_ptr<VertexBuffer> m_aabbVertexBuffer;
	std::unique_ptr<Shader> shader;

	Matrix4x4 view;
	Matrix4x4 proj;
};

class Renderer
{
	static RendererData renderData;
	static RendererData testRenderData;

	static std::vector<class Mesh> s_renderMeshes;

public:

	enum PRIMITIVE_MODE
	{
		LINES,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_FAN,
		TRIANGLE_STRIP,
	};

	static void Init();
	static void Clear();
	static  void ShutDown();
	static void AddMeshes(const class Mesh& p_rendererComponent);

	static void SetClearColor(float r, float g, float b, float a) { RenderCommand::SetClearColor(r, g, b, a); }
	static void BeginScene(const Camera& camera);

	static void BeginShadow();
	static void RenderSkybox();
	static void RenderShadows();
	static void Render(const Primitive& primitive);
	void Render(const AABB& p_aabb);
	static void Render(const std::vector<Mesh>& p_meshes);

	static void Render(const std::unique_ptr<Primitive>& primitive);
	void SetViewport(int x, int y, int width, int height);
	static void EndScene();

};


class Renderer2D
{
	Renderer2DData m_Data;

	void Flush();

public:
	void Init();
	void BeginScene(const Camera& camera);
	void StartBatch();
	void EndScene();


	void DrawQuad(const Matrix4x4& transform, const Texture& texture);
	void DrawSprite(const Sprite& sprite);

};