#pragma once

#include <vector>

#include "atlas/types.hpp"

namespace msdf_atlas {
void utf8Decode(std::vector<unicode_t> &codepoints, const char *utf8String);
}
