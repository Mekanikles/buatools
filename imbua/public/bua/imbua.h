#pragma once
#include <bua/bua.h>

namespace bua
{

namespace im
{
	using ElementId = u32;
	static const ElementId ElementId_Invalid = -1;

	void beginRender();
	void endRender(not_null<RenderState*> renderState);

	void fill(const Rect& rect, const Color& color);
}

}