#include <cstdlib>
#include <cstring>
#include <ctime>

struct complex {
  float real, imag;
};

struct position {
  int x, y;
};

struct Mandelbrot {
  size_t size;
  size_t maxIter;
  size_t width, height;
  float xMax, xMin;
  float yMax, yMin;

  Mandelbrot() {
    size = 1000;
    maxIter = 1000;
    width = 0;
    height = 0;
    xMax = 0.0;
    xMin = 0.0;
    yMax = 0.0;
    yMin = 0.0;
  }

  bool unset() const { return this->xMax == 0.0 || this->xMin == 0.0 || this->yMax == 0.0 || this->yMin == 0.0; }

  void set_size() {
    this->width = static_cast<size_t>((this->xMax - this->xMin) / static_cast<float>(size));
    this->height = static_cast<size_t>((this->yMax - this->yMin) / static_cast<float>(size));
  }
};

size_t computePixel(position pos);
