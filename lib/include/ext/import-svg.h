#pragma once

#include "core/Shape.h"

#ifndef MSDLIB_PUBLIC
#define MSDLIB_PUBLIC
#endif

namespace msdfgen {

extern MSDLIB_PUBLIC const int SVG_IMPORT_FAILURE;
extern MSDLIB_PUBLIC const int SVG_IMPORT_SUCCESS_FLAG;
extern MSDLIB_PUBLIC const int SVG_IMPORT_PARTIAL_FAILURE_FLAG;
extern MSDLIB_PUBLIC const int SVG_IMPORT_INCOMPLETE_FLAG;
extern MSDLIB_PUBLIC const int SVG_IMPORT_UNSUPPORTED_FEATURE_FLAG;
extern MSDLIB_PUBLIC const int SVG_IMPORT_TRANSFORMATION_IGNORED_FLAG;

/// Builds a shape from an SVG path string
bool buildShapeFromSvgPath(Shape &shape, const char *pathDef, double endpointSnapRange = 0);

/// Reads a single <path> element found in the specified SVG file and converts it to output Shape
bool loadSvgShape(Shape &output, const char *filename, int pathIndex = 0, Vector2 *dimensions = NULL);

/// New version - if Skia is available, reads the entire geometry of the SVG file into the output Shape, otherwise may
/// only read one path, returns SVG import flags
int loadSvgShape(Shape &output, Shape::Bounds &viewBox, const char *filename);
}// namespace msdfgen
