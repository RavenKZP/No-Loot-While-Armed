#include "Settings.h"
#include "SimpleIni.h"

void Settings::LoadSettings() {
    CSimpleIniW ini;
    ini.SetUnicode();

    if (!std::filesystem::exists(setting_path)) {
        logger::info("No {} file found, creating new with default values", setting_path);
        SaveSettings();
    } else {
        ini.LoadFile(setting_path);

        ModActive = ini.GetBoolValue(L"Settings", L"ModActive");

        Message = ini.GetBoolValue(L"Settings", L"Message");
        MessageSound = ini.GetBoolValue(L"Settings", L"MessageSound");

        AllowActionsInCombat = ini.GetBoolValue(L"Settings", L"AllowActionsInCombat");
        AutoActionsInCombat = ini.GetBoolValue(L"Settings", L"AutoActionsInCombat");
        AutoSheatle = ini.GetBoolValue(L"Settings", L"AutoSheatle");
        AutoActivate = ini.GetBoolValue(L"Settings", L"AutoActivate");
        // AutoDraw = ini.GetBoolValue(L"Settings", L"AutoDraw");

        NoMount = ini.GetBoolValue(L"Settings", L"NoMount");

        NoLootBody = ini.GetBoolValue(L"Settings", L"NoLootBody");
        NoLootContainer = ini.GetBoolValue(L"Settings", L"NoLootContainer");
        NoLootPickpocket = ini.GetBoolValue(L"Settings", L"NoLootPickpocket");

        QuickLootSupport = ini.GetBoolValue(L"Settings", L"QuickLootSupport");
        HideQLOnlyWield = ini.GetBoolValue(L"Settings", L"HideQLOnlyWhenWielding");

        NoLootFlora = ini.GetBoolValue(L"Settings", L"NoLootFlora");
        NoLootCritter = ini.GetBoolValue(L"Settings", L"NoLootCritter");

        NoLootWeapon = ini.GetBoolValue(L"Settings", L"NoLootWeapon");
        NoLootArmor = ini.GetBoolValue(L"Settings", L"NoLootArmor");
        NoLootAmmo = ini.GetBoolValue(L"Settings", L"NoLootAmmo");

        NoLootBook = ini.GetBoolValue(L"Settings", L"NoLootBook");
        NoLootNote = ini.GetBoolValue(L"Settings", L"NoLootNote");
        NoLootSpellBook = ini.GetBoolValue(L"Settings", L"NoLootSpellBook");
        NoLootSkillBook = ini.GetBoolValue(L"Settings", L"NoLootSkillBook");
        NoLootScroll = ini.GetBoolValue(L"Settings", L"NoLootScroll");

        NoLootPotion = ini.GetBoolValue(L"Settings", L"NoLootPotion");
        NoLootPoison = ini.GetBoolValue(L"Settings", L"NoLootPoison");
        NoLootFood = ini.GetBoolValue(L"Settings", L"NoLootFood");
        NoLootIngredient = ini.GetBoolValue(L"Settings", L"NoLootIngredient");

        NoLootKey = ini.GetBoolValue(L"Settings", L"NoLootKey");
        NoLootSoulGem = ini.GetBoolValue(L"Settings", L"NoLootSoulGem");
        NoLootMisc = ini.GetBoolValue(L"Settings", L"NoLootMisc");
        NoLootGold = ini.GetBoolValue(L"Settings", L"NoLootGold");
        NoLootLockpick = ini.GetBoolValue(L"Settings", L"NoLootLockpick");
        NoLootLight = ini.GetBoolValue(L"Settings", L"NoLootLight");

        NoDoor = ini.GetBoolValue(L"Settings", L"NoDoor");
        NoFurniture = ini.GetBoolValue(L"Settings", L"NoFurniture");
        NoActivators = ini.GetBoolValue(L"Settings", L"NoActivators");

        logger::info("Settings Loaded");
    }
}

void Settings::SaveSettings() {
    CSimpleIniW ini;
    ini.SetUnicode();
    ini.LoadFile(setting_path);
    ini.Reset();
    ini.SetBoolValue(L"Settings", L"ModActive", ModActive);

    ini.SetBoolValue(L"Settings", L"Message", Message);
    ini.SetBoolValue(L"Settings", L"MessageSound", MessageSound);

    ini.SetBoolValue(L"Settings", L"AllowActionsInCombat", AllowActionsInCombat);
    ini.SetBoolValue(L"Settings", L"AutoActionsInCombat", AutoActionsInCombat);

    ini.SetBoolValue(L"Settings", L"AutoSheatle", AutoSheatle);
    ini.SetBoolValue(L"Settings", L"AutoActivate", AutoActivate);
    // ini.SetBoolValue(L"Settings", L"AutoDraw", AutoDraw);

    ini.SetBoolValue(L"Settings", L"NoMount", NoMount);

    ini.SetBoolValue(L"Settings", L"NoLootBody", NoLootBody);
    ini.SetBoolValue(L"Settings", L"NoLootContainer", NoLootContainer);
    ini.SetBoolValue(L"Settings", L"NoLootPickpocket", NoLootPickpocket);

    ini.SetBoolValue(L"Settings", L"QuickLootSupport", QuickLootSupport);
    ini.SetBoolValue(L"Settings", L"HideQLOnlyWhenWielding", HideQLOnlyWield);


    ini.SetBoolValue(L"Settings", L"NoLootFlora", NoLootFlora);
    ini.SetBoolValue(L"Settings", L"NoLootCritter", NoLootCritter);

    ini.SetBoolValue(L"Settings", L"NoLootWeapon", NoLootWeapon);
    ini.SetBoolValue(L"Settings", L"NoLootArmor", NoLootArmor);
    ini.SetBoolValue(L"Settings", L"NoLootAmmo", NoLootAmmo);

    ini.SetBoolValue(L"Settings", L"NoLootBook", NoLootBook);
    ini.SetBoolValue(L"Settings", L"NoLootNote", NoLootNote);
    ini.SetBoolValue(L"Settings", L"NoLootSpellBook", NoLootSpellBook);
    ini.SetBoolValue(L"Settings", L"NoLootSkillBook", NoLootSkillBook);
    ini.SetBoolValue(L"Settings", L"NoLootScroll", NoLootScroll);

    ini.SetBoolValue(L"Settings", L"NoLootPotion", NoLootPotion);
    ini.SetBoolValue(L"Settings", L"NoLootPoison", NoLootPoison);
    ini.SetBoolValue(L"Settings", L"NoLootFood", NoLootFood);
    ini.SetBoolValue(L"Settings", L"NoLootIngredient", NoLootIngredient);

    ini.SetBoolValue(L"Settings", L"NoLootKey", NoLootKey);
    ini.SetBoolValue(L"Settings", L"NoLootSoulGem", NoLootSoulGem);
    ini.SetBoolValue(L"Settings", L"NoLootMisc", NoLootMisc);
    ini.SetBoolValue(L"Settings", L"NoLootGold", NoLootGold);
    ini.SetBoolValue(L"Settings", L"NoLootLockpick", NoLootLockpick);
    ini.SetBoolValue(L"Settings", L"NoLootLight", NoLootLight);

    ini.SetBoolValue(L"Settings", L"NoDoor", NoDoor);
    ini.SetBoolValue(L"Settings", L"NoFurniture", NoFurniture);
    ini.SetBoolValue(L"Settings", L"NoActivators", NoActivators);

    ini.SaveFile(setting_path);

    logger::info("Settings Saved");
}

void Settings::ResetSettings() {
    ModActive = true;

    Message = false;
    MessageSound = true;

    AllowActionsInCombat = true;
    AutoActionsInCombat = true;

    AutoSheatle = true;
    AutoActivate = true;
    AutoDraw = false;

    NoMount = true;

    NoLootBody = true;
    NoLootContainer = true;
    NoLootPickpocket = true;

    QuickLootSupport = true;
    HideQLOnlyWield = true;

    NoLootFlora = true;
    NoLootCritter = true;

    NoLootWeapon = true;
    NoLootArmor = true;
    NoLootAmmo = true;

    NoLootBook = true;
    NoLootNote = true;

    NoLootSpellBook = true;
    NoLootSkillBook = true;
    NoLootScroll = true;
    NoLootSoulGem = true;

    NoLootPotion = true;
    NoLootPoison = true;
    NoLootFood = true;
    NoLootIngredient = true;

    NoLootKey = true;
    NoLootMisc = true;
    NoLootGold = true;
    NoLootLockpick = true;
    NoLootLight = true;

    NoDoor = true;
    NoFurniture = true;
    NoActivators = true;

    logger::info("Settings Reseted");
}