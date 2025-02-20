#pragma once

namespace Hooks {
    void Install();

    struct InputHook {
		static void thunk(RE::BSTEventSource<RE::InputEvent*>* a_dispatcher, RE::InputEvent* const* a_event);
		static inline REL::Relocation<decltype(thunk)> func;
		static bool ProcessInput(RE::InputEvent* event);
	};

	inline std::atomic_bool blocked = false;
	inline RE::TESObjectREFRPtr crosshair_ref = nullptr;
    bool OnActivate();
}