#include "MCP.h"
#include "Utils.h"
#include "SKSEMCP/utils.hpp"

void MCP::Register() {
    if (!SKSEMenuFramework::IsInstalled()) {
		logger::error("SKSEMenuFramework is not installed.");
		return;
	}
    SKSEMenuFramework::SetSection(mod_name);
    SKSEMenuFramework::AddSectionItem("Settings", RenderSettings);
    SKSEMenuFramework::AddSectionItem("Log", RenderLog);

}

void __stdcall MCP::RenderSettings()
{
	ImGui::Checkbox("Enabled", &MCP::enabled);
}

void __stdcall MCP::RenderLog()
{
	ImGui::Checkbox("Trace", &LogSettings::log_trace);
    ImGui::SameLine();
    ImGui::Checkbox("Info", &LogSettings::log_info);
    ImGui::SameLine();
    ImGui::Checkbox("Warning", &LogSettings::log_warning);
    ImGui::SameLine();
    ImGui::Checkbox("Error", &LogSettings::log_error);


    // if "Generate Log" button is pressed, read the log file
    if (ImGui::Button("Generate Log")) {
		logLines = ReadLogFile();
	}

    // Display each line in a new ImGui::Text() element
    for (const auto& line : logLines) {
        if (line.find("trace") != std::string::npos && !LogSettings::log_trace) continue;
        if (line.find("info") != std::string::npos && !LogSettings::log_info) continue;
        if (line.find("warning") != std::string::npos && !LogSettings::log_warning) continue;
        if (line.find("error") != std::string::npos && !LogSettings::log_error) continue;
		ImGui::Text(line.c_str());
	}
}
