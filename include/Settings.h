#pragma once

#include <unordered_set>

#include "ClibUtil/singleton.hpp"

class Settings final : public clib_util::singleton::ISingleton<Settings> {
public:
    void LoadSettings();
    void SaveSettings() const;
    void ResetSettings();

    void InitializeDefaultExcludedRaces();
    bool AddRaceToExclude(RE::TESRace* race);
    bool RemoveRaceFromExclude(RE::TESRace* race);
    bool AddPlayerRaceToExclude();
    bool RemovePlayerRaceFromExclude();

    // Kill Switch
    bool ModActive = true;

    // Display Message
    bool Message = false;
    bool MessageSound = true;

    // Automated actions
    bool AllowActionsInCombat = true;
    bool AutoActionsInCombat = true;

    bool AutoSheatle = true;
    bool AutoActivate = true;
    bool AutoDraw = false;

    // Mout, Horse
    bool NoMount = true;

    // Inventory
    bool NoLootBody = true;
    bool NoLootContainer = true;
    bool NoLootPickpocket = true;

    //QuickLoot
    bool QuickLootSupport = true;
    bool HideQLOnlyWield = true;

    // Fauna and Flora
    bool NoLootFlora = true;
    bool NoLootCritter = true;

    // Items
    bool NoLootWeapon = true;
    bool NoLootArmor = true;
    bool NoLootAmmo = true;

    bool NoLootBook = true;
    bool NoLootNote = true;
    bool NoLootSpellBook = true;
    bool NoLootSkillBook = true;
    bool NoLootScroll = true;

    bool NoLootPotion = true;
    bool NoLootPoison = true;
    bool NoLootFood = true;
    bool NoLootIngredient = true;

    bool NoLootKey = true;
    bool NoLootSoulGem = true;
    bool NoLootMisc = true;
    bool NoLootGold = true;
    bool NoLootLockpick = true;
    bool NoLootLight = true;

    // Open Doors
    bool NoDoor = true;

    // Use Furniture (Sit)
    bool NoFurniture = true;

    // Leavers, Buttons
    bool NoActivators = true;

    //ExcludedRaces
    std::unordered_set<RE::TESRace*> excludedRaces;

private:
    const char* setting_path{"Data/SKSE/Plugins/NoLootWhileArmed.ini"};
};