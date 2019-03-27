#pragma once
#include "ChampionPlugin.h"

namespace AIOTemplate
{
	class ModeProcessor
	{
	public:
		ModeProcessor(ChampionPlugin* plugin)
		{
			this->plugin = plugin; 
		};
		bool IsReady() { return this->plugin != nullptr;  }
		virtual void Process(std::vector<std::shared_ptr<Spell::SpellBase>>) = 0;
	protected:
		ChampionPlugin* plugin;
	};
}
