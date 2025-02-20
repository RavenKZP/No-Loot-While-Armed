#pragma once

namespace Settings {
    inline const char* setting_path{"Data/SKSE/Plugins/NoLootWhileArmed.ini"};

    void LoadSettings();
    void SaveSettings();
    void ResetSettings();

    inline bool ModActive = true;

    // Display Message
    inline bool Message = false;

    // Auto Sheatle when out of combat
    inline bool AutoSheatle = true;
    
    // Inventory
    inline bool NoLootBody = true;
    inline bool NoLootContainer = true;
    inline bool NoLootPickpocket = true;

    // World Objects
    inline bool NoLootFlora = true;
    inline bool NoLootBugs = true;

    // Items
    inline bool NoLootWeapon = true;
    inline bool NoLootArmor = true;
    inline bool NoLootBook = true;
    inline bool NoLootPotion = true;
    inline bool NoLootFood = true;
    inline bool NoLootScrool = true;
    inline bool NoLootIngredient = true;
    inline bool NoLootKey = true;
    inline bool NoLootSoulGem = true;
    inline bool NoLootMisc = true;
    inline bool NoLootLight = true;
    
    // Open Dors
    inline bool NoLootDoor = false;

    // Use Furniture (Sit)
    inline bool NoLootFurniture = true;

    // Leavers, Buttons
    inline bool NoLootActivators = true;
}