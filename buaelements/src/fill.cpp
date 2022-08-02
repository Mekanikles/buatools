#include <bua/elements/fill.h>

namespace bua
{

////////////////////////////////////////////////////////////////////////////////	

elements::Fill::Fill(const Rect& rect, const Color& color)
{
	update(rect, color);
}

////////////////////////////////////////////////////////////////////////////////

void elements::Fill::update(const Rect& rect, const Color& color)
{
	mesh.vertexData.clear();
	mesh.indexData.clear();
	mesh.vertexData.reserve(4);
	mesh.indexData.reserve(6);

	mesh.vertexData.push_back(MeshData::Vertex { rect.x, rect.y, 0, color });
	mesh.vertexData.push_back(MeshData::Vertex { rect.x, rect.y + rect.h, 0, color });
	mesh.vertexData.push_back(MeshData::Vertex { rect.x + rect.w, rect.y + rect.h, 0, color });
	mesh.vertexData.push_back(MeshData::Vertex { rect.x + rect.w, rect.y, 0, color });

	mesh.indexData.push_back(0);
	mesh.indexData.push_back(1);
	mesh.indexData.push_back(2);
	mesh.indexData.push_back(0);
	mesh.indexData.push_back(2);
	mesh.indexData.push_back(3);
}

////////////////////////////////////////////////////////////////////////////////

void elements::Fill::render(not_null<RenderState*> renderState) const
{
	renderState->addMesh(mesh);
}

////////////////////////////////////////////////////////////////////////////////

}