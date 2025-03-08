#include"MCP.h"
#include"Utils.h"
#include <ranges>
#include"Settings.h"
#include"SKSEMCP/utils.hpp"

namespace {
    bool* GetSetting(const std::string_view& checkbox_name) {
	    const auto set = Settings::GetSingleton();
	    if (checkbox_name == "Mod Active") return &set->ModActive;
	    if (checkbox_name == "Message") return &set->Message;
	    if (checkbox_name == "Sound") return &set->MessageSound;
		if (checkbox_name == "Allow Actions In Combat") return &set->AllowActionsInCombat;
		if (checkbox_name == "Auto Actions In Combat") return &set->AutoActionsInCombat;
		if (checkbox_name == "Sheathe") return &set->AutoSheatle;
		if (checkbox_name == "Activate") return &set->AutoActivate;
		if (checkbox_name == "Mount") return &set->NoMount;
		if (checkbox_name == "Dead Body") return &set->NoLootBody;
		if (checkbox_name == "Containers") return &set->NoLootContainer;
		if (checkbox_name == "Pickpocket") return &set->NoLootPickpocket;
		if (checkbox_name == "QuickLoot Support") return &set->QuickLootSupport;
		if (checkbox_name == "Hide Menu Only When Wielding") return &set->HideQLOnlyWield;
		if (checkbox_name == "Flora") return &set->NoLootFlora;
		if (checkbox_name == "Critter") return &set->NoLootCritter;
		if (checkbox_name == "Weapon") return &set->NoLootWeapon;
		if (checkbox_name == "Armor") return &set->NoLootArmor;
		if (checkbox_name == "Ammo") return &set->NoLootAmmo;
		if (checkbox_name == "Food") return &set->NoLootFood;
		if (checkbox_name == "Potion") return &set->NoLootPotion;
		if (checkbox_name == "Poison") return &set->NoLootPoison;
		if (checkbox_name == "Ingredient") return &set->NoLootIngredient;
		if (checkbox_name == "Book") return &set->NoLootBook;
		if (checkbox_name == "Skill Book") return &set->NoLootSkillBook;
		if (checkbox_name == "Spell Book") return &set->NoLootSpellBook;
		if (checkbox_name == "Scroll") return &set->NoLootScroll;
		if (checkbox_name == "Soul Gem") return &set->NoLootSoulGem;
		if (checkbox_name == "Key") return &set->NoLootKey;
		if (checkbox_name == "Lockpick") return &set->NoLootLockpick;
		if (checkbox_name == "Gold") return &set->NoLootGold;
		if (checkbox_name == "Misc") return &set->NoLootMisc;
		if (checkbox_name == "Light") return &set->NoLootLight;
		if (checkbox_name == "Furniture") return &set->NoFurniture;
		if (checkbox_name == "Doors") return &set->NoDoor;
		if (checkbox_name == "Activators") return &set->NoActivators;
	    return nullptr;
    }
    void RenderDisableFlags(const std::string_view& checkbox_name) {
		static const std::set<std::string_view> disabler_settings = {
			"Mod Active",
			"Sheathe",
		};
        if (disabler_settings.contains(checkbox_name)) {
			if (*GetSetting(checkbox_name) == false) {
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.1f);
			}
        }
    }
	void RenderCheckBox(const std::string& checkbox_name,const std::string& a_label) {
        if (bool* setting = GetSetting(checkbox_name)) {
			ImGui::Checkbox((checkbox_name + "##" + a_label).c_str(), setting);
		}
        else {
			logger::warn("Unknown checkbox name: {}", checkbox_name);
        }
	}

	void CollapseAll() {
		for (auto& section : MCP::SettingsMCP::sections) {
			section.collapsed = true;
		}
	}

	void ExpandAll() {
		for (auto& section : MCP::SettingsMCP::sections) {
			section.collapsed = false;
		}
	}

	std::vector<std::string>
    slice(const std::vector<std::string>& cbs, const int begin, const int end) {
        return { cbs.begin() + begin, cbs.begin() + end };
    }

    template<int... Ends>
    void makeSection(const std::string& label, const std::vector<std::string>& cbs)
    {
		using namespace MCP::SettingsMCP;
        std::map<size_t, std::vector<std::string>> rows;
        int rowIndex = 0;
        int begin = 0;
        ((rows[rowIndex++] = slice(cbs, begin, Ends), begin = Ends), ...);
        const Section a_section{label, rows};
	    sections.push_back(a_section);
    }

}


void MCP::Register() {
    if (!SKSEMenuFramework::IsInstalled()) {
		logger::warn("SKSEMenuFramework is not installed.");
		return;
	}
    SKSEMenuFramework::SetSection("No Loot When Armed");
    SettingsMCP::CreateSettingsSections();
    SKSEMenuFramework::AddSectionItem("Settings", RenderSettings);
#ifndef NDEBUG
    SKSEMenuFramework::AddSectionItem("Log", RenderLog);
#endif
}

void __stdcall MCP::RenderSettings() {
    Settings* set = Settings::GetSingleton();
    if (ImGui::Button("Save Settings")) {
        set->SaveSettings();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset Settings")) {
        set->ResetSettings();
    }

	if (ImGui::Button("Expand All")) ExpandAll();
	ImGui::SameLine();
	if (ImGui::Button("Collapse All")) CollapseAll();

	using namespace SettingsMCP;

	for (auto& section : sections) {

	    if (section.label == "Quick Loot") {
			if (!ModCompatibility::QuickLootMod::GetSingleton()->is_installed) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.1f);
            }
		}

		section.Render();

		if (section.label == "Automated Actions") {
            if (set->AutoSheatle == false) {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }
		}
		if (section.label == "Quick Loot") {
			if (!ModCompatibility::QuickLootMod::GetSingleton()->is_installed) {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }
		}
	}

    if (set->ModActive == false) {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}


void __stdcall MCP::RenderLog() {
    ImGui::Checkbox("Trace", &LogSettings::log_trace);
    ImGui::SameLine();
    ImGui::Checkbox("Info", &LogSettings::log_info);
    ImGui::SameLine();
    ImGui::Checkbox("Warning", &LogSettings::log_warning);
    ImGui::SameLine();
    ImGui::Checkbox("Error", &LogSettings::log_error);

    // if"Generate Log" button is pressed, read the log file
    if (ImGui::Button("Generate Log")) {
        logLines = ReadLogFile();
    }

    // Display each line in a new ImGui::Text() element
    for (const auto& line : logLines) {
        if (line.find("trace") != std::string::npos && !LogSettings::log_trace) continue;
        if (line.find("info") != std::string::npos && !LogSettings::log_info) continue;
        if (line.find("warning") != std::string::npos && !LogSettings::log_warning) continue;
        if (line.find("error") != std::string::npos && !LogSettings::log_error) continue;
        ImGui::Text(line.c_str());
    }
}

MCP::SettingsMCP::Section::Section(std::string a_label, const std::map<size_t, std::vector<std::string>>& checkboxes) : checkboxes(checkboxes), label(std::move(
    a_label)) {
	if (label == "Automated Actions") spacing = 400.0f;
	if (label == "Quick Loot") spacing = 300.0f;
}

void MCP::SettingsMCP::Section::Render()
{
	ImGui::SetNextItemOpen(!collapsed);

	if (ImGui::CollapsingHeader((label+"##collapsable").c_str(),ImGuiTreeNodeFlags_DefaultOpen)) {

		collapsed = false;

		if (ImGui::Button(std::string("Enable All").append("##" + label).c_str())) {
			for (const auto& cboxes : (checkboxes | std::views::values)) {
				for (const auto& cb : cboxes) {
					if (bool* setting = GetSetting(cb)) {
						*setting = true;
					}
				}
			}
		}
		ImGui::SameLine();
		if (ImGui::Button(std::string("Disable All").append("##" + label).c_str())) {
			for (const auto& cboxes : (checkboxes | std::views::values)) {
				for (const auto& cb : cboxes) {
					if (bool* setting = GetSetting(cb)) {
						*setting = false;
					}
				}
			}
        }

	    for (const auto& cboxes : (checkboxes | std::views::values)) {
		    size_t index = 0;
		    for (const auto& cb : cboxes) {
                if (index>0) ImGui::SetCursorPosX(spacing*index);
                RenderCheckBox(cb,label);
                RenderDisableFlags(cb);
                if (index < cboxes.size() - 1) ImGui::SameLine();
                ++index;
            }
        }
	}
	else {
		collapsed = true;
	}
}

void MCP::SettingsMCP::CreateSettingsSections()
{
#define SVEC(...) std::vector<std::string>{ __VA_ARGS__ }
#define CREATE_SECTION(LABEL, CHECKBOXES, ...) makeSection<__VA_ARGS__>(LABEL, CHECKBOXES)

        CREATE_SECTION("General", SVEC("Mod Active", "Message", "Sound"), 3);
		CREATE_SECTION("Automated Actions",SVEC("Allow Actions In Combat", "Auto Actions In Combat", "Sheathe", "Activate"), 2, 4);
		CREATE_SECTION("Mount",SVEC("Mount"),1);
		CREATE_SECTION("Inventory", SVEC("Dead Body", "Containers", "Pickpocket"), 3);
		CREATE_SECTION("Quick Loot", SVEC("QuickLoot Support","Hide Menu Only When Wielding"), 2);
		CREATE_SECTION("Fauna and Flora", SVEC("Flora", "Critter"), 2);
		CREATE_SECTION("Items", 
			SVEC("Weapon", "Armor", "Ammo", 
				"Food", "Potion", "Poison", "Ingredient",
				"Book", "Skill Book", "Spell Book", 
				"Scroll","Soul Gem",
				"Key", "Lockpick", 
				"Gold", "Misc", "Light"), 
			    3, 7, 10, 12, 14, 17);
		CREATE_SECTION("Furniture and Doors", SVEC("Furniture", "Doors"), 2);
		CREATE_SECTION("Activators/Buttons/Levers", SVEC("Activators"), 1);

#undef SVEC
#undef CREATE_SECTION
}
