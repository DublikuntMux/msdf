#pragma once

#include "core/BitmapRef.hpp"
#include "core/Projection.hpp"
#include "core/Scanline.hpp"
#include "core/Shape.hpp"

namespace msdfgen {
/// Analytically constructs a scanline at y evaluating fill by linear interpolation of the SDF.
void scanlineSDF(Scanline &line,
  const BitmapConstRef<float, 1> &sdf,
  const Projection &projection,
  double y,
  bool inverseYAxis = false);
void scanlineSDF(Scanline &line,
  const BitmapConstRef<float, 3> &sdf,
  const Projection &projection,
  double y,
  bool inverseYAxis = false);
void scanlineSDF(Scanline &line,
  const BitmapConstRef<float, 4> &sdf,
  const Projection &projection,
  double y,
  bool inverseYAxis = false);

/// Estimates the portion of the area that will be filled incorrectly when rendering using the SDF.
double estimateSDFError(const BitmapConstRef<float, 1> &sdf,
  const Shape &shape,
  const Projection &projection,
  int scanlinesPerRow,
  FillRule fillRule = FILL_NONZERO);
double estimateSDFError(const BitmapConstRef<float, 3> &sdf,
  const Shape &shape,
  const Projection &projection,
  int scanlinesPerRow,
  FillRule fillRule = FILL_NONZERO);
double estimateSDFError(const BitmapConstRef<float, 4> &sdf,
  const Shape &shape,
  const Projection &projection,
  int scanlinesPerRow,
  FillRule fillRule = FILL_NONZERO);
}// namespace msdfgen
