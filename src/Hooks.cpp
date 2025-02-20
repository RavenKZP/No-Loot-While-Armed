#include "Hooks.h"
#include "Settings.h"
#include "Utils.h"

namespace Hooks {

    void Install() {
        ActivateHook<RE::AlchemyItem>::InstallHook();
        ActivateHook<RE::IngredientItem>::InstallHook();
        ActivateHook<RE::ScrollItem>::InstallHook();

        ActivateHook<RE::TESAmmo>::InstallHook();
        ActivateHook<RE::TESNPC>::InstallHook();
        ActivateHook<RE::TESFlora>::InstallHook();
        ActivateHook<RE::TESFurniture>::InstallHook();
        ActivateHook<RE::TESKey>::InstallHook();
        ActivateHook<RE::TESSoulGem>::InstallHook();

        ActivateHook<RE::TESObjectACTI>::InstallHook();
        ActivateHook<RE::TESObjectARMO>::InstallHook();
        ActivateHook<RE::TESObjectBOOK>::InstallHook();
        ActivateHook<RE::TESObjectCONT>::InstallHook();
        ActivateHook<RE::TESObjectDOOR>::InstallHook();
        ActivateHook<RE::TESObjectLIGH>::InstallHook();
        ActivateHook<RE::TESObjectMISC>::InstallHook();
        ActivateHook<RE::TESObjectTREE>::InstallHook();
        ActivateHook<RE::TESObjectWEAP>::InstallHook();

        // Unused as Can't get animations
        //PlayerUpdateHook::InstallHook();

        RE::FormType JustForReferenceToAllTypes;

        logger::info("Hooks Installed");
    }

    template <class T>
    void ActivateHook<T>::InstallHook() {
        REL::Relocation<std::uintptr_t> vTable(T::VTABLE[0]);
        func = vTable.write_vfunc(0x37, &ActivateHook::thunk);
    }

    void PlayerUpdateHook::InstallHook() {
        REL::Relocation<std::uintptr_t> vTable(RE::PlayerCharacter::VTABLE[0]);
        func = vTable.write_vfunc(0xAD, &PlayerUpdateHook::thunk);
    }

    template <class T>
    bool ActivateHook<T>::thunk(RE::TESBoundObject* a_this, RE::TESObjectREFR* a_targetRef,
                                RE::TESObjectREFR* a_activatorRef, std::uint8_t a_arg3, RE::TESBoundObject* a_object,
                                std::int32_t a_targetCount) {
        
        if (a_this->Is(RE::FormType::Weapon)) {
            logger::trace("Its a Weapon");
        }
        if (a_this->Is(RE::FormType::NPC)) {
            logger::trace("Its a NPC");
        }

        if (a_targetRef && a_activatorRef) {
            if (const auto actor = a_activatorRef->As<RE::Actor>()) {
                if (!actor->IsPlayerRef()) {
                    return func(a_this, a_targetRef, a_activatorRef, a_arg3, a_object, a_targetCount);
                }

                if (a_this->Is(RE::FormType::NPC)) {
                    if (!a_targetRef->IsDead()) {
                        logger::trace("{} is not dead", a_targetRef->GetName());
                        if (actor->IsSneaking()) {
                            logger::trace("No Loot While Armed");
                            return false;
                        }
                        return func(a_this, a_targetRef, a_activatorRef, a_arg3, a_object, a_targetCount);
                    }
                }
                logger::trace("a_targetRef {}", a_targetRef->GetName());
                if (const auto actorState = actor->AsActorState()) {
                    if (actorState->GetWeaponState() != RE::WEAPON_STATE::kSheathed) {
                        logger::trace("No Loot While Armed");
                        if (!actor->IsInCombat()) {
                            actor->DrawWeaponMagicHands(false);
                            Utils::SetActivationEvent(a_this, a_targetRef, a_activatorRef, a_arg3, a_object,
                                                      a_targetCount);
                        }
                        return false;
                    }
                }
            }
        }
        logger::trace("Call original");
        return func(a_this, a_targetRef, a_activatorRef, a_arg3, a_object, a_targetCount);
    }

    void PlayerUpdateHook::thunk(RE::PlayerCharacter* a_actor, float a_delta) {
        if (!a_actor) {
            return func(a_actor, a_delta);
        }
        if (Utils::SavedActivationEvent.self_this) {
            if (const RE::ActorState* actorState = a_actor->AsActorState()) {
                if (actorState->GetWeaponState() == RE::WEAPON_STATE::kSheathed) {
                    logger::trace("kSheathed");
                    Utils::ActivationEvent act = Utils::GetActivationEvent();
                    // Looks like calling this dont trigger animations :(
                    act.self_this->Activate(act.targetRef, act.activatorRef, act.arg3, act.object, act.targetCount);
                    Utils::ResetActivationEvent();
                }
            }
        }
        
        return func(a_actor, a_delta);
    }
}