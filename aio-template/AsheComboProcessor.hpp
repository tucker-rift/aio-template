#include "Plugin.h"
#include "ModeProcessor.h"


namespace AIOTemplate
{
	class AsheComboProcessor : public ModeProcessor
	{
	public:
		AsheComboProcessor(AshePlugin* plugin) : ModeProcessor(plugin) {}
		void Process(std::vector<std::shared_ptr<Spell::SpellBase>> spells) override
		{
			auto spellQ = cast<Spell::Active>(spells.at(0));
			auto spellW = cast<Spell::Skillshot>(spells.at(1));
			auto spellE = cast<Spell::Skillshot>(spells.at(2));
			auto spellR = cast<Spell::Skillshot>(spells.at(3));


			// Cast abilities if they're available, just because this is a template.
			if (spellQ->IsReady() && Player.GetResource(ABILITY_TYPE_MANA).Current > spellQ->ManaCost()) spellQ->Cast();
			if (spellW->IsReady() && Player.GetResource(ABILITY_TYPE_MANA).Current > spellW->ManaCost()) spellW->Cast(&Player);
			if (spellE->IsReady() && Player.GetResource(ABILITY_TYPE_MANA).Current > spellE->ManaCost()) spellE->Cast(&Player);
			if (spellR->IsReady() && Player.GetResource(ABILITY_TYPE_MANA).Current > spellR->ManaCost()) spellR->Cast(&Player);
		}
	};
}
