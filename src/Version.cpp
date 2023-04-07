#include "Version.h"
#include "version_gen.h"

std::string Version::getVcsRef() {
   return VCS_REF;
}

std::string Version::getBuildTimestamp() {
   return TIMESTAMP;
}
