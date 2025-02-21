#pragma once

namespace MCP {

	inline bool enabled = true;
	inline bool auto_activate = true;

	void __stdcall RenderSettings();
	void __stdcall RenderLog();
    void Register();

	inline std::vector<std::string> logLines;
};