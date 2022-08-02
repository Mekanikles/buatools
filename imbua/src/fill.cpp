#include <bua/imbua.h>

#include <bua/elements/fill.h>
#include "imstate.h"

namespace bua
{

namespace im
{
	void fill(const Rect& rect, const Color& color)
	{
		// TODO: Awkward API, have to supply data in both constructor and update
		auto [element, inserted] = g_currentImState->addOrCreateElement<elements::Fill>([&]()
			{
				return eastl::make_unique<elements::Fill>(rect, color);
			});
		
		if (!inserted)
			element->update(rect, color);
	}
}

}