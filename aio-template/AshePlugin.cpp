#include "AshePlugin.h"
#include "ModeProcessor.h"
#include "AsheComboProcessor.hpp"

using namespace AIOTemplate;

AsheComboProcessor comboProcessor = AsheComboProcessor(nullptr);


void AshePlugin::OnPluginRegistered()
{
	auto w = Player.GetSpell(1);
	auto e = Player.GetSpell(2);
	auto r = Player.GetSpell(3);

	DeclareSpell(SpellSlot::Q, SkillStage::Default, std::make_shared<Spell::Active>(SpellSlot::Q));
	DeclareSpell(SpellSlot::W, SkillStage::Default, std::make_shared<Spell::Skillshot>(SpellSlot::W, w.CastRange, SkillshotType::Cone, w.CastDelay, w.MissileSpeed, w.LineWidth, DamageType::Physical, true));
	DeclareSpell(SpellSlot::E, SkillStage::Default, std::make_shared<Spell::Skillshot>(SpellSlot::E, e.CastRange, SkillshotType::Line, e.CastDelay, e.MissileSpeed, e.LineWidth, DamageType::Physical, true));
	DeclareSpell(SpellSlot::R, SkillStage::Default, std::make_shared<Spell::Skillshot>(SpellSlot::R, r.CastRange, SkillshotType::Line, r.CastDelay, r.MissileSpeed, r.LineWidth, DamageType::Magical, true));

	comboProcessor = AsheComboProcessor(this);
	SdkDisplayChatLocalPlayer("This sends text to the player's chatbox. (Only the scripter can see this)", CHAT_FLAG_GREEN);
}

void AshePlugin::ProcessCombo()
{
	if(!comboProcessor.IsReady())
	{
		comboProcessor = AsheComboProcessor(this);
		return;
	}
	
	comboProcessor.Process({
		GetSpell(SpellSlot::Q, SkillStage::Default),
		GetSpell(SpellSlot::W, SkillStage::Default),
		GetSpell(SpellSlot::E, SkillStage::Default),
		GetSpell(SpellSlot::R, SkillStage::Default)
	});
}
