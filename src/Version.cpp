#include "Version.h"
#include "version_gen.h"

std::string Version::getAppName() {
   return "wxPic";
}

std::string Version::getVersion() {
   return "0.1";
}

std::string Version::getVcsRef() {
   return VCS_REF;
}

std::string Version::getBuildTimestamp() {
   return TIMESTAMP;
}
