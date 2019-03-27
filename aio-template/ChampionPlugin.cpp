#include "ChampionPlugin.h"
#include "Plugin.h"

using namespace AIOTemplate;

#pragma region SDK Callbacks
static void _cdecl RenderOverlayCallback(_In_ void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnRenderOverlay(userData);
}

static void _cdecl RenderGameCallback(_In_ void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnRenderGame(userData);
}

static void _cdecl UpdateCallback(_In_ void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) {
		plugin->OnUpdate(userData);
		if (pCore->Orbwalker->IsModeActive(OrbwalkingMode::Combo)) plugin->ProcessCombo();
		if (pCore->Orbwalker->IsModeActive(OrbwalkingMode::LaneClear)) plugin->ProcessLaneClear();
		if (pCore->Orbwalker->IsModeActive(OrbwalkingMode::Mixed)) plugin->ProcessHarass();
		if (pCore->Orbwalker->IsModeActive(OrbwalkingMode::Flee)) plugin->ProcessFlee();
	}
}

static void _cdecl TickCallback(_In_ void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnTick(userData);
}

static void _cdecl RecallCallback(void* hero, const char* name, const char* type, void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnRecall(hero, name, type, userData);
}


static void _cdecl GainVisionCallback(AIHeroClient* hero)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnHeroEnterView(hero);
}

static void _cdecl LoseVisionCallback(AIHeroClient* hero)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnHeroExitView(hero);
}

static void _cdecl CreateObjectCallback(void* object, unsigned int netID, void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnObjectCreated(object, netID, userData);
}

static void _cdecl DeleteObjectCallback(void* object, unsigned int netID, void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnObjectRemoved(object, netID, userData);
}

static void _cdecl EndSpellCallback(void* ai, PSDK_SPELL_CAST cast, void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnCastSpell(ai, cast, userData);
}

static void _cdecl StartCastCallback(void* ai, PSDK_SPELL_CAST cast, void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnProcessSpell(ai, cast, userData);
}

static void _cdecl PreCastCallback(bool* process, PSDK_SPELL spell, Vector3* position, AttackableUnit** target)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnPreCast(process, spell, position, target);
}

static void _cdecl AttackCallback(void* ai, void* target, bool start, bool stop, void* userData)
{
	auto plugin = Plugin::GetChampionPlugin();
	if (plugin) plugin->OnAttack(ai, target, start, stop, userData); 
}

#pragma endregion

void ChampionPlugin::RegisterPlugin()
{
	pSDK->EventHandler->RegisterCallback(CallbackEnum::Overlay, RenderOverlayCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::Update, RenderGameCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::Update, UpdateCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::Tick, TickCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::Recall, RecallCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::CreateObject, CreateObjectCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::DeleteObject, DeleteObjectCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::GainVision, GainVisionCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::LoseVision, LoseVisionCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::PreCast, PreCastCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::SpellCastStart, StartCastCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::SpellCastEnd, EndSpellCallback);
	pSDK->EventHandler->RegisterCallback(CallbackEnum::Attack, AttackCallback);
	OnPluginRegistered();
}


void ChampionPlugin::DeclareSpell(SpellSlot slot, SkillStage stage, std::shared_ptr<Spell::SpellBase> spell)
{
	auto it = spells.find(stage);
	if(it != spells.end())
	{
		auto& vec = it->second;
		vec.insert_or_assign(slot, spell); 
	}
	else
	{
		spells.insert_or_assign(stage, std::map<SpellSlot, std::shared_ptr<Spell::SpellBase>>{ { slot, spell } });
	}
}


std::shared_ptr<Spell::SpellBase> ChampionPlugin::GetSpell(SpellSlot slot, SkillStage stage)
{
	auto stageIt = spells.find(stage);
	if(stageIt != spells.end())
	{
		auto& m = stageIt->second;
		auto slotIt = m.find(slot);
		if(slotIt != m.end())
		{
			return slotIt->second; 
		}
	}
	return nullptr; 
}
