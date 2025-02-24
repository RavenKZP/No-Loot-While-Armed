#include "Events.h"
#include "Hooks.h"

RE::BSEventNotifyControl EventSink::ProcessEvent(const SKSE::CrosshairRefEvent* a_event, RE::BSTEventSource<SKSE::CrosshairRefEvent>*)
{
    Hooks::crosshair_ref = a_event->crosshairRef;
	return RE::BSEventNotifyControl::kContinue;
}
