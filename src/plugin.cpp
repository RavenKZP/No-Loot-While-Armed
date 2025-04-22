#include "Events.h"
#include "logger.h"
#include "Hooks.h"
#include "Settings.h"
#include "MCP.h"
#include "Utils.h"

void OnMessage(SKSE::MessagingInterface::Message* message) {
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        Settings::GetSingleton()->LoadSettings();
        MCP::Register();

        ModCompatibility::Install();
        Hooks::Install();
        EventSinks::Install();
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SetupLog();
    logger::info("Plugin loaded");
    SKSE::Init(skse);
    logger::info("Game version: {}", skse->RuntimeVersion().string());
    SKSE::GetMessagingInterface()->RegisterListener(OnMessage);
    return true;
}
