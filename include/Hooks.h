#pragma once

namespace Hooks {
    void Install();

    struct InputHook {
		static void thunk(RE::BSTEventSource<RE::InputEvent*>* a_dispatcher, RE::InputEvent* const* a_event);
		static inline REL::Relocation<decltype(thunk)> func;
		static bool ProcessInput(RE::InputEvent* event);
	};

    template <typename ContainerType>
    class ActivateHook {
        public:
        static void Install();
    private:
        static bool thunk(ContainerType* a_this,
                                       RE::TESObjectREFR* a_targetRef, 
                                        RE::TESObjectREFR* a_activatorRef, 
                                        std::uint8_t a_arg3, 
                                        RE::TESBoundObject* a_object, 
                                        std::int32_t a_targetCount);
        static inline REL::Relocation<decltype(thunk)> func;
    };

	inline std::atomic_bool blocked = false;
    inline RE::TESObjectREFRPtr crosshair_ref = nullptr;
    inline RE::TESObjectREFRPtr saved_ref = nullptr;
    inline const SKSE::CrosshairRefEvent my_event{nullptr};
    inline SKSE::CrosshairRefEvent my_event2{nullptr};
    
    bool OnActivate();
}