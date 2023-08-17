#include "Settings.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#define CONFIG_FILENAME "wxpic.config.json"
#define CONFIG_TOOLS_PRIMARY_COLOR "tools.primary_color"

boost::property_tree::ptree getPtree() {
	boost::property_tree::ptree pt;
	try {
		boost::property_tree::read_json(CONFIG_FILENAME, pt);
	}
	catch (const boost::property_tree::json_parser_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return pt;
}

wxColor Settings::getPrimaryColor() {
	boost::property_tree::ptree pt(getPtree());
	wxColor defaultColor(0xff, 0x44, 0x44);
	wxColor primaryColor;
	try {
		wxString colorStr = pt.get<std::string>(CONFIG_TOOLS_PRIMARY_COLOR);
		if (!primaryColor.Set(colorStr)) {
			primaryColor = defaultColor;
		}
		return primaryColor;
	}
	catch (const boost::property_tree::ptree_error &e) {
		std::cerr << e.what() << std::endl;
		return defaultColor;
	}
}

void Settings::setPrimaryColor(const wxColor &c) {
	boost::property_tree::ptree pt(getPtree());
	pt.put(CONFIG_TOOLS_PRIMARY_COLOR, c.GetAsString(wxC2S_HTML_SYNTAX));
	boost::property_tree::write_json(CONFIG_FILENAME, pt);
}
