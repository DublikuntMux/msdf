#pragma once

#include "atlas/FontGeometry.h"
#include "atlas/types.h"

namespace msdf_atlas {
struct JsonAtlasMetrics
{
  struct GridMetrics
  {
    int cellWidth, cellHeight;
    int columns, rows;
    const double *originX, *originY;
    int spacing;
  };
  double distanceRange;
  double size;
  int width, height;
  YDirection yDirection;
  const GridMetrics *grid;
};

/// Writes the font and glyph metrics and atlas layout data into a comprehensive JSON file
bool exportJSON(const FontGeometry *fonts,
  int fontCount,
  ImageType imageType,
  const JsonAtlasMetrics &metrics,
  const char *filename,
  bool kerning);
}// namespace msdf_atlas