#pragma once

#include "core/edge-segments.h"

namespace msdfgen {
/// Container for a single edge of dynamic type.
class EdgeHolder
{
public:
  /// Swaps the edges held by a and b.
  static void swap(EdgeHolder &a, EdgeHolder &b);

  inline EdgeHolder() : edgeSegment() {}
  inline EdgeHolder(EdgeSegment *segment) : edgeSegment(segment) {}
  inline EdgeHolder(Point2 p0, Point2 p1, EdgeColor edgeColor = WHITE)
    : edgeSegment(EdgeSegment::create(p0, p1, edgeColor))
  {}
  inline EdgeHolder(Point2 p0, Point2 p1, Point2 p2, EdgeColor edgeColor = WHITE)
    : edgeSegment(EdgeSegment::create(p0, p1, p2, edgeColor))
  {}
  inline EdgeHolder(Point2 p0, Point2 p1, Point2 p2, Point2 p3, EdgeColor edgeColor = WHITE)
    : edgeSegment(EdgeSegment::create(p0, p1, p2, p3, edgeColor))
  {}
  EdgeHolder(const EdgeHolder &orig);
  EdgeHolder(EdgeHolder &&orig);
  ~EdgeHolder();
  EdgeHolder &operator=(const EdgeHolder &orig);
  EdgeHolder &operator=(EdgeHolder &&orig);
  EdgeSegment &operator*();
  const EdgeSegment &operator*() const;
  EdgeSegment *operator->();
  const EdgeSegment *operator->() const;
  operator EdgeSegment *();
  operator const EdgeSegment *() const;

private:
  EdgeSegment *edgeSegment;
};
}// namespace msdfgen
