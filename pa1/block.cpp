#include "block.h"

/**
 * Returns the width of the block.
 */
int Block::width() const{
  return data[0].size();
}

/**
 * Returns the height of the block.
 */
int Block::height() const{/*your code here*/
  return data.size();
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
Block::Block(PNG & im, int x, int y, int width, int height){ 
  for (int j = 0; j < height; j++){
    vector<HSLAPixel> temp;
    for (int i = 0; i < width; i++){
      temp.push_back(*(im.getPixel(x+i,y+j)));
    }
    data.push_back(temp);
  }
}

/**
 * Draws the block at position (x,y) in the image im
 */
void Block::render(PNG & im, int x, int y) const {/*your code here*/
  for (int i = 0; i < width(); i++) {
    for (int j = 0; j < height(); j++) {
      HSLAPixel * pixel = im.getPixel(x + i, y + j);
      //Copy pixel from one image to the other
      pixel->h = data[j][i].h; 
      pixel->s = data[j][i].s; 
      pixel->l = data[j][i].l; 
      pixel->a = data[j][i].a; 

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
