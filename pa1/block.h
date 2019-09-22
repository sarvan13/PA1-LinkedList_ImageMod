
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
using namespace std;
using namespace cs221util;

/**
 * Block: A class that contains a two-dimensional vector of pixels.
 *
 * You should not remove anything from this class definition.
 */
class Block{

 public:
  Block(); /* default constructor GIVEN */

  /*------- you must implement the remaining functions -------*/
  Block(PNG & im, int x, int y, int width, int height);
  void render(PNG & im, int x, int y) const ;
  void greyscale();
  int width() const;
  int height() const;

 private:

  vector< vector < HSLAPixel > > data;
  int gray_flag = -1;
};
#endif
