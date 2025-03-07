#include "Utils.h"

#include "Hooks.h"

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

void ModCompatibility::QuickLootMod::OnOpeningLootMenu(QuickLoot::Events::OpeningLootMenuEvent* event) {
    if (!GetSingleton()->IsAllowed()) {
        event->result = QuickLoot::Events::HandleResult::kStop;
    } else {
        Hooks::saved_ref.reset();
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
