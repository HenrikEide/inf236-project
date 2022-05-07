#include "mandelbrot.h"

#include <complex>
#include <vector>

using namespace std;

// https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
size_t computePixel(position pos) {
  auto x0 = 0.0;
  auto y0 = 0.0;

  auto x2 = 0.0;
  auto y2 = 0.0;

  auto x = 0.0;
  auto y = 0.0;

  size_t iteration = 0;
  size_t maxIteration = 1000;

  while ((x2 + y2 <= 4) && iteration < maxIteration) {
    y = 2 * x * y + y0;
    x = x2 - y2 + x0;
    x2 = x * x;
    y2 = y * y;
    iteration++;
  }

  return iteration;
}

// https://stackoverflow.com/a/16505538/273503
// CC BY-SA 3.0
int COLORS[17][3] = {
    // R   G   B
    {66, 30, 15},     // brown 3
    {25, 7, 26},      // dark violet
    {9, 1, 47},       // darkest blue
    {4, 4, 73},       // blue 5
    {0, 7, 100},      // blue 4
    {12, 44, 138},    // blue 3
    {24, 82, 177},    // blue 2
    {57, 125, 209},   // blue 1
    {134, 181, 229},  // blue 0
    {211, 236, 248},  // lightest blue
    {241, 233, 191},  // lightest yellow
    {248, 201, 95},   // light yellow
    {255, 170, 0},    // dirty yellow
    {204, 128, 0},    // brown 0
    {153, 87, 0},     // brown 1
    {106, 52, 3},     // brown 2
};