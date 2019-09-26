#include "grid.h"
#include "grid_given.cpp"

// PA1 functions


/**
 * Destroys the current Grid. This function should ensure that
 * memory does not leak on destruction of a grid.
 */
Grid::~Grid(){ /*your code here*/

}

/**
 * Rotate row r (row 0 is the first) by count positions.
 * If row r is ABCDE (left to right) in grid g then row r
 * in grid g should be DEABC after the call g.rotateR(r, 2).
 * Rotate headOfCol_ if necessary.
 */
void Grid::rotateR(int r, int count) { /* your code here */
    if(count == 0) return;
    Node* head = headOfRow_[r];
    rotateRHelper(head, r, numCols());
    rotateR(r, count-1);

}

void Grid::rotateRHelper(Node * & node, int r, int count){
    if(count== 0){
        node->up = headOfRow_[r == 0 ? numRows()-1:r-1];
        node->down = headOfRow_[r == numRows() - 1? 0:r+1];
        headOfRow_[r] = node;
    }
    node->up = node->right->up;
    node->down = node->right->down;
    rotateRHelper(node->right, r, count - 1);
}

/**
 * Rotate column c (column 0 is the first) by count positions.
 * If column c is ABCDE (top to bottom) in grid g then column c
 * in grid g should be DEABC after the call g.rotateC(c, 2). 
 * Rotate headOfRow_ if necessary.
 */
void Grid::rotateC(int c, int count) { /* your code here */
    if(count == 0) return;
    Node* head = headOfCol_[c];
    rotateCHelper(head, c, numRows());
    rotateC(c, count-1);
}

void Grid::rotateCHelper(Node * & node, int c, int count){
    if(count == 0){
        node->left = headOfCol_[c == 0? numCols() - 1: c-1];
        node->right = headOfCol_[c == numCols() - 1 ? 0: c+1];
        headOfCol_[c] = node;
    }
    node->right = node->down->right;
    node->left = node->down->left;
    rotateCHelper(node->down, c, count-1);
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Grid class. Clears headOfRow_ and headOfCol_ vectors.
 * Sets bwidth_, bheight_ to zero.
 * After clear() the grid represents an empty grid.
 */
void Grid::clear() { /*your code here*/
    
  
}


/**
 * Makes the current Grid a copy of the "other" Grid.
 * The dimensions should be the same.  The Nodes should
 * contain the same blocks, but the Nodes should be newly
 * allocated. This function is used in both the copy
 * constructor and the assignment operator for Grids.
 */
void Grid::copy(Grid const& other) { /*your code here*/

}
