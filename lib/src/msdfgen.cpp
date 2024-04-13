#include "msdfgen.h"
#include "core/ShapeDistanceFinder.h"
#include "core/contour-combiners.h"
#include "core/edge-selectors.h"
#include "core/msdf-error-correction.h"

namespace msdfgen {
template<typename DistanceType> class DistancePixelConversion;

template<> class DistancePixelConversion<double>
{
  double invRange;

public:
  typedef BitmapRef<float, 1> BitmapRefType;
  inline explicit DistancePixelConversion(double range) : invRange(1 / range) {}
  inline void operator()(float *pixels, double distance) const { *pixels = float(invRange * distance + .5); }
};

template<> class DistancePixelConversion<MultiDistance>
{
  double invRange;

public:
  typedef BitmapRef<float, 3> BitmapRefType;
  inline explicit DistancePixelConversion(double range) : invRange(1 / range) {}
  inline void operator()(float *pixels, const MultiDistance &distance) const
  {
    pixels[0] = float(invRange * distance.r + .5);
    pixels[1] = float(invRange * distance.g + .5);
    pixels[2] = float(invRange * distance.b + .5);
  }
};

template<> class DistancePixelConversion<MultiAndTrueDistance>
{
  double invRange;

public:
  typedef BitmapRef<float, 4> BitmapRefType;
  inline explicit DistancePixelConversion(double range) : invRange(1 / range) {}
  inline void operator()(float *pixels, const MultiAndTrueDistance &distance) const
  {
    pixels[0] = float(invRange * distance.r + .5);
    pixels[1] = float(invRange * distance.g + .5);
    pixels[2] = float(invRange * distance.b + .5);
    pixels[3] = float(invRange * distance.a + .5);
  }
};

template<class ContourCombiner>
void generateDistanceField(
  const typename DistancePixelConversion<typename ContourCombiner::DistanceType>::BitmapRefType &output,
  const Shape &shape,
  const Projection &projection,
  double range)
{
  DistancePixelConversion<typename ContourCombiner::DistanceType> distancePixelConversion(range);
#pragma omp parallel
  {
    ShapeDistanceFinder<ContourCombiner> distanceFinder(shape);
    bool rightToLeft = false;
#pragma omp for
    for (int y = 0; y < output.height; ++y) {
      int row = shape.inverseYAxis ? output.height - y - 1 : y;
      for (int col = 0; col < output.width; ++col) {
        int x = rightToLeft ? output.width - col - 1 : col;
        Point2 p = projection.unproject(Point2(x + .5, y + .5));
        typename ContourCombiner::DistanceType distance = distanceFinder.distance(p);
        distancePixelConversion(output(x, row), distance);
      }
      rightToLeft = !rightToLeft;
    }
  }
}

void generateSDF(const BitmapRef<float, 1> &output,
  const Shape &shape,
  const Projection &projection,
  double range,
  const GeneratorConfig &config)
{
  if (config.overlapSupport)
    generateDistanceField<OverlappingContourCombiner<TrueDistanceSelector>>(output, shape, projection, range);
  else
    generateDistanceField<SimpleContourCombiner<TrueDistanceSelector>>(output, shape, projection, range);
}

void generatePSDF(const BitmapRef<float, 1> &output,
  const Shape &shape,
  const Projection &projection,
  double range,
  const GeneratorConfig &config)
{
  if (config.overlapSupport)
    generateDistanceField<OverlappingContourCombiner<PerpendicularDistanceSelector>>(output, shape, projection, range);
  else
    generateDistanceField<SimpleContourCombiner<PerpendicularDistanceSelector>>(output, shape, projection, range);
}

void generateMSDF(const BitmapRef<float, 3> &output,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config)
{
  if (config.overlapSupport)
    generateDistanceField<OverlappingContourCombiner<MultiDistanceSelector>>(output, shape, projection, range);
  else
    generateDistanceField<SimpleContourCombiner<MultiDistanceSelector>>(output, shape, projection, range);
  msdfErrorCorrection(output, shape, projection, range, config);
}

void generateMTSDF(const BitmapRef<float, 4> &output,
  const Shape &shape,
  const Projection &projection,
  double range,
  const MSDFGeneratorConfig &config)
{
  if (config.overlapSupport)
    generateDistanceField<OverlappingContourCombiner<MultiAndTrueDistanceSelector>>(output, shape, projection, range);
  else
    generateDistanceField<SimpleContourCombiner<MultiAndTrueDistanceSelector>>(output, shape, projection, range);
  msdfErrorCorrection(output, shape, projection, range, config);
}
}// namespace msdfgen
