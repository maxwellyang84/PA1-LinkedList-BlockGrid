#include "block.h"

/**
 * Returns the width of the block.
 */
int Block::width() const{/*your code here*/
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
Block::Block(PNG & im, int x, int y, int width, int height) {/*your code here*/
    
    
    int temp_y = y;
    for(int i = 0; i < height; i++){
        vector<HSLAPixel> temp;
        int temp_x = x;
        for(int j = 0; j < width; j++){
            HSLAPixel p = *im.getPixel(temp_x,temp_y);
            temp.push_back(p);
            temp_x++;
        }
        data.push_back(temp);
        temp_y++;
        
    }
}

/**
 * Draws the block at position (x,y) in the image im
 */
void Block::render(PNG & im, int x, int y) const {/*your code here*/
    int temp_y = y;
    for(int i = 0; i < height(); i++){
        int temp_x = x;
        for(int j = 0; j < width(); j++){
            *im.getPixel(temp_x,temp_y) = data[i][j];
            temp_x++;
        }
        temp_y++;
    }
}

/**
 * Changes the saturation of every pixel in the block to 0,
 * which removes the color, leaving grey.
 */
void Block::greyscale() {/*your code here*/
    for(int i = 0; i < height(); i++){
        for(int j = 0; j < width(); j++){
            data[i][j].s = 0;
        }
    }
}
