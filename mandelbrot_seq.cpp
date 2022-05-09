#include <getopt.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <tuple>
#include <vector>

#include "mandelbrot.h"

using namespace std;

int main(int argc, char *argv[]) {
  int opt;
  auto mandelbrot = Mandelbrot();

  while ((opt = getopt(argc, argv, "i:w:h:x:X:y:Y:")) != -1) {
    switch (opt) {
      case 'i':
        mandelbrot.maxIter = static_cast<size_t>(atoi(optarg));
        break;
      case 'w':
        mandelbrot.width = static_cast<size_t>(atoi(optarg));
        break;
      case 'h':
        mandelbrot.height = static_cast<size_t>(atoi(optarg));
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
        fprintf(stderr, "Usage: %s [-i max_iter] [-w width] [-h height] [-x x_min] [-X x_max] [-y y_min] [-Y y_max]\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  if (mandelbrot.unset()) {
    fprintf(stderr, "Usage: %s [-i max_iter] [-w width] [-h height] [-x x_min] [-X x_max] [-y y_min] [-Y y_max]\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  auto image = vector<tuple<int, int, int>>(mandelbrot.height * mandelbrot.width);

  auto realScale = (mandelbrot.xMax - mandelbrot.xMin) / static_cast<float>(mandelbrot.width);
  auto imagScale = (mandelbrot.yMax - mandelbrot.yMin) / static_cast<float>(mandelbrot.height);

  for (size_t y = 0; y < mandelbrot.height; ++y) {
    auto yy = mandelbrot.yMin + static_cast<float>(y) * imagScale;

    for (size_t x = 0; x < mandelbrot.width; ++x) {
      auto xx = mandelbrot.xMin + static_cast<float>(x) * realScale;

      auto iteration = computePixel(xx, yy, mandelbrot);
      setColor(x, y, iteration, mandelbrot, image);
    }
  }

  writeImage(mandelbrot, image);

  cout << "finished!" << endl;

  return 0;
}