#pragma once

#include "atlas/GlyphGeometry.h"
#include "atlas/Remap.h"
#include "core/BitmapRef.hpp"
#include "core/generator-config.h"

namespace msdf_atlas {
/** Prototype of an atlas generator class.
 *  An atlas generator maintains the atlas bitmap (AtlasStorage) and its layout and facilitates
 *  generation of bitmap representation of glyphs. The layout of the atlas is given by the caller.
 */
class AtlasGenerator
{

public:
  AtlasGenerator();
  AtlasGenerator(int width, int height);
  /// Generates bitmap representation for the supplied array of glyphs
  void generate(const GlyphGeometry *glyphs, int count);
  /// Resizes the atlas and rearranges the generated pixels according to the remapping array
  void rearrange(int width, int height, const Remap *remapping, int count);
  /// Resizes the atlas and keeps the generated pixels in place
  void resize(int width, int height);
};

}// namespace msdf_atlas

/// Configuration of signed distance field generator
struct GeneratorAttributes
{
  msdfgen::MSDFGeneratorConfig config;
  bool scanlinePass = false;
};

/// A function that generates the bitmap for a single glyph
template<typename T, int N>
using GeneratorFunction = void (*)(const msdfgen::BitmapRef<T, N> &,
  const msdf_atlas::GlyphGeometry &,
  const GeneratorAttributes &);
