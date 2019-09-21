#include "grid.h"

/**
 * public accessor functions.
 */
int Grid::numRows() const {return headOfRow_.size();}
int Grid::numCols() const {return headOfCol_.size();}
int Grid::bheight() const {return bheight_;}
int Grid::bwidth() const {return bwidth_;} 

/**
 * Default constructor.
 */
Grid::Grid() { /* nothing */ }

/* Most useful Grid constructor.
 * Builds a grid out of the blocks in the
 * given image. The blocks we create
 * have width equal to im.width()/nCols,
 * and height equal to im.height()/nRows.
 * Our Grid is a two-dimensional circular doubly-linked list.
 */
Grid::Grid(PNG & im, int nCols, int nRows) {

  if( nCols == 0 || nRows == 0 ) return;

  bwidth_ = im.width() / nCols;		// width of all Node blocks
  bheight_ = im.height() / nRows;	// height of all Node blocks

  if( bwidth_ == 0 || bheight_ == 0 ) {
    cerr << "ERROR: Cannot divide image of size " <<
      im.width() << "x" << im.height() <<
      " into " << nCols << " columns and " << nRows << " rows." << endl;
    bwidth_ = 0;
    bheight_ = 0;
    return;
  }

  // Set up a temporary two-dimensional vector of ptrs to Nodes containing
  // the correct sub-blocks of the image.
  vector < vector < Node * > > A;
  for( int j=0; j<nRows; j++ ) {
    vector < Node * > temp;
    for( int i=0; i<nCols; i++ ) {
      Node* p = new Node(Block(im, i*bwidth_, j*bheight_, bwidth_, bheight_));
      temp.push_back(p);
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

/* copy constructor */
Grid::Grid(Grid const& other) {
  copy(other); // you'll implement copy()
}

/* assignment operator */
Grid & Grid::operator=(Grid const& rhs) {
   if (this != &rhs) {
      clear(); // you'll implement clear()
      copy(rhs);
   }
   return *this;
}

/**
 * Takes the current grid and renders it into a
 * correctly sized PNG. The blocks in the grid
 * are placed in the image across each row,
 * top to bottom.
 */
PNG Grid::render(){

   PNG im;
   int nRows = numRows();
   int nCols = numCols();
   im.resize(nCols*bwidth_, nRows*bheight_);
   for( int j=0; j<nRows; j++ ) {
     Node *p = headOfRow_[j];
     for( int i=0; i<nCols; i++ ) {
       p->block.render(im, i*bwidth_, j*bheight_);
       p = p->right;
     }
   }
   return im;
}


// Node constructors
Grid::Node::Node() : left(NULL), right(NULL), up(NULL), down(NULL), block(Block())
{ /* nothing */ }

Grid::Node::Node(const Block& ndata) : left(NULL), right(NULL), up(NULL), down(NULL), block(ndata)
{ /* nothing */ }
