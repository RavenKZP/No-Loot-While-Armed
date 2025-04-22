#pragma once

namespace MCP {
	void __stdcall RenderSettings();
	void __stdcall RenderExcludedRaces();
	void __stdcall RenderLog();
    void Register();

	inline std::vector<std::string> logLines;

	namespace SettingsMCP {

        class Section {
	        std::map<size_t, std::vector<std::string>> checkboxes;
			float spacing = 200.0f;
        public:
	        Section(std::string a_label, const std::map<size_t, std::vector<std::string>>& checkboxes);
	        std::string label;
	        bool collapsed = false;
			void Render();
        };

	    inline std::vector<MCP::SettingsMCP::Section> sections;
		void CreateSettingsSections();
	};
};
