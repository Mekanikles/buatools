#include <bua/bua.h>

namespace bua
{

////////////////////////////////////////////////////////////////////////////////

RenderState::RenderState(uint reservedCapacityInQuads)
{
	meshData.vertexData.reserve(reservedCapacityInQuads * 4);
	meshData.indexData.reserve(reservedCapacityInQuads * 6);
}

////////////////////////////////////////////////////////////////////////////////

void RenderState::reset()
{
	meshData.vertexData.clear();
	meshData.indexData.clear();
}

////////////////////////////////////////////////////////////////////////////////

void RenderState::addMesh(const MeshData& mesh)
{
	const auto indexBase = meshData.vertexData.size();
	meshData.indexData.reserve(meshData.indexData.size() + mesh.indexData.size());
	for (auto index : mesh.indexData)
		meshData.indexData.push_back(index + indexBase);

	meshData.vertexData.reserve(meshData.vertexData.size() + mesh.vertexData.size());
	for (auto vertex : mesh.vertexData)
		meshData.vertexData.push_back(vertex);
}

////////////////////////////////////////////////////////////////////////////////

}