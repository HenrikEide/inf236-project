#include <cstdlib>
#include <cstring>
#include <ctime>
#include <tuple>
#include <vector>

using namespace std;

struct complex {
  float real, imag;

  complex(float _real, float _imag) {
    real = _real;
    imag = _imag;
  }
};

struct Mandelbrot {
  size_t maxIter;
  size_t width, height;
  float xMax, xMin;
  float yMax, yMin;

  Mandelbrot() {
    maxIter = 1000;
    width = 1024;
    height = 768;
    xMax = 0.0;
    xMin = 0.0;
    yMax = 0.0;
    yMin = 0.0;
  }

  bool unset() const { return this->xMax == 0.0 || this->xMin == 0.0 || this->yMax == 0.0 || this->yMin == 0.0; }
};

size_t computePixel(float _x, float _y, Mandelbrot mandelbrot);
void setColor(size_t x, size_t y, size_t iteration, Mandelbrot mandel, vector<tuple<int, int, int>>& image);
void writeImage(Mandelbrot mandel, const vector<tuple<int, int, int>>& image);