#pragma once
#include "bua/bua.h"

namespace bua
{

namespace elements
{
	class Fill : public Element
	{
	public:
		Fill(const Rect& rect, const Color& color);

		void update(const Rect& rect, const Color& color);

	protected:
		virtual void render(not_null<RenderState*> renderState) const override;

	private:
		MeshData mesh;
	};
}

}
