#include "Events.h"
#include "logger.h"
#include "Hooks.h"

void OnMessage(SKSE::MessagingInterface::Message* message) {
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        Hooks::Install();
		SKSE::GetCrosshairRefEventSource()->AddEventSink(EventSink::GetSingleton());
    }
    if (message->type == SKSE::MessagingInterface::kNewGame || message->type == SKSE::MessagingInterface::kPostLoadGame) {
        // Post-load
    }
}

SKSEPluginLoad(const SKSE::LoadInterface *skse) {

    SetupLog();
    logger::info("Plugin loaded");
    SKSE::Init(skse);
    logger::info("Game version: {}", skse->RuntimeVersion().string());
    SKSE::GetMessagingInterface()->RegisterListener(OnMessage);
    return true;
}
