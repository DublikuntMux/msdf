#pragma once

#include "atlas/GlyphGeometry.hpp"
#include "atlas/types.hpp"

namespace msdf_atlas {
/**
 * This class computes the layout of a static tightly packed atlas and may optionally
 * also find the minimum required dimensions and/or the maximum glyph scale
 */
class TightAtlasPacker
{
public:
  TightAtlasPacker();

  /// Computes the layout for the array of glyphs. Returns 0 on success
  int pack(GlyphGeometry *glyphs, int count);

  /// Sets the atlas's fixed dimensions
  void setDimensions(int width, int height);
  /// Sets the atlas's dimensions to be determined during pack
  void unsetDimensions();
  /// Sets the constraint to be used when determining dimensions
  void setDimensionsConstraint(DimensionsConstraint dimensionsConstraint);
  /// Sets the spacing between glyph boxes
  void setSpacing(int spacing);
  /// Sets fixed glyph scale
  void setScale(double scale);
  /// Sets the minimum glyph scale
  void setMinimumScale(double minScale);
  /// Sets the unit component of the total distance range
  void setUnitRange(double unitRange);
  /// Sets the pixel component of the total distance range
  void setPixelRange(double pxRange);
  /// Sets the miter limit for bounds computation
  void setMiterLimit(double miterLimit);
  /// Sets whether each glyph's origin point should stay aligned with the pixel grid
  void setOriginPixelAlignment(bool align);
  void setOriginPixelAlignment(bool alignX, bool alignY);

  /// Outputs the atlas's final dimensions
  void getDimensions(int &width, int &height) const;
  /// Returns the final glyph scale
  double getScale() const;
  /// Returns the final combined pixel range (including converted unit range)
  double getPixelRange() const;

private:
  int width, height;
  int spacing;
  DimensionsConstraint dimensionsConstraint;
  double scale;
  double minScale;
  double unitRange;
  double pxRange;
  double miterLimit;
  bool pxAlignOriginX, pxAlignOriginY;
  double scaleMaximizationTolerance;

  int tryPack(GlyphGeometry *glyphs,
    int count,
    DimensionsConstraint dimensionsConstraint,
    int &width,
    int &height,
    double scale) const;
  double packAndScale(GlyphGeometry *glyphs, int count) const;
};
}// namespace msdf_atlas
