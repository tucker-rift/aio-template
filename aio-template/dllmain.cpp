#pragma once
#include "Plugin.h"

PLUGIN_SETUP("aio-template", OnLoad); 

void __cdecl OnLoad(void* userData)
{
	LOAD_ENVIRONMENT();

	if(Player.PTR() && pSDK && pCore)
	{
		AIOTemplate::Plugin::Init();
	}
}