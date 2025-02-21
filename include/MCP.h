#pragma once

namespace MCP {

	inline bool enabled = true;

	void __stdcall RenderSettings();
	void __stdcall RenderLog();
    void Register();

	inline std::vector<std::string> logLines;
};