#include "core/EdgeHolder.h"

namespace msdfgen {

void EdgeHolder::swap(EdgeHolder &a, EdgeHolder &b)
{
  EdgeSegment *tmp = a.edgeSegment;
  a.edgeSegment = b.edgeSegment;
  b.edgeSegment = tmp;
}

EdgeHolder::EdgeHolder(const EdgeHolder &orig) : edgeSegment(orig.edgeSegment ? orig.edgeSegment->clone() : NULL) {}

EdgeHolder::EdgeHolder(EdgeHolder &&orig) : edgeSegment(orig.edgeSegment) { orig.edgeSegment = NULL; }

EdgeHolder::~EdgeHolder() { delete edgeSegment; }

EdgeHolder &EdgeHolder::operator=(const EdgeHolder &orig)
{
  if (this != &orig) {
    delete edgeSegment;
    edgeSegment = orig.edgeSegment ? orig.edgeSegment->clone() : NULL;
  }
  return *this;
}

EdgeHolder &EdgeHolder::operator=(EdgeHolder &&orig)
{
  if (this != &orig) {
    delete edgeSegment;
    edgeSegment = orig.edgeSegment;
    orig.edgeSegment = NULL;
  }
  return *this;
}

EdgeSegment &EdgeHolder::operator*() { return *edgeSegment; }

const EdgeSegment &EdgeHolder::operator*() const { return *edgeSegment; }

EdgeSegment *EdgeHolder::operator->() { return edgeSegment; }

const EdgeSegment *EdgeHolder::operator->() const { return edgeSegment; }

EdgeHolder::operator EdgeSegment *() { return edgeSegment; }

EdgeHolder::operator const EdgeSegment *() const { return edgeSegment; }

}// namespace msdfgen
