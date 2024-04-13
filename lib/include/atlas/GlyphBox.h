#pragma once

#include "atlas/Rectangle.h"

namespace msdf_atlas {

/// The glyph box - its bounds in plane and atlas
struct GlyphBox
{
  int index;
  double advance;
  struct
  {
    double l, b, r, t;
  } bounds;
  Rectangle rect;
};
}// namespace msdf_atlas
