#include "Hooks.h"
#include "Utils.h"
#include "Animation.h"
#include "MCP.h"
#include "Settings.h"

namespace Hooks {

    void Install() {

        auto& trampoline = SKSE::GetTrampoline();
        constexpr size_t size_per_hook = 14;
	    trampoline.create(size_per_hook*1);
        const REL::Relocation<std::uintptr_t> target3{REL::RelocationID(67315, 68617)};
        InputHook::func = trampoline.write_call<5>(target3.address() + 0x7B, InputHook::thunk);

        logger::info("Hooks Installed");
    }

    static void AutoActions() {
        const auto set = Settings::GetSingleton();
        const auto player = RE::PlayerCharacter::GetSingleton();

        if (!player->IsInCombat()) {
            if (set->AutoSheatle) {
                player->DrawWeaponMagicHands(false);
                blocked.store(true);
            }
            if (set->AutoActivate) {
                AnimationEventSink* eventSink = GetOrCreateEventSink();
                player->AddAnimationGraphEventSink(eventSink);
                saved_ref = crosshair_ref;
            }
        }
    }

    bool OnActivate() {
        const auto set = Settings::GetSingleton();
		const auto player = RE::PlayerCharacter::GetSingleton();

        if (const auto actorState = player->AsActorState()) {
            if (actorState->GetWeaponState() != RE::WEAPON_STATE::kSheathed) {
                bool noLoot = false;
                if (const auto a_targetRef = crosshair_ref->GetBaseObject()) {
                    auto FormType = a_targetRef->GetFormType();

                    // Iteraction with other Actor
                    switch (FormType) {
                        case RE::FormType::NPC: {
                            auto NPC = crosshair_ref->As<RE::Actor>();
                            if (NPC->IsDead()) {  // Dead Actor
                                if (set->NoLootBody) {
                                    noLoot = true;
                                }
                            } else {  // If Actor is Alive
                                if (player->IsSneaking() && set->NoLootPickpocket) {
                                    noLoot = true;
                                }
                                if (NPC->IsAMount() && set->NoMount) {
                                    noLoot = true;
                                }
                            }
                            break;
                        }
                        case RE::FormType::Weapon:
                            if (set->NoLootWeapon) {
                                noLoot = true;
                            }
                            break;

                        case RE::FormType::Ammo:
                        case RE::FormType::Projectile:
                            if (set->NoLootAmmo) {
                                noLoot = true;
                            }
                            break;

                        case RE::FormType::Armor:
                            if (set->NoLootArmor) {
                                noLoot = true;
                            }
                            break;

                        case RE::FormType::Book:
                            if (a_targetRef->As<RE::TESObjectBOOK>()->TeachesSkill()) {
                                if (set->NoLootSkillBook) {
                                    noLoot = true;
                                }
                            } else if (a_targetRef->As<RE::TESObjectBOOK>()->TeachesSpell()) {
                                if (set->NoLootSpellBook) {
                                    noLoot = true;
                                }
                            } else if (set->NoLootBook) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Note: //Is this even Used?
                            if (set->NoLootNote) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::KeyMaster:
                            if (set->NoLootKey) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::SoulGem:
                            if (set->NoLootSoulGem) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Container:
                            if (set->NoLootContainer) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Flora: {
                            // Nothing seems to work, always getting empty EditorID
                            auto editorID = crosshair_ref->GetBaseObject()->GetFormEditorID();
                            if (editorID && strstr(editorID, "Coin")) {
                                if (set->NoLootGold) {
                                    noLoot = true;
                                }
                            } else {
                                if (set->NoLootFlora) {
                                    noLoot = true;
                                }
                            }
                            break;
                        }
                        case RE::FormType::Tree:  // Some Flora is tree type (e.g. Hanging moss)
                            if (set->NoLootFlora) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Scroll:
                            if (set->NoLootScroll) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::AlchemyItem:
                            if (a_targetRef->As<RE::AlchemyItem>()->IsFood()) {
                                if (set->NoLootFood) {
                                    noLoot = true;
                                }
                            } else if (a_targetRef->As<RE::AlchemyItem>()->IsPoison()) {
                                if (set->NoLootPoison) {
                                    noLoot = true;
                                }
                            } else if (set->NoLootPotion) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Ingredient:
                            if (set->NoLootIngredient) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Misc:
                            if (a_targetRef->IsGold() && set->NoLootGold) {
                                noLoot = true;
                            } else if (a_targetRef->IsLockpick() && set->NoLootLockpick) {
                                noLoot = true;
                            } else if (set->NoLootMisc) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Light:
                            if (set->NoLootLight) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Door:
                            if (set->NoDoor) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Furniture:
                            if (set->NoFurniture) {
                                noLoot = true;
                            }
                            break;
                        case RE::FormType::Activator: {
                            //Nothing seems to work, always getting empty EditorID
                            const char* editorID = crosshair_ref->GetBaseObject()->GetFormEditorID();
                            if (editorID && strstr(editorID, "Critter")) {
                                if (set->NoLootCritter) {
                                    noLoot = true;
                                }
                            } else {
                                if (set->NoActivators) {
                                    noLoot = true;
                                }
                            }
                            break;
                        }
                    }

                    if (noLoot) {
                        AutoActions();
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void InputHook::thunk(RE::BSTEventSource<RE::InputEvent*>* a_dispatcher, RE::InputEvent* const* a_event) {
        if (!Settings::GetSingleton()->ModActive || !a_dispatcher || !a_event || !crosshair_ref) {
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

    bool InputHook::ProcessInput(RE::InputEvent* event) {
        auto set = Settings::GetSingleton();
		bool block = false;
		if (const auto button_event = event->AsButtonEvent()) {
            if (button_event->userEvent == RE::UserEvents::GetSingleton()->activate) {
                if (button_event->IsDown()) {
				    if (!OnActivate()) {
					    block = true;
                    }
                } else if (blocked.load()) {
					block = true;
                }
            }
        }
        if (block) {
            if (set->Message && set->MessageSound) {
                RE::DebugNotification("No Loot When Armed", "UIMenuCancel");
            } else if (set->Message) {
                RE::DebugNotification("No Loot When Armed");
            } else if (set->MessageSound) {
                RE::DebugNotification(" ", "UIMenuCancel"); // Not trigger multiple times like PlaySound do
            }
        }
        return block;
    }

}