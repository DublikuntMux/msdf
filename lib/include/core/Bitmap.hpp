#pragma once

#include <cstdlib>
#include <cstring>

#include "core/BitmapRef.hpp"

namespace msdfgen {
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

template<typename T, int N> Bitmap<T, N>::Bitmap() : pixels(NULL), w(0), h(0) {}

template<typename T, int N> Bitmap<T, N>::Bitmap(int width, int height) : w(width), h(height)
{
  pixels = new T[N * w * h];
}

template<typename T, int N> Bitmap<T, N>::Bitmap(const BitmapConstRef<T, N> &orig) : w(orig.width), h(orig.height)
{
  pixels = new T[N * w * h];
  memcpy(pixels, orig.pixels, sizeof(T) * N * w * h);
}

template<typename T, int N> Bitmap<T, N>::Bitmap(const Bitmap<T, N> &orig) : w(orig.w), h(orig.h)
{
  pixels = new T[N * w * h];
  memcpy(pixels, orig.pixels, sizeof(T) * N * w * h);
}

template<typename T, int N> Bitmap<T, N>::Bitmap(Bitmap<T, N> &&orig) : pixels(orig.pixels), w(orig.w), h(orig.h)
{
  orig.pixels = NULL;
  orig.w = 0, orig.h = 0;
}

template<typename T, int N> Bitmap<T, N>::~Bitmap() { delete[] pixels; }

template<typename T, int N> Bitmap<T, N> &Bitmap<T, N>::operator=(const BitmapConstRef<T, N> &orig)
{
  if (pixels != orig.pixels) {
    delete[] pixels;
    w = orig.width, h = orig.height;
    pixels = new T[N * w * h];
    memcpy(pixels, orig.pixels, sizeof(T) * N * w * h);
  }
  return *this;
}

template<typename T, int N> Bitmap<T, N> &Bitmap<T, N>::operator=(const Bitmap<T, N> &orig)
{
  if (this != &orig) {
    delete[] pixels;
    w = orig.w, h = orig.h;
    pixels = new T[N * w * h];
    memcpy(pixels, orig.pixels, sizeof(T) * N * w * h);
  }
  return *this;
}

template<typename T, int N> Bitmap<T, N> &Bitmap<T, N>::operator=(Bitmap<T, N> &&orig)
{
  if (this != &orig) {
    delete[] pixels;
    pixels = orig.pixels;
    w = orig.w, h = orig.h;
    orig.pixels = NULL;
  }
  return *this;
}

template<typename T, int N> int Bitmap<T, N>::width() const { return w; }

template<typename T, int N> int Bitmap<T, N>::height() const { return h; }

template<typename T, int N> T *Bitmap<T, N>::operator()(int x, int y) { return pixels + N * (w * y + x); }

template<typename T, int N> const T *Bitmap<T, N>::operator()(int x, int y) const { return pixels + N * (w * y + x); }

template<typename T, int N> Bitmap<T, N>::operator T *() { return pixels; }

template<typename T, int N> Bitmap<T, N>::operator const T *() const { return pixels; }

template<typename T, int N> Bitmap<T, N>::operator BitmapRef<T, N>() { return BitmapRef<T, N>(pixels, w, h); }

template<typename T, int N> Bitmap<T, N>::operator BitmapConstRef<T, N>() const
{
  return BitmapConstRef<T, N>(pixels, w, h);
}
}// namespace msdfgen
