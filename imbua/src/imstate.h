#pragma once
#include <bua/imbua.h>

#include <typeindex>
#include <EASTL/hash_map.h>
#include <EASTL/functional.h>

namespace bua
{

struct ImState
{
	Context context;

	struct ElementInfo
	{
		Element* element;
	};

	struct TypeMapEntry
	{
		u32 idCounter = 0;
		eastl::hash_map<im::ElementId, ElementInfo> elementMap;
	};

	using TypeId = size_t;
	eastl::hash_map<TypeId, TypeMapEntry> typeMap;

	void onBeginRender();

	template<typename ElementT>
	eastl::pair<ElementT*, bool> addOrCreateElement(eastl::function<eastl::unique_ptr<ElementT>()> creationFunc)
	{
		const auto typeId = typeid(ElementT).hash_code();
		auto& typeEntry = typeMap[typeId];

		const auto elementId = (im::ElementId)++typeEntry.idCounter;
		auto [kvp, inserted] = typeEntry.elementMap.insert(elementId);

		if (inserted)
		{
			size_t index = context.elements.size();
			context.elements.push_back(creationFunc());
			kvp->second = ElementInfo{ context.elements.back().get() };
		}

		return eastl::make_pair(static_cast<ElementT*>(kvp->second.element), inserted);
	}
};

extern eastl::unique_ptr<ImState> g_currentImState;

}