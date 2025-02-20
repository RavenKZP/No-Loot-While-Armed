#include "Events.h"
#include "Hooks.h"

RE::BSEventNotifyControl EventSink::ProcessEvent(const SKSE::CrosshairRefEvent* a_event, RE::BSTEventSource<SKSE::CrosshairRefEvent>*)
{
    Hooks::crosshair_ref = a_event->crosshairRef;
	if (Hooks::crosshair_ref) {
		logger::trace("Crosshair ref set to {}", Hooks::crosshair_ref->GetName());
	}
	else {
		logger::trace("Crosshair ref is null");
	}
	return RE::BSEventNotifyControl::kContinue;
}
