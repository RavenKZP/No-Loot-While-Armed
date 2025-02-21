#include "Hooks.h"
#include "Utils.h"
#include "Animation.h"
#include "MCP.h"

namespace Hooks {

    void Install() {

        // Unused as Can't get animations
        //PlayerUpdateHook::InstallHook();

        RE::FormType JustForReferenceToAllTypes;

        auto& trampoline = SKSE::GetTrampoline();
        constexpr size_t size_per_hook = 14;
	    trampoline.create(size_per_hook*1);
        const REL::Relocation<std::uintptr_t> target3{REL::RelocationID(67315, 68617)};
        InputHook::func = trampoline.write_call<5>(target3.address() + 0x7B, InputHook::thunk);

        logger::info("Hooks Installed");
    }

    bool OnActivate()
    {
		// TODO: needs refactoring

		const auto player = RE::PlayerCharacter::GetSingleton();
		const auto a_activatorRef = player;
        if (const auto a_targetRef = crosshair_ref) {
            if (const auto actor = a_activatorRef->As<RE::Actor>()) {
                if (actor->IsPlayerRef()) {
                    if (a_targetRef->As<RE::Actor>()) {
                        if (!a_targetRef->IsDead()) {
                            if (actor->IsSneaking()) {
                                return false;
                            }
                            return true;
                        }
                    }
                    if (const auto actorState = actor->AsActorState()) {
                        if (actorState->GetWeaponState() != RE::WEAPON_STATE::kSheathed) {
                            if (!actor->IsInCombat()) {
                                actor->DrawWeaponMagicHands(false);
                                AnimationEventSink* eventSink = GetOrCreateEventSink();
	                            player->AddAnimationGraphEventSink(eventSink);
                            }
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    void InputHook::thunk(RE::BSTEventSource<RE::InputEvent*>* a_dispatcher, RE::InputEvent* const* a_event)
    {
		// TODO: make sure only relevant activations are blocked! (e.g. only relevant forms. not in menus. not sure if possible anyway)

        if (!MCP::enabled || !a_dispatcher || !a_event || !crosshair_ref) {
		    return func(a_dispatcher, a_event);
	    }

        auto first = *a_event;
        auto last = *a_event;
        size_t length = 0;

        for (auto current = *a_event; current; current = current->next) {
            if (ProcessInput(current)) {
                if (current != last) {
                    last->next = current->next;
                } else {
                    last = current->next;
                    first = current->next;
                }
            } else {
                last = current;
                ++length;
            }
        }

        if (length == 0) {
            constexpr RE::InputEvent* const dummy[] = {nullptr};
            func(a_dispatcher, dummy);
        } else {
            RE::InputEvent* const e[] = {first};
            func(a_dispatcher, e);
        }
    }

    bool InputHook::ProcessInput(RE::InputEvent* event)
    {
		bool block = false;
		if (const auto button_event = event->AsButtonEvent()) {
            if (button_event->userEvent == RE::UserEvents::GetSingleton()->activate) {
                if (button_event->IsDown()) {
				    if (!OnActivate()) {
					    block = true;
                        blocked.store(true);
                    }
                } else if (blocked.load()) {
					block = true;
                }
            }
        }
        return block;
    }

}