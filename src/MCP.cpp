#include"MCP.h"
#include"Utils.h"
#include"Settings.h"
#include"SKSEMCP/utils.hpp"

void MCP::Register() {
    if (!SKSEMenuFramework::IsInstalled()) {
		logger::warn("SKSEMenuFramework is not installed.");
		return;
	}
    SKSEMenuFramework::SetSection("No Loot When Armed");
    SKSEMenuFramework::AddSectionItem("Settings", RenderSettings);
#ifndef NDEBUG
    SKSEMenuFramework::AddSectionItem("Log", RenderLog);
#endif

}

void __stdcall MCP::RenderSettings()
{
    Settings* set = Settings::GetSingleton();
    if (ImGui::Button("Save Settings")) {
        set->SaveSettings();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset Settings")) {
        set->ResetSettings();
    }

    ImGui::Text("No Loot When Armed");
    ImGui::Checkbox("Mod Active", &set->ModActive);

    if (set->ModActive == false) {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.1f);
    }

    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Message", &set->Message);
    ImGui::SameLine();
    ImGui::SetCursorPosX(400);
    ImGui::Checkbox("Sound", &set->MessageSound);

    ImGui::Text("");
    ImGui::Text("Automated actions");
    ImGui::Checkbox("No Auto Actions In Combat", &set->NoAutoActionsInCombat);
    ImGui::Checkbox("Sheatle", &set->AutoSheatle);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);

    if (set->AutoSheatle == false) {
        set->AutoActivate = false;
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.1f);
    }
    ImGui::Checkbox("Activate", &set->AutoActivate);
    //ImGui::SameLine();
    //ImGui::SetCursorPosX(400);
    //ImGui::Checkbox("Draw", &set->AutoDraw);
    if (set->AutoSheatle == false) {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }

    ImGui::Text("");
    ImGui::Text("Mount, Horse");
    ImGui::Checkbox("Mount", &set->NoMount);

    ImGui::Text("");
    ImGui::Text("Inventory, Chests");
    ImGui::Checkbox("Dead Body", &set->NoLootBody);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Containers", &set->NoLootContainer);
    ImGui::SameLine();
    ImGui::SetCursorPosX(400);
    ImGui::Checkbox("Pickopcket", &set->NoLootPickpocket);

    ImGui::Text("");
    ImGui::Text("Fauna and Flora");
    ImGui::Checkbox("Flora", &set->NoLootFlora);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Critter", &set->NoLootCritter);

    ImGui::Text("");
    ImGui::Text("Items");
    ImGui::Checkbox("Weapon", &set->NoLootWeapon);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Armor", &set->NoLootArmor);
    ImGui::SameLine();
    ImGui::SetCursorPosX(400);
    ImGui::Checkbox("Ammo", &set->NoLootAmmo);

    ImGui::Checkbox("Food", &set->NoLootFood);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Potion", &set->NoLootPotion);
    ImGui::SameLine();
    ImGui::SetCursorPosX(400);
    ImGui::Checkbox("Poison", &set->NoLootPoison);
    ImGui::SameLine();
    ImGui::SetCursorPosX(600);
    ImGui::Checkbox("Ingredient", &set->NoLootIngredient);

    ImGui::Checkbox("Book", &set->NoLootBook);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Skill Book", &set->NoLootSkillBook);
    ImGui::SameLine();
    ImGui::SetCursorPosX(400);
    ImGui::Checkbox("Spell Book", &set->NoLootSpellBook);

    ImGui::Checkbox("Scrool", &set->NoLootScroll);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Soul Gem", &set->NoLootSoulGem);

    //ImGui::SameLine();
    //ImGui::Checkbox("Note", &set->NoLootNote);

    ImGui::Checkbox("Key", &set->NoLootKey);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Lockpick", &set->NoLootLockpick);

    ImGui::Checkbox("Gold", &set->NoLootGold);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Misc", &set->NoLootMisc);
    ImGui::SameLine();
    ImGui::SetCursorPosX(400);
    ImGui::Checkbox("Light", &set->NoLootLight);

    ImGui::Text("");
    ImGui::Text("Furnitures, WorkBench, Beds, Chairs, Doors");
    ImGui::Checkbox("Doors", &set->NoDoor);
    ImGui::SameLine();
    ImGui::SetCursorPosX(200);
    ImGui::Checkbox("Furnitures", &set->NoFurniture);

    ImGui::Text("");
    ImGui::Text("Activators, Buttons, Leavers");
    ImGui::Checkbox("Activators", &set->NoActivators);    

    
    if (set->ModActive == false) {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}


void __stdcall MCP::RenderLog()
{
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
