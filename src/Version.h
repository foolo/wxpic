#pragma once
#include <string>

class Version {
public:
	static std::string getVcsRef();
   static std::string getBuildTimestamp();
};
