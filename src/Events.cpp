#include "Events.h"
#include "Hooks.h"
#include "Utils.h"

RE::BSEventNotifyControl EventSink::ProcessEvent(const SKSE::CrosshairRefEvent* a_event, RE::BSTEventSource<SKSE::CrosshairRefEvent>*)
{
    Hooks::crosshair_ref = a_event->crosshairRef;

	if (!a_event->crosshairRef) {
		ModCompatibility::QuickLootMod::GetSingleton()->SetAllowed(true);
	}
	else if (Hooks::saved_ref != a_event->crosshairRef) {
		logger::info("CrosshairRef is a container");
	    ModCompatibility::QuickLootMod::GetSingleton()->SetAllowed(false);
	}

	return RE::BSEventNotifyControl::kContinue;
}

void EventSinks::Install()
{
	const auto a_eventsink = EventSink::GetSingleton();
	SKSE::GetCrosshairRefEventSource()->AddEventSink(a_eventsink);
}