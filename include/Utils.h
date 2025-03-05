#pragma once
#include "ClibUtil/singleton.hpp"
#include "QuickLootAPI.h"

const auto mod_name = static_cast<std::string>(SKSE::PluginDeclaration::GetSingleton()->GetName());

std::filesystem::path GetLogPath();
std::vector<std::string> ReadLogFile();


namespace ModCompatibility {

	class Mod
    {
	protected:
        explicit Mod(const char* path) : path(path) {}
	    const char* path=nullptr;
	    [[nodiscard]] bool IsInstalled() const { return std::filesystem::exists(path); }
		virtual void OnInit() = 0;
	public:
        virtual ~Mod() = default;
        void Init() {is_installed = IsInstalled();OnInit();}
	    bool is_installed = false;
    };

	class QuickLootMod final : public Mod, public clib_util::singleton::ISingleton<QuickLootMod>
    {
        static void OnOpeningLootMenu(QuickLoot::Events::OpeningLootMenuEvent* event);

		bool is_allowed = true;

	protected:
		void OnInit() override
		{
			if (!is_installed) return;
			QuickLoot::QuickLootAPI::Init();
            QuickLoot::QuickLootAPI::RegisterOpeningLootMenuHandler(OnOpeningLootMenu);
		}
	public:
		QuickLootMod() : Mod("Data/SKSE/Plugins/QuickLootIE.dll") {}
		[[nodiscard]] bool IsAllowed() const { return is_allowed; }
		void SetAllowed(const bool allowed) { is_allowed = allowed; }
	};

    void Install();
};


namespace LogSettings {
	inline bool log_trace = true;
	inline bool log_info = true;
	inline bool log_warning = true;
	inline bool log_error = true;
};