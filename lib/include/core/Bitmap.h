#pragma once

#include "core/BitmapRef.hpp"

namespace msdfgen {

/// A 2D image bitmap with N channels of type T. Pixel memory is managed by the class.
template<typename T, int N = 1> class Bitmap
{
public:
  Bitmap();
  Bitmap(int width, int height);
  Bitmap(const BitmapConstRef<T, N> &orig);
  Bitmap(const Bitmap<T, N> &orig);
  Bitmap(Bitmap<T, N> &&orig);
  ~Bitmap();
  Bitmap<T, N> &operator=(const BitmapConstRef<T, N> &orig);
  Bitmap<T, N> &operator=(const Bitmap<T, N> &orig);
  Bitmap<T, N> &operator=(Bitmap<T, N> &&orig);
  /// Bitmap width in pixels.
  int width() const;
  /// Bitmap height in pixels.
  int height() const;
  T *operator()(int x, int y);
  const T *operator()(int x, int y) const;
  explicit operator T *();
  explicit operator const T *() const;
  operator BitmapRef<T, N>();
  operator BitmapConstRef<T, N>() const;

private:
  T *pixels;
  int w, h;
};
}// namespace msdfgen
