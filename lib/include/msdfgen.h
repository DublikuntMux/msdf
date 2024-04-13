#pragma once

#include "core/BitmapRef.hpp"
#include "core/Projection.h"
#include "core/Shape.h"
#include "core/Vector2.hpp"
#include "core/generator-config.h"

namespace msdfgen {

/// Generates a conventional single-channel signed distance field.
void generateSDF(const BitmapRef<float, 1> &output,
  const Shape &shape,
  const Projection &projection,
  double range,
  const GeneratorConfig &config = GeneratorConfig());

/// Generates a single-channel signed perpendicular distance field.
void generatePSDF(const BitmapRef<float, 1> &output,
  const Shape &shape,
  const Projection &projection,
  double range,
  const GeneratorConfig &config = GeneratorConfig());

/// Generates a multi-channel signed distance field. Edge colors must be assigned first! (See edgeColoringSimple)
void generateMSDF(const BitmapRef<float, 3> &output,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config = MSDFGeneratorConfig());

/// Generates a multi-channel signed distance field with true distance in the alpha channel. Edge colors must be
/// assigned first.
void generateMTSDF(const BitmapRef<float, 4> &output,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config = MSDFGeneratorConfig());

void generateSDF(const BitmapRef<float, 1> &output,
  const Shape &shape,
  double range,
  const Vector2 &scale,
  const Vector2 &translate,
  bool overlapSupport = true);

void generatePSDF(const BitmapRef<float, 1> &output,
  const Shape &shape,
  double range,
  const Vector2 &scale,
  const Vector2 &translate,
  bool overlapSupport = true);

void generatePseudoSDF(const BitmapRef<float, 1> &output,
  const Shape &shape,
  double range,
  const Vector2 &scale,
  const Vector2 &translate,
  bool overlapSupport = true);

void generateMSDF(const BitmapRef<float, 3> &output,
  const Shape &shape,
  double range,
  const Vector2 &scale,
  const Vector2 &translate,
  const ErrorCorrectionConfig &errorCorrectionConfig = ErrorCorrectionConfig(),
  bool overlapSupport = true);

void generateMTSDF(const BitmapRef<float, 4> &output,
  const Shape &shape,
  double range,
  const Vector2 &scale,
  const Vector2 &translate,
  const ErrorCorrectionConfig &errorCorrectionConfig = ErrorCorrectionConfig(),
  bool overlapSupport = true);
}// namespace msdfgen
