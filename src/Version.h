#pragma once
#include <string>

class Version {
public:
   static std::string getAppName();
   static std::string getVersion();
	static std::string getVcsRef();
   static std::string getBuildTimestamp();
};
