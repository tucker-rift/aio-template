#pragma once
#include "ChampionPlugin.h"

namespace AIOTemplate
{
	class AshePlugin : public ChampionPlugin
	{
	public:
		void OnPluginRegistered() override;
		void OnRenderGame(void* userData) override {};
		void OnRenderOverlay(void* userData) override {};
		void ProcessCombo() override;
	};
}