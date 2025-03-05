#pragma once

#include "ClibUtil/singleton.hpp"

class Settings final : public clib_util::singleton::ISingleton<Settings> {
public:
    void LoadSettings();
    void SaveSettings();
    void ResetSettings();

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

private:
    const char* setting_path{"Data/SKSE/Plugins/NoLootWhileArmed.ini"};
};