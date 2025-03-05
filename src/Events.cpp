#include "Events.h"
#include "Hooks.h"
#include "Settings.h"
#include "Utils.h"

RE::BSEventNotifyControl EventSink::ProcessEvent(const SKSE::CrosshairRefEvent* a_event,
                                                 RE::BSTEventSource<SKSE::CrosshairRefEvent>*) {
    Hooks::crosshair_ref = a_event->crosshairRef;
    if (ModCompatibility::QuickLootMod::GetSingleton()->is_installed) {
        if (Settings::GetSingleton()->QuickLootSupport) {
            if (!Hooks::saved_ref) {
                ModCompatibility::QuickLootMod::GetSingleton()->SetAllowed(false);
            } else if (a_event->crosshairRef && Hooks::saved_ref->GetFormID() != a_event->crosshairRef->GetFormID()) {
                ModCompatibility::QuickLootMod::GetSingleton()->SetAllowed(false);
            }
        } else {
            ModCompatibility::QuickLootMod::GetSingleton()->SetAllowed(true);
        }
    }

    return RE::BSEventNotifyControl::kContinue;
}

void EventSinks::Install() {
    const auto a_eventsink = EventSink::GetSingleton();
    SKSE::GetCrosshairRefEventSource()->AddEventSink(a_eventsink);
}