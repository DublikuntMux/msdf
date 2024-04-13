#pragma once

#include "core/BitmapRef.hpp"
#include "core/Projection.hpp"
#include "core/Scanline.hpp"
#include "core/Shape.hpp"

namespace msdfgen {
/// Rasterizes the shape into a monochrome bitmap.
void rasterize(const BitmapRef<float, 1> &output,
  const Shape &shape,
  const Projection &projection,
  FillRule fillRule = FILL_NONZERO);
/// Fixes the sign of the input signed distance field, so that it matches the shape's rasterized fill.
void distanceSignCorrection(const BitmapRef<float, 1> &sdf,
  const Shape &shape,
  const Projection &projection,
  FillRule fillRule = FILL_NONZERO);
void distanceSignCorrection(const BitmapRef<float, 3> &sdf,
  const Shape &shape,
  const Projection &projection,
  FillRule fillRule = FILL_NONZERO);
void distanceSignCorrection(const BitmapRef<float, 4> &sdf,
  const Shape &shape,
  const Projection &projection,
  FillRule fillRule = FILL_NONZERO);
}// namespace msdfgen
