#include "Animation.h"

#include "Hooks.h"
#include "Utils.h"

RE::BSEventNotifyControl AnimationEventSink::ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>*)
{
	//logger::info("AnimationEventSink::ProcessEvent: {} {}", a_event->tag, a_event->payload);
	if (const RE::BSFixedString& eventTag = a_event->tag; eventTag == "IdleStop") {
		CleanupAnimationEvent(this);
		//SKSE::GetTaskInterface()->AddTask([]() {
			if (const auto ref = Hooks::crosshair_ref) {
				const auto player = RE::PlayerCharacter::GetSingleton();
				const auto a_obj = ref->GetBaseObject();
				
				//if (!a_obj->Activate(ref.get(), player, 0, a_obj, 1)) {
				//	logger::error("Failed to activate {}", ref->GetName());
				//}
				//else {
					//logger::trace("Activated {}", ref->GetName());
				auto player_controls = RE::PlayerControls::GetSingleton();
				if (auto activate_handler = player_controls->activateHandler) {
					if (auto player_controls_data = &player_controls->data) {
						player->AsActorState()->actorState2.weaponState = RE::WEAPON_STATE::kSheathed;
						if (auto button_event = GetOrCreateActivateEvent()) {
							if (activate_handler->CanProcess(button_event)) {
								logger::trace("Can process button event");
							    RE::BSInputEventQueue::GetSingleton()->PushOntoInputQueue(button_event);
							    RE::BSInputEventQueue::GetSingleton()->AddButtonEvent(button_event->device.get()
									, button_event->idCode, 1.f, 0.005f);
							    RE::BSInputEventQueue::GetSingleton()->AddButtonEvent(button_event->device.get()
									, button_event->idCode, 0.f, 0.01f);
								//activate_handler->ProcessButton(button_event,player_controls_data);
						        logger::trace("Processed activate event");
							}
							else {
								logger::error("Cannot process button event");
							}
						}
						else {
							logger::error("No button event");
						}
					}
					else {
						logger::error("No player controls data");
					}
				}
				else {
					logger::error("No activate handler");
				}
				//}
				logger::trace("Activated {}", ref->GetName());
			}
			else {
				logger::trace("No target ref");
			}
			Utils::listenActionEvent.store(false);
		//});
    }
	Hooks::blocked.store(false);
	return RE::BSEventNotifyControl::kContinue;
}

void CleanupAnimationEvent(AnimationEventSink* eventSink)
{
    RE::PlayerCharacter::GetSingleton()->RemoveAnimationGraphEventSink(eventSink);
    logger::trace("EventSink removed.");
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
	const auto device = RE::INPUT_DEVICE::kKeyboard;
	const auto activate_key = controlmap->GetMappedKey(RE::UserEvents::GetSingleton()->activate,device);
	const auto event = RE::ButtonEvent::Create(device,RE::UserEvents::GetSingleton()->activate,activate_key,1.f,0.f);
	activate_event = event;
	return event;
}
