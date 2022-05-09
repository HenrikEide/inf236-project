#include "mandelbrot.h"

#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

// https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
size_t computePixel(float _x, float _y, Mandelbrot mandelbrot) {
  float x = 0.0;
  float y = 0.0;

  size_t iteration = 0;
  size_t maxIteration = mandelbrot.maxIter;

  while ((x * x + y * y <= 2 * 2) && iteration < maxIteration) {
    auto temp = x * x - y * y + _x;
    y = 2 * x * y + _y;
    x = temp;
    iteration++;
  }

  return iteration;
}

// https://stackoverflow.com/a/16505538/273503
// CC BY-SA 3.0
int const COLOR_SIZE = 16;
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

void setColor(size_t x, size_t y, size_t iteration, Mandelbrot mandel, vector<tuple<int, int, int>>& image) {
  if (iteration == mandel.maxIter) {
    image[(mandel.height * y) + x] = make_tuple(COLORS[COLOR_SIZE][0], COLORS[COLOR_SIZE][1], COLORS[COLOR_SIZE][2]);
  } else {
    auto color = iteration % COLOR_SIZE;
    image[(mandel.height * y) + x] = make_tuple(COLORS[color][0], COLORS[color][1], COLORS[color][2]);
  }
}

void writeImage(Mandelbrot mandel, const vector<tuple<int, int, int>>& image) {
  ofstream file;
  file.open("mandelbrot.ppm");
  file << "P6"
       << " " << mandel.height << " " << mandel.width << " "
       << "255" << endl;

  for (const auto& item : image) {
    int r, g, b;
    tie(r, g, b) = item;
    file << r << g << b << "  ";
  }

  file.close();
}
