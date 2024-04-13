#include "core/msdf-error-correction.h"
#include "core/Bitmap.h"
#include "core/MSDFErrorCorrection.h"
#include "core/contour-combiners.h"

namespace msdfgen {

template<int N>
static void msdfErrorCorrectionInner(const BitmapRef<float, N> &sdf,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config)
{
  if (config.errorCorrection.mode == ErrorCorrectionConfig::DISABLED) return;
  Bitmap<byte, 1> stencilBuffer;
  if (!config.errorCorrection.buffer) stencilBuffer = Bitmap<byte, 1>(sdf.width, sdf.height);
  BitmapRef<byte, 1> stencil;
  stencil.pixels = config.errorCorrection.buffer ? config.errorCorrection.buffer : (byte *)stencilBuffer;
  stencil.width = sdf.width, stencil.height = sdf.height;
  MSDFErrorCorrection ec(stencil, projection, range);
  ec.setMinDeviationRatio(config.errorCorrection.minDeviationRatio);
  ec.setMinImproveRatio(config.errorCorrection.minImproveRatio);
  switch (config.errorCorrection.mode) {
  case ErrorCorrectionConfig::DISABLED:
  case ErrorCorrectionConfig::INDISCRIMINATE:
    break;
  case ErrorCorrectionConfig::EDGE_PRIORITY:
    ec.protectCorners(shape);
    ec.protectEdges<N>(sdf);
    break;
  case ErrorCorrectionConfig::EDGE_ONLY:
    ec.protectAll();
    break;
  }
  if (config.errorCorrection.distanceCheckMode == ErrorCorrectionConfig::DO_NOT_CHECK_DISTANCE
      || (config.errorCorrection.distanceCheckMode == ErrorCorrectionConfig::CHECK_DISTANCE_AT_EDGE
          && config.errorCorrection.mode != ErrorCorrectionConfig::EDGE_ONLY)) {
    ec.findErrors<N>(sdf);
    if (config.errorCorrection.distanceCheckMode == ErrorCorrectionConfig::CHECK_DISTANCE_AT_EDGE) ec.protectAll();
  }
  if (config.errorCorrection.distanceCheckMode == ErrorCorrectionConfig::ALWAYS_CHECK_DISTANCE
      || config.errorCorrection.distanceCheckMode == ErrorCorrectionConfig::CHECK_DISTANCE_AT_EDGE) {
    if (config.overlapSupport)
      ec.findErrors<OverlappingContourCombiner, N>(sdf, shape);
    else
      ec.findErrors<SimpleContourCombiner, N>(sdf, shape);
  }
  ec.apply(sdf);
}

template<int N>
static void msdfErrorCorrectionShapeless(const BitmapRef<float, N> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio,
  bool protectAll)
{
  Bitmap<byte, 1> stencilBuffer(sdf.width, sdf.height);
  MSDFErrorCorrection ec(stencilBuffer, projection, range);
  ec.setMinDeviationRatio(minDeviationRatio);
  if (protectAll) ec.protectAll();
  ec.findErrors<N>(sdf);
  ec.apply(sdf);
}

void msdfErrorCorrection(const BitmapRef<float, 3> &sdf,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config)
{
  msdfErrorCorrectionInner(sdf, shape, projection, range, config);
}
void msdfErrorCorrection(const BitmapRef<float, 4> &sdf,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config)
{
  msdfErrorCorrectionInner(sdf, shape, projection, range, config);
}

void msdfFastDistanceErrorCorrection(const BitmapRef<float, 3> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio)
{
  msdfErrorCorrectionShapeless(sdf, projection, range, minDeviationRatio, false);
}
void msdfFastDistanceErrorCorrection(const BitmapRef<float, 4> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio)
{
  msdfErrorCorrectionShapeless(sdf, projection, range, minDeviationRatio, false);
}

void msdfFastEdgeErrorCorrection(const BitmapRef<float, 3> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio)
{
  msdfErrorCorrectionShapeless(sdf, projection, range, minDeviationRatio, true);
}
void msdfFastEdgeErrorCorrection(const BitmapRef<float, 4> &sdf,
  const Projection &projection,
  double range,
  double minDeviationRatio)
{
  msdfErrorCorrectionShapeless(sdf, projection, range, minDeviationRatio, true);
}
}// namespace msdfgen
