#pragma once

namespace MCP {
	void __stdcall RenderSettings();
	void __stdcall RenderLog();
    void Register();

	inline std::vector<std::string> logLines;
};