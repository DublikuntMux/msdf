#pragma once

#include "core/BitmapRef.hpp"
#include "core/base.h"

namespace msdfgen {
bool savePng(const BitmapConstRef<byte, 1> &bitmap, const char *filename);
bool savePng(const BitmapConstRef<byte, 3> &bitmap, const char *filename);
bool savePng(const BitmapConstRef<byte, 4> &bitmap, const char *filename);
bool savePng(const BitmapConstRef<float, 1> &bitmap, const char *filename);
bool savePng(const BitmapConstRef<float, 3> &bitmap, const char *filename);
bool savePng(const BitmapConstRef<float, 4> &bitmap, const char *filename);
}
