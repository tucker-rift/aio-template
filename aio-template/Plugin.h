#pragma once
#include "ChampionPlugin.h"
#include <memory>

namespace AIOTemplate
{
	// Used for casting shared_ptr's between sub & base class references. 
	template <typename TOUT, typename TIN>
	inline std::shared_ptr<TOUT> cast(TIN in)
	{
		return std::static_pointer_cast<TOUT>(in);
	}

	class Plugin
	{
	public:
		static void Init();
		static std::shared_ptr<ChampionPlugin> GetChampionPlugin();
	};
}
