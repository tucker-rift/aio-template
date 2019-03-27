#pragma once
#include "../rift-sdk-extensions/Include/SDK Extensions.h"

namespace AIOTemplate
{
	class ChampionPlugin
	{
	public:
		void RegisterPlugin();
		void DeclareSpell(SpellSlot slot, SkillStage stage, std::shared_ptr<Spell::SpellBase>);
		std::shared_ptr<Spell::SpellBase> GetSpell(SpellSlot slot, SkillStage stage = SkillStage::Default);

		virtual void OnObjectCreated(void* object, unsigned int netID, void* userData) {};
		virtual void OnObjectRemoved(void* object, unsigned int netID, void* userData) {};
		virtual void OnAttack(void* ai, void* target, bool start, bool stop, void* userData) {};
		virtual void OnUpdate(void* userData) {};
		virtual void OnTick(void* userData) {};
		virtual void OnRenderGame(void* userData) {};
		virtual void OnRenderOverlay(void* userData) {};
		virtual void OnProcessSpell(void* ai, PSDK_SPELL_CAST cast, void* userData) {};
		virtual void OnCastSpell(void* ai, PSDK_SPELL_CAST cast, void* userData) {};
		virtual void OnPreCast(bool* process, PSDK_SPELL spell, Vector3* position, AttackableUnit** target) {};
		virtual void OnRecall(void* hero, const char* name, const char* type, void* userData) {};
		virtual void OnHeroEnterView(AIHeroClient* hero) {};
		virtual void OnHeroExitView(AIHeroClient* hero) {};

		virtual void ProcessCombo() {};
		virtual void ProcessLaneClear() {};
		virtual void ProcessFlee() {};
		virtual void ProcessHarass() {};

		virtual void OnPluginRegistered() {}

	protected:
		std::map<SkillStage, std::map<SpellSlot, std::shared_ptr<Spell::SpellBase>>> spells; 
	};
}
