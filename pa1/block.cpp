#include "block.h"

/**
 * Returns the width of the block.
 */
int Block::width() const{/*your code here*/
  return w;
}

/**
 * Returns the height of the block.
 */
int Block::height() const{/*your code here*/
  return h;
}

/**
 * Default Block constructor.
 */
Block::Block() {/* nothing */}

/**
 * Useful Block constructor.
 * Makes a block from the rectangle of width by height pixels in im
 * whose upper-left corner is at position (x,y).
 */
Block::Block(PNG & im, int x, int y, int width, int height) {/*your code here*/
  w = width;
  h = height;
  this->x = x;
  this->y = y;
  image_ref = im;
}

/**
 * Draws the block at position (x,y) in the image im
 */
void Block::render(PNG & im, int x, int y) const {/*your code here*/
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      HSLAPixel * pixel = im.getPixel(x + i, y + j);
      //Copy pixel from one image to the other
      pixel->h = image_ref.getPixel(this->x + i, this->y + j)->h;
      pixel->s = image_ref.getPixel(this->x + i, this->y + j)->s;
      pixel->l = image_ref.getPixel(this->x + i, this->y + j)->l;
      pixel->a = image_ref.getPixel(this->x + i, this->y + j)->a;

      if (gray_flag == 0) {
        pixel->s = 0.0;
      }
    }
  } 
}

/**
 * Changes the saturation of every pixel in the block to 0,
 * which removes the color, leaving grey.
 */
void Block::greyscale() {/*your code here*/
  gray_flag = 0;
}
