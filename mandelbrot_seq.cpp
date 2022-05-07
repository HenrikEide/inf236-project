#include <getopt.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

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
        fprintf(stderr, "Usage: %s [-i max_iter] [-s image_size] [-x x_min] [-X x_max] [-y y_min] [-Y y_max]\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  if (mandelbrot.unset()) {
    fprintf(stderr, "Usage: %s [-i max_iter] [-s image_size] [-x x_min] [-X x_max] [-y y_min] [-Y y_max]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  mandelbrot.set_size();

  return 0;
}