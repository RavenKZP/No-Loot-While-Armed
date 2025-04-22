#include "Settings.h"
#include "SimpleIni.h"

void Settings::LoadSettings() {
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.SetMultiKey(true);

    if (!std::filesystem::exists(setting_path)) {
        logger::info("No {} file found, creating new with default values", setting_path);
        ResetSettings();
        SaveSettings();
    } else {
        ini.LoadFile(setting_path);

        ModActive = ini.GetBoolValue("Settings", "ModActive");

        Message = ini.GetBoolValue("Settings", "Message");
        MessageSound = ini.GetBoolValue("Settings", "MessageSound");

        AllowActionsInCombat = ini.GetBoolValue("Settings", "AllowActionsInCombat");
        AutoActionsInCombat = ini.GetBoolValue("Settings", "AutoActionsInCombat");
        AutoSheatle = ini.GetBoolValue("Settings", "AutoSheatle");
        AutoActivate = ini.GetBoolValue("Settings", "AutoActivate");
        // AutoDraw = ini.GetBoolValue("Settings", "AutoDraw");

        NoMount = ini.GetBoolValue("Settings", "NoMount");

        NoLootBody = ini.GetBoolValue("Settings", "NoLootBody");
        NoLootContainer = ini.GetBoolValue("Settings", "NoLootContainer");
        NoLootPickpocket = ini.GetBoolValue("Settings", "NoLootPickpocket");

        QuickLootSupport = ini.GetBoolValue("Settings", "QuickLootSupport");
        HideQLOnlyWield = ini.GetBoolValue("Settings", "HideQLOnlyWhenWielding");

        NoLootFlora = ini.GetBoolValue("Settings", "NoLootFlora");
        NoLootCritter = ini.GetBoolValue("Settings", "NoLootCritter");

        NoLootWeapon = ini.GetBoolValue("Settings", "NoLootWeapon");
        NoLootArmor = ini.GetBoolValue("Settings", "NoLootArmor");
        NoLootAmmo = ini.GetBoolValue("Settings", "NoLootAmmo");

        NoLootBook = ini.GetBoolValue("Settings", "NoLootBook");
        NoLootNote = ini.GetBoolValue("Settings", "NoLootNote");
        NoLootSpellBook = ini.GetBoolValue("Settings", "NoLootSpellBook");
        NoLootSkillBook = ini.GetBoolValue("Settings", "NoLootSkillBook");
        NoLootScroll = ini.GetBoolValue("Settings", "NoLootScroll");

        NoLootPotion = ini.GetBoolValue("Settings", "NoLootPotion");
        NoLootPoison = ini.GetBoolValue("Settings", "NoLootPoison");
        NoLootFood = ini.GetBoolValue("Settings", "NoLootFood");
        NoLootIngredient = ini.GetBoolValue("Settings", "NoLootIngredient");

        NoLootKey = ini.GetBoolValue("Settings", "NoLootKey");
        NoLootSoulGem = ini.GetBoolValue("Settings", "NoLootSoulGem");
        NoLootMisc = ini.GetBoolValue("Settings", "NoLootMisc");
        NoLootGold = ini.GetBoolValue("Settings", "NoLootGold");
        NoLootLockpick = ini.GetBoolValue("Settings", "NoLootLockpick");
        NoLootLight = ini.GetBoolValue("Settings", "NoLootLight");

        NoDoor = ini.GetBoolValue("Settings", "NoDoor");
        NoFurniture = ini.GetBoolValue("Settings", "NoFurniture");
        NoActivators = ini.GetBoolValue("Settings", "NoActivators");

        CSimpleIniA::TNamesDepend raceNames;
        ini.GetAllValues("ExcludedRaces", "ExcludeRace", raceNames);

        for (const auto& raceName : raceNames) {
            auto* form = RE::TESForm::LookupByEditorID(raceName.pItem);
            if (form) {
                if (auto* race = form->As<RE::TESRace>()) {
                    excludedRaces.insert(race);
                    logger::info("Excluded race: {}", raceName.pItem);
                }
            } else {
                logger::warn("Race '{}' not found!", raceName.pItem);
            }
        }

        logger::info("Settings Loaded");
    }
}

void Settings::SaveSettings() {
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.SetMultiKey(true);
    ini.LoadFile(setting_path);
    ini.Reset();
    ini.SetBoolValue("Settings", "ModActive", ModActive);

    ini.SetBoolValue("Settings", "Message", Message);
    ini.SetBoolValue("Settings", "MessageSound", MessageSound);

    ini.SetBoolValue("Settings", "AllowActionsInCombat", AllowActionsInCombat);
    ini.SetBoolValue("Settings", "AutoActionsInCombat", AutoActionsInCombat);

    ini.SetBoolValue("Settings", "AutoSheatle", AutoSheatle);
    ini.SetBoolValue("Settings", "AutoActivate", AutoActivate);
    // ini.SetBoolValue("Settings", "AutoDraw", AutoDraw);

    ini.SetBoolValue("Settings", "NoMount", NoMount);

    ini.SetBoolValue("Settings", "NoLootBody", NoLootBody);
    ini.SetBoolValue("Settings", "NoLootContainer", NoLootContainer);
    ini.SetBoolValue("Settings", "NoLootPickpocket", NoLootPickpocket);

    ini.SetBoolValue("Settings", "QuickLootSupport", QuickLootSupport);
    ini.SetBoolValue("Settings", "HideQLOnlyWhenWielding", HideQLOnlyWield);


    ini.SetBoolValue("Settings", "NoLootFlora", NoLootFlora);
    ini.SetBoolValue("Settings", "NoLootCritter", NoLootCritter);

    ini.SetBoolValue("Settings", "NoLootWeapon", NoLootWeapon);
    ini.SetBoolValue("Settings", "NoLootArmor", NoLootArmor);
    ini.SetBoolValue("Settings", "NoLootAmmo", NoLootAmmo);

    ini.SetBoolValue("Settings", "NoLootBook", NoLootBook);
    ini.SetBoolValue("Settings", "NoLootNote", NoLootNote);
    ini.SetBoolValue("Settings", "NoLootSpellBook", NoLootSpellBook);
    ini.SetBoolValue("Settings", "NoLootSkillBook", NoLootSkillBook);
    ini.SetBoolValue("Settings", "NoLootScroll", NoLootScroll);

    ini.SetBoolValue("Settings", "NoLootPotion", NoLootPotion);
    ini.SetBoolValue("Settings", "NoLootPoison", NoLootPoison);
    ini.SetBoolValue("Settings", "NoLootFood", NoLootFood);
    ini.SetBoolValue("Settings", "NoLootIngredient", NoLootIngredient);

    ini.SetBoolValue("Settings", "NoLootKey", NoLootKey);
    ini.SetBoolValue("Settings", "NoLootSoulGem", NoLootSoulGem);
    ini.SetBoolValue("Settings", "NoLootMisc", NoLootMisc);
    ini.SetBoolValue("Settings", "NoLootGold", NoLootGold);
    ini.SetBoolValue("Settings", "NoLootLockpick", NoLootLockpick);
    ini.SetBoolValue("Settings", "NoLootLight", NoLootLight);

    ini.SetBoolValue("Settings", "NoDoor", NoDoor);
    ini.SetBoolValue("Settings", "NoFurniture", NoFurniture);
    ini.SetBoolValue("Settings", "NoActivators", NoActivators);

    for (const auto* race : excludedRaces) {
        if (race) {
            const char* editorID = race->GetFormEditorID();
            if (editorID && *editorID) {
                ini.SetValue("ExcludedRaces", "ExcludeRace", editorID);
            }
        }
    }

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

    InitializeDefaultExcludedRaces();

    logger::info("Settings Reseted");
}

void Settings::InitializeDefaultExcludedRaces() {
    excludedRaces.clear();

     static const std::string raceNames[] = {"WerewolfBeastRace",     "DragonRace",    "DLC1VampireBeastRace",
                                             "DLC2WerebearBeastRace", "NecroLichRace", "Kata_DragonidRace"};

     for (const auto& raceName : raceNames) {
         auto* form = RE::TESForm::LookupByEditorID(raceName);
         if (form) {
             if (auto* race = form->As<RE::TESRace>()) {
                 excludedRaces.insert(race);
                 logger::info("Excluded race: {}", raceName);
             }
         } else {
             logger::warn("Race '{}' not found!", raceName);
         }
     }
 }

bool Settings::AddRaceToExclude(RE::TESRace* race) {
    if (race) {
        excludedRaces.insert(race);
        logger::info("Added race to exclusion: {}", race->GetFormEditorID());
        return true;
    }
    return false;
}

bool Settings::RemoveRaceFromExclude(RE::TESRace* race) {
    if (race) {
        auto erased = excludedRaces.erase(race);
        if (erased > 0) {
            logger::info("Removed race from exclusion: {}", race->GetFormEditorID());
            return true;
        }
    }
    return false;
}

bool Settings::AddPlayerRaceToExclude() {
    auto* player = RE::PlayerCharacter::GetSingleton();
    if (!player) return false;
    return AddRaceToExclude(player->GetRace());
}

bool Settings::RemovePlayerRaceFromExclude() {
    auto* player = RE::PlayerCharacter::GetSingleton();
    if (!player) return false;
    return RemoveRaceFromExclude(player->GetRace());
}
