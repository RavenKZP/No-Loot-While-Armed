#include "Animation.h"
#include "Hooks.h"

RE::BSEventNotifyControl AnimationEventSink::ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>*)
{
	//logger::info("AnimationEventSink::ProcessEvent: {} {}", a_event->tag, a_event->payload);
    if (const RE::BSFixedString& eventTag = a_event->tag; eventTag == "IdleStop") {
        CleanupAnimationEvent(this);
        Hooks::blocked.store(false);
        if (const auto ref = Hooks::crosshair_ref) {
            if (ref == Hooks::saved_ref) {
                const auto player = RE::PlayerCharacter::GetSingleton();

                const auto player_controls = RE::PlayerControls::GetSingleton();
                if (const auto activate_handler = player_controls->activateHandler) {
                    player->AsActorState()->actorState2.weaponState = RE::WEAPON_STATE::kSheathed;
                    if (const auto button_event = GetOrCreateActivateEvent()) {
                        if (activate_handler->CanProcess(button_event)) {
                            const auto id_code = static_cast<int32_t>(button_event->idCode);
                            const auto device = button_event->device.get();
                            const auto input_event_q = RE::BSInputEventQueue::GetSingleton();
                            input_event_q->PushOntoInputQueue(button_event);
                            input_event_q->AddButtonEvent(device, id_code, 1.f, 0.005f);
                            input_event_q->AddButtonEvent(device, id_code, 0.f, 0.01f);
                        }
                    }
                }
            }
        }
    }
	return RE::BSEventNotifyControl::kContinue;
}

void CleanupAnimationEvent(AnimationEventSink* eventSink)
{
    RE::PlayerCharacter::GetSingleton()->RemoveAnimationGraphEventSink(eventSink);
}

AnimationEventSink* GetOrCreateEventSink()
{
	if (currentAnimationEventSink) {
		return currentAnimationEventSink.get();
	}
    const auto eventSink = new AnimationEventSink();
	currentAnimationEventSink.reset(eventSink);
	return eventSink;
}

RE::ButtonEvent* GetOrCreateActivateEvent()
{
	if (activate_event) {
		return activate_event;
	}
	const auto controlmap = RE::ControlMap::GetSingleton();
    constexpr auto device = RE::INPUT_DEVICE::kKeyboard;
	const auto activate_key = controlmap->GetMappedKey(RE::UserEvents::GetSingleton()->activate,device);
	const auto event = RE::ButtonEvent::Create(device,RE::UserEvents::GetSingleton()->activate,activate_key,1.f,0.f);
	activate_event = event;
	return event;
}
