#include "Settings.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#define CONFIG_FILENAME "wxpic.config.json"
#define CONFIG_TOOLS_PRIMARY_COLOR "tools.primary_color"
#define CONFIG_TOOLS_BRUSH_SIZE "tools.brush_size"

namespace pt = boost::property_tree;

pt::ptree getPtree() {
	pt::ptree pt;
	try {
		pt::read_json(CONFIG_FILENAME, pt);
	}
	catch (const pt::json_parser_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return pt;
}

wxColor Settings::getPrimaryColor() {
	pt::ptree pt(getPtree());
	wxColor defaultColor(0xff, 0x44, 0x44);
	wxColor primaryColor;
	try {
		wxString colorStr = pt.get<std::string>(CONFIG_TOOLS_PRIMARY_COLOR);
		if (!primaryColor.Set(colorStr)) {
			primaryColor = defaultColor;
		}
		return primaryColor;
	}
	catch (const pt::ptree_error &e) {
		std::cerr << e.what() << std::endl;
		return defaultColor;
	}
}

void Settings::setPrimaryColor(const wxColor &c) {
	pt::ptree pt(getPtree());
	pt.put(CONFIG_TOOLS_PRIMARY_COLOR, c.GetAsString(wxC2S_HTML_SYNTAX));
	pt::write_json(CONFIG_FILENAME, pt);
}

int Settings::getBrushSize() {
	pt::ptree pt(getPtree());
	try {
		return pt.get<int>(CONFIG_TOOLS_BRUSH_SIZE);
	}
	catch (const pt::ptree_error &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

void Settings::setBrushSize(int size) {
	pt::ptree pt(getPtree());
	pt.put(CONFIG_TOOLS_BRUSH_SIZE, size);
	pt::write_json(CONFIG_FILENAME, pt);
}
