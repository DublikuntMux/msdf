#pragma once

#include "core/BitmapRef.hpp"
#include "core/Projection.h"
#include "core/Shape.h"
#include "core/generator-config.h"

namespace msdfgen {
/// Predicts potential artifacts caused by the interpolation of the MSDF and corrects them by converting nearby texels
/// to single-channel.
void msdfErrorCorrection(const BitmapRef<float, 3> &sdf,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config = MSDFGeneratorConfig());

void msdfErrorCorrection(const BitmapRef<float, 4> &sdf,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config = MSDFGeneratorConfig());

/// Applies the simplified error correction to all discontiunous distances (INDISCRIMINATE mode). Does not need shape or
/// translation.
void msdfFastDistanceErrorCorrection(const BitmapRef<float, 3> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);

void msdfFastDistanceErrorCorrection(const BitmapRef<float, 4> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);

/// Applies the simplified error correction to edges only (EDGE_ONLY mode). Does not need shape or translation.
void msdfFastEdgeErrorCorrection(const BitmapRef<float, 3> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);

void msdfFastEdgeErrorCorrection(const BitmapRef<float, 4> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);
}// namespace msdfgen
