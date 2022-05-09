#include <getopt.h>
#include <omp.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <tuple>
#include <vector>

#include "mandelbrot.h"

using namespace std;

int main(int argc, char *argv[]) {
  int opt;
  auto mandelbrot = Mandelbrot();

  while ((opt = getopt(argc, argv, "i:s:x:X:y:Y:")) != -1) {
    switch (opt) {
      case 'i':
        mandelbrot.maxIter = static_cast<size_t>(atoi(optarg));
        break;
      case 's':
        mandelbrot.size = static_cast<size_t>(atoi(optarg));
        break;
      case 'x':
        mandelbrot.xMin = static_cast<float>(atof(optarg));
        break;
      case 'X':
        mandelbrot.xMax = static_cast<float>(atof(optarg));
        break;
      case 'y':
        mandelbrot.yMin = static_cast<float>(atof(optarg));
        break;
      case 'Y':
        mandelbrot.yMax = static_cast<float>(atof(optarg));
        break;
      case '?':
        fprintf(stderr, "Unknown option %c", optopt);
        exit(EXIT_FAILURE);
      default:
        cerr << "Fell through :(" << endl;
        fprintf(stderr, "Usage: %s [-i max_iter] [-w x] [-h y] [-x x_min] [-X x_max] [-y y_min] [-Y y_max]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  if (mandelbrot.unset()) {
    fprintf(stderr, "Usage: %s [-i max_iter] [-w x] [-h y] [-x x_min] [-X x_max] [-y y_min] [-Y y_max]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  auto image = vector<tuple<int, int, int>>(mandelbrot.size * mandelbrot.size);

  auto start = omp_get_wtime();
  auto xScale = (mandelbrot.xMax - mandelbrot.xMin) / static_cast<float>(mandelbrot.size);
  auto yScale = (mandelbrot.yMax - mandelbrot.yMin) / static_cast<float>(mandelbrot.size);

#pragma omp parallel default(none) shared(yScale, xScale, image, mandelbrot)
  {
#pragma omp for
    for (size_t y = 0; y < mandelbrot.size; ++y) {
      auto yy = mandelbrot.yMin + static_cast<float>(y) * yScale;

      for (size_t x = 0; x < mandelbrot.size; ++x) {
        auto xx = mandelbrot.xMin + static_cast<float>(x) * xScale;

        auto iteration = computePixel(xx, yy, mandelbrot);
        setColor(x, y, iteration, mandelbrot, image);
      }
    }
  }

  double end = omp_get_wtime();
  double dur = end - start;

  writeImage(mandelbrot, image);

  cout << "finished!" << endl;
  printf("Computed a %zu * %zu px image in %fs\n", mandelbrot.size, mandelbrot.size, dur);

  return 0;
}