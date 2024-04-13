#pragma once

#include "atlas/types.h"
#include "core/BitmapRef.hpp"

namespace msdf_atlas {
template<typename T, int N>
bool saveImage(const msdfgen::BitmapConstRef<T, N> &bitmap,
  ImageFormat format,
  const char *filename,
  YDirection outputYDirection = YDirection::BOTTOM_UP);
}
