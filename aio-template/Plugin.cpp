#include "Plugin.h"
#include "AshePlugin.h"

using namespace AIOTemplate; 

static std::shared_ptr<ChampionPlugin> championPlugin; 

std::shared_ptr<ChampionPlugin> Plugin::GetChampionPlugin()
{
	if (championPlugin) return championPlugin;
	// ------- ADD CHAMPIONS BELOW THIS LINE  -------

	if (strcmp(Player.GetCharName(), "Ashe") == 0) 
		championPlugin = std::make_shared<AshePlugin>();
	
	//  ----------------------------------------------
	if (championPlugin) championPlugin->RegisterPlugin(); 
	return championPlugin;
}


void Plugin::Init()
{
	GetChampionPlugin();
}

