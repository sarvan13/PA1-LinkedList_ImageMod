#include "grid.h"
#include "grid_given.cpp"
//#include <cmath>

// PA1 functions


/**
 * Destroys the current Grid. This function should ensure that
 * memory does not leak on destruction of a grid.
 */
Grid::~Grid(){ 
  clear();
}

/**
 * Rotate row r (row 0 is the first) by count positions.
 * If row r is ABCDE (left to right) in grid g then row r
 * in grid g should be DEABC after the call g.rotateR(r, 2).
 * Rotate headOfCol_ if necessary.
 */
void Grid::rotateR(int r, int count) {
  //Rotate right if positive
  if (count >= 0) {
    for (int i = 0; i < count; i++) { 
       Node * curr = headOfRow_[r];
       //Nodes that will be the last Node's (head->left)
       // final neighbours
       Node * last_down = curr->down;
       Node * last_up = curr->up;

      //Change pointers so neighbouring Nodes are correct
      //For all nodes except the last    
      for (int i = 0; i < numCols() - 1; i++) {
        curr->up = curr->right->up;
        curr->down = curr->right->down;
        curr->right->up->down = curr;
        curr->right->down->up = curr;

        curr = curr->right;
      }
      //Correct the neighbours for the last Node
      curr->up = last_up; 
      curr->down = last_down;
      last_up->down = curr;
      last_down->up = curr;

      //Change the head of the row to be the last Node
      headOfRow_[r] = headOfRow_[r]->left;
    }
  }

  //Rotate left if negative
  else {
     r = r * (-1);
     for (int i = 0; i < count; i++) { 
       Node * curr = headOfRow_[r];
       //Nodes that will be the last Node's (head->right)
       // final neighbours
       Node * last_down = curr->down;
       Node * last_up = curr->up;

      //Change pointers so neighbouring Nodes are correct
      //For all nodes except the last    
      for (int i = 0; i < numCols() - 1; i++) {
        curr->up = curr->left->up;
        curr->down = curr->left->down;
        curr->left->up->down = curr;
        curr->left->down->up = curr;

        curr = curr->left;
      }
      //Correct the neighbours for the last Node
      curr->up = last_up; 
      curr->down = last_down;
      last_up->down = curr;
      last_down->up = curr;

      //Change the head of the row to be the last Node
      headOfRow_[r] = headOfRow_[r]->right;
    }
     
  }

  cout << "Rotated Row" << endl; 
}

/**
 * Rotate column c (column 0 is the first) by count positions.
 * If column c is ABCDE (top to bottom) in grid g then column c
 * in grid g should be DEABC after the call g.rotateC(c, 2). 
 * Rotate headOfRow_ if necessary.
 */
void Grid::rotateC(int c, int count) {
  //Rotate down if positive
  if (count >= 0) {
    for (int i = 0; i < count; i++) { 
       Node * curr = headOfCol_[c];
       //Nodes that will be the last Node's (head->up)
       // final neighbours
       Node * last_right = curr->right;
       Node * last_left = curr->left;

      //Change pointers so neighbouring Nodes are correct
      //For all nodes except the last    
      for (int i = 0; i < numRows() - 1; i++) {
        curr->right = curr->down->right;
        curr->left = curr->down->left;
        curr->down->right->left = curr;
        curr->down->left->right = curr;

        curr = curr->down;
      }
      //Correct the neighbours for the last Node
      curr->right = last_right; 
      curr->left = last_left;
      last_left->right = curr;
      last_right->left = curr;

      //Change the head of the row to be the last Node
      headOfCol_[c] = headOfCol_[c]->up;
    }
  }

  //Rotate Up if negative
  else {
    c = c * (-1);
    for (int i = 0; i < count; i++) { 
      Node * curr = headOfCol_[c];
      //Nodes that will be the last Node's (head->down)
      // final neighbours
      Node * last_right = curr->right;
      Node * last_left = curr->left;

     //Change pointers so neighbouring Nodes are correct
      for (int i = 0; i < numRows() - 1; i++) {
        curr->right = curr->up->right;
        curr->left = curr->up->left;
        curr->up->right->left = curr;
        curr->up->left->right = curr;
       
        curr = curr->up;
      } 
      //Correct the neighbours for the last Node
      curr->right = last_right;
      curr->left = last_left;
      last_left->right = curr;
      last_right->left = curr;

      headOfCol_[c] = headOfCol_[c]->down;
    } 
  }

  cout << "Rotated Col" << endl; 
}



/**
 * Destroys all dynamically allocated memory associated with the
 * current Grid class. Clears headOfRow_ and headOfCol_ vectors.
 * Sets bwidth_, bheight_ to zero.
 * After clear() the grid represents an empty grid.
 */
void Grid::clear(){
  bwidth_ = 0;
  bheight_ = 0;
 
  for (int i = 0; i < headOfRow_.size(); i++) {
    cout << "Clear " << i << endl;
    delete_row(headOfRow_[i]);

  }
  
  headOfRow_.clear();
  headOfCol_.clear();

}


/**
 * Destroys the row of Nodes.
 */
void Grid::delete_row(Node * & curr) {
  for (int i = 0; i < numCols(); i++) {
      Node *t = curr;
      curr = curr->right;
      cout << "Node " << t << endl;
      delete t;
  }  
 /*  if ( i == numCols() - 1) {
      delete curr;
      curr = NULL;
    }*/
}


/**
 * Makes the current Grid a copy of the "other" Grid.
 * The dimensions should be the same.  The Nodes should
 * contain the same blocks, but the Nodes should be newly
 * allocated. This function is used in both the copy
 * constructor and the assignment operator for Grids.
 */
void Grid::copy(Grid const& other) { /*your code here*/
  //Clear self
  this->clear();

  //Copy 'other' to self
  bheight_ = other.bheight_;
  bwidth_ = other.bwidth_;

  // Set up a temporary two-dimensional vector of ptrs to Nodes containing
  // the correct sub-blocks of the image.
  vector < vector < Node * > > A;
  for( int j=0; j<other.numRows(); j++ ) {
    vector < Node * > temp;
    Node * temp_node = other.headOfRow_[j];
    for( int i=0; i<other.numCols(); i++ ) {
      Node* p = new Node(temp_node->block);
      temp_node = temp_node->right;
      temp.push_back(p);
    }
    A.push_back(temp);
  }
  // Set up the pointer structure between Nodes
  for( int j=0; j<other.numRows(); j++ ) {
    for( int i=0; i<other.numCols(); i++ ) {
      Node *p = A[j][i];
      // The following uses the C++ conditional operator
      // (also known as the C ternary operator):
      //
      // (condition) ? (if_true) : (if_false)
      //
      // which has the value if_true if the condition is true
      // and has the value if_false otherwise.
      p->up    = A[(j==0) ? other.numRows()-1 : j-1] [i]; 
      p->down  = A[(j==other.numRows()-1) ? 0 : j+1][i];
      p->left  = A[j] [(i==0) ? other.numCols()-1 : i-1];
      p->right = A[j] [(i==other.numCols()-1) ? 0 : i+1];
    }
  }
  for( int j=0; j<other.numRows(); j++ ) {
    headOfRow_.push_back(A[j][0]);
  }
  for( int i=0; i<other.numCols(); i++ ) {
    headOfCol_.push_back(A[0][i]);
  }
}

