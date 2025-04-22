#include "Utils.h"
#include "FormIDReader.h"
#include "Hooks.h"
#include "Settings.h"

std::filesystem::path GetLogPath() {
    const auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    return logFilePath;
}

std::vector<std::string> ReadLogFile() {
    std::vector<std::string> logLines;

    // Open the log file
    std::ifstream file(GetLogPath().c_str());
    if (!file.is_open()) {
        // Handle error
        return logLines;
    }

    // Read and store each line from the file
    std::string line;
    while (std::getline(file, line)) {
        logLines.push_back(line);
    }

    file.close();

    return logLines;
}

namespace {
    template <class T = RE::TESForm>
    T* GetFormByID(const RE::FormID id, const std::string& editor_id="") {
        if (!editor_id.empty()) {
            if (auto* form = RE::TESForm::LookupByEditorID<T>(editor_id)) return form;
        }
        if (T* form = RE::TESForm::LookupByID<T>(id)) return form;
        return nullptr;
    };
    bool isValidHexWithLength7or8(const char* input)
    {
        std::string inputStr(input);

        if (inputStr.substr(0, 2) == "0x") {
            inputStr = inputStr.substr(2);
        }

        const std::regex hexRegex("^[0-9A-Fa-f]{7,8}$");
        const bool isValid = std::regex_match(inputStr, hexRegex);
        return isValid;
    }
};
RE::FormID GetFormIDFromString(const std::string& formEditorId)
{
    static const std::string delimiter = "~";

    if (formEditorId.empty()) return 0;

	const auto plugin_and_localid = FormReader::split(formEditorId, delimiter);
	if (plugin_and_localid.size() == 2) {
		const auto& plugin_name = plugin_and_localid[1];
		const auto local_id = FormReader::GetFormIDFromString(plugin_and_localid[0]);
		const auto formid = FormReader::GetForm(plugin_name.c_str(), local_id);
		if (const auto form = RE::TESForm::LookupByID(formid)) return form->GetFormID();
	}

    if (isValidHexWithLength7or8(formEditorId.c_str())) {
        int form_id_;
        std::stringstream ss;
        ss << std::hex << formEditorId;
        ss >> form_id_;
        if (const auto temp_form = GetFormByID(form_id_, "")) return temp_form->GetFormID();
        logger::warn("FormID is null for {}", formEditorId);
        return 0;
    }
    if (const auto temp_form = GetFormByID(0, formEditorId)) return temp_form->GetFormID();
    return 0;
}

void ModCompatibility::QuickLootMod::OnOpeningLootMenu(QuickLoot::Events::OpeningLootMenuEvent* event) {
    if (GetSingleton()->IsAllowed() || Settings::GetSingleton()->HideQLOnlyWield && !RE::PlayerCharacter::GetSingleton()->AsActorState()->IsWeaponDrawn()) {
        Hooks::saved_ref.reset();
    } else {
        event->result = QuickLoot::Events::HandleResult::kStop;
    }
}

void ModCompatibility::Install() { 
    QuickLootMod::GetSingleton()->Init(); 
}

bool Game::HasItem(RE::TESObjectREFR* ref, const RE::TESForm* item) {
    if (ref->HasContainer()) {
        for (const auto inv = ref->GetInventory(); const auto& [fst, snd] : inv) {
            if (snd.first > 0) {
                const auto a_name = fst->GetName();
                const auto res = item ? fst->GetFormID() == item->GetFormID() : a_name && (*a_name != '\0');
                if (res) return true;
            }
        }
    }
    return false;
}
