#pragma once

namespace Hooks {
    void Install();

    template <class T>
    struct ActivateHook {
        static void InstallHook();
        static bool thunk(RE::TESBoundObject* a_this, RE::TESObjectREFR* a_targetRef, RE::TESObjectREFR* a_activatorRef,
                          std::uint8_t a_arg3, RE::TESBoundObject* a_object, std::int32_t a_targetCount);
        static inline REL::Relocation<decltype(thunk)> func;
    };

    struct PlayerUpdateHook {
        static void InstallHook();
        static void thunk(RE::PlayerCharacter* a_player, float a_delta);
        static inline REL::Relocation<decltype(thunk)> func;
    };
}