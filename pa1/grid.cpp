#include "grid.h"
#include "grid_given.cpp"

// PA1 functions


/**
 * Destroys the current Grid. This function should ensure that
 * memory does not leak on destruction of a grid.
 */
Grid::~Grid(){ /*your code here*/
    clear();
}

/**
 * Rotate row r (row 0 is the first) by count positions.
 * If row r is ABCDE (left to right) in grid g then row r
 * in grid g should be DEABC after the call g.rotateR(r, 2).
 * Rotate headOfCol_ if necessary.
 */
void Grid::rotateR(int r, int count) { /* your code here */
    r = r%numRows();
    if(count == 0) {
        if(r == 0){
        Node *headCol = headOfRow_[r];
        for(int i = 0; i < numCols();i++){
            headOfCol_[i] = headCol;
            headCol = headCol->right;
        }
      }
      return;
    }
    Node* head = headOfRow_[r];
    rotateRHelper(head, r, numCols()-1);
    
    rotateR(r, count-1);

}

void Grid::rotateRHelper(Node * & node, int r, int count){
    if(count== 0){
        headOfRow_[r == 0 ? numRows()-1:r-1]->down = node;
        headOfRow_[r == numRows() - 1? 0:r+1]->up = node;
        node->up = headOfRow_[r == 0 ? numRows()-1:r-1];
        node->down = headOfRow_[r == numRows() - 1? 0:r+1];
        headOfRow_[r] = node;
        return;
    }
    node->right->up->down = node;
    node->right->down->up = node;
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
    c = c%numCols();
    if(count == 0) {
      if(c == 0){
        Node *headRow = headOfCol_[c];
        for(int i = 0; i < numRows();i++){
            headOfRow_[i] = headRow;
            headRow = headRow->down;
        }
      }
      return;
    }
    Node* head = headOfCol_[c];
    rotateCHelper(head, c, numRows()-1);
    rotateC(c, count-1);
}

void Grid::rotateCHelper(Node * & node, int c, int count){
    if(count == 0){
        headOfCol_[c == 0 ? numCols()-1:c-1]->right = node;
        headOfCol_[c == numCols() - 1? 0:c+1]->left = node;
        node->left = headOfCol_[c == 0? numCols() - 1: c-1];
        node->right = headOfCol_[c == numCols() - 1 ? 0: c+1];
        headOfCol_[c] = node;
        return;
    }
    node->down->left->right = node;
    node->down->right->left = node;
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
    bheight_ = 0;
    bwidth_ = 0;
    int rows = numRows();
    int cols = numCols();
    for(int i = 0; i < rows; i++){
        Node * ptr = headOfRow_[i];
        for(int j = 0; j < cols; j++){
            Node * temp = ptr->right;
            delete ptr;
            ptr = temp;
        }
        // headOfRow_.erase(headOfRow_.begin() + i);
    }
    headOfRow_.clear();
    headOfCol_.clear();
  
}


/**
 * Makes the current Grid a copy of the "other" Grid.
 * The dimensions should be the same.  The Nodes should
 * contain the same blocks, but the Nodes should be newly
 * allocated. This function is used in both the copy
 * constructor and the assignment operator for Grids.
 */
void Grid::copy(Grid const& other) { /*your code here*/
    bwidth_ = other.bwidth();
    bheight_ = other.bheight();

    if( bwidth_ == 0 || bheight_ == 0 ) {
    bwidth_ = 0;
    bheight_ = 0;
    return;
  }

  int nRows = other.numRows();
  int nCols = other.numCols();

  vector < vector < Node * > > A;
  for( int j=0; j<nRows; j++ ) {
    vector < Node * > temp;
    Node* node = other.headOfRow_[j];
   
    for( int i=0; i<nCols; i++ ) {
      Node* p = new Node(node->block);
      temp.push_back(p);
      node = node->right;
    }
    A.push_back(temp);
  }
  // Set up the pointer structure between Nodes
  for( int j=0; j<nRows; j++ ) {
    for( int i=0; i<nCols; i++ ) {
      Node *p = A[j][i];
      // The following uses the C++ conditional operator
      // (also known as the C ternary operator):
      //
      // (condition) ? (if_true) : (if_false)
      //
      // which has the value if_true if the condition is true
      // and has the value if_false otherwise.
      p->up    = A[(j==0) ? nRows-1 : j-1] [i]; 
      p->down  = A[(j==nRows-1) ? 0 : j+1][i];
      p->left  = A[j] [(i==0) ? nCols-1 : i-1];
      p->right = A[j] [(i==nCols-1) ? 0 : i+1];
    }
  }
  for( int j=0; j<nRows; j++ ) {
    headOfRow_.push_back(A[j][0]);
  }
  for( int i=0; i<nCols; i++ ) {
    headOfCol_.push_back(A[0][i]);
  }

}
