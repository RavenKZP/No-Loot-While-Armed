#pragma once

const auto mod_name = static_cast<std::string>(SKSE::PluginDeclaration::GetSingleton()->GetName());

std::filesystem::path GetLogPath();
std::vector<std::string> ReadLogFile();

namespace LogSettings {
	inline bool log_trace = true;
	inline bool log_info = true;
	inline bool log_warning = true;
	inline bool log_error = true;
};