#pragma once
#include <bua/core.h>

#include <EASTL/vector.h>
#include <EASTL/variant.h>
#include <EASTL/unique_ptr.h>

namespace bua
{

struct Rect
{
	float x, y, h, w;
};

struct Color
{
	float r, g, b, a;
};

struct MeshData
{
	struct Vertex
	{
		float x, y, z;
		Color color;
	};

	eastl::vector<size_t> indexData;
	eastl::vector<Vertex> vertexData;
};

struct RenderState
{
	// TODO: move to slab allocation with slab size in config
	RenderState(uint reservedCapacityInQuads);

	void reset();
	void addMesh(const MeshData& mesh);

	MeshData meshData;
};

class Element
{
public:
	virtual ~Element() {}
	virtual void render(not_null<RenderState*> renderState) const = 0;
};

struct Context
{
	eastl::vector<eastl::unique_ptr<Element>> elements;
};

}
