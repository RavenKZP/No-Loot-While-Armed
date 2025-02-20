#pragma once

struct AnimationEventSink final : RE::BSTEventSink<RE::BSAnimationGraphEvent> {
    RE::BSEventNotifyControl ProcessEvent(const RE::BSAnimationGraphEvent* a_event,
                                          RE::BSTEventSource<RE::BSAnimationGraphEvent>*) override;
    AnimationEventSink() = default;
};

void CleanupAnimationEvent(AnimationEventSink* eventSink);

inline std::unique_ptr<AnimationEventSink> currentAnimationEventSink = nullptr;
AnimationEventSink* GetOrCreateEventSink();

inline RE::ButtonEvent* activate_event = nullptr;
RE::ButtonEvent* GetOrCreateActivateEvent();