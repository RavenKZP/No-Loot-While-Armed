#pragma once

namespace Utils {

	struct ActivationEvent {
        RE::TESBoundObject* self_this = nullptr;
        RE::TESObjectREFR* targetRef = nullptr;
        RE::TESObjectREFR* activatorRef = nullptr;
        std::uint8_t arg3 = 0;
        RE::TESBoundObject* object = nullptr;
        std::int32_t targetCount = 0;
    };

    inline ActivationEvent SavedActivationEvent;

    void SetActivationEvent(RE::TESBoundObject* a_this, RE::TESObjectREFR* a_targetRef, RE::TESObjectREFR* a_activatorRef,
                          std::uint8_t a_arg3, RE::TESBoundObject* a_object, std::int32_t a_targetCount) {
        SavedActivationEvent.self_this = a_this;
        SavedActivationEvent.targetRef = a_targetRef;
        SavedActivationEvent.activatorRef = a_activatorRef;
        SavedActivationEvent.arg3 = a_arg3;
        SavedActivationEvent.object = a_object;
        SavedActivationEvent.targetCount = a_targetCount;
    }

    ActivationEvent GetActivationEvent() { 
        return SavedActivationEvent;
    }

    void ResetActivationEvent() {
        SavedActivationEvent.self_this = nullptr;
        SavedActivationEvent.targetRef = nullptr;
        SavedActivationEvent.activatorRef = nullptr;
        SavedActivationEvent.arg3 = 0;
        SavedActivationEvent.object = nullptr;
        SavedActivationEvent.targetCount = 0;
    }

}