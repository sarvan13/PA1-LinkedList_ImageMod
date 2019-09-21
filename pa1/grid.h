
/**
 *
 * Two-dimensional circular doubly-linked list (PA 1)
 *
 */

#ifndef _GRID_H_
#define _GRID_H_

#include <algorithm>
#include <iostream>
#include "block.h"
using namespace std;

/**
 * Put your solution to the puzzle here.
 * This is a macro definition.
 * Use the variable "g" to refer to the grid and put a '\'
 * at the end of a line to continue the macro on the next line.
 * The example given here does not solve the puzzle.
 * Replace it with a sequence of rotateR and rotateC commands
 * that does solve the puzzle. 
 * COMPLETE FOR PA1
 */
#define PUZZLE_SOLUTION  g.rotateR(0, 1);\
  g.rotateC(1, -1);\
  g.rotateR(0, 2);\
  g.rotateC(1,1);

/**
 * Grid: This is a container class for blocks. It is implemented
 * as a two-dimensional circular doubly-linked list of nodes, each of
 * which contains a block.
 *
 * You should not remove anything from this class definition, but
 * you may find it helpful to add your own private helper functions to it.
 */
class Grid {
private:

   /**
    * The Node class is private to the Grid class via the principle of
    * encapsulation---the end user does not need to know our node-based
    * implementation details.
    */
   class Node {
   public:
      Node(); // default constructor--GIVEN
      Node(const Block & ndata); // data provided constructor--GIVEN

      Node *left, *right, *up, *down; // ptr to nbr nodes in grid
      const Block block; // block held by Node. const for this PA
   };

public:

   /* =============== public given functions ====================*/
   /**
    * Default constructor.
    * GIVEN
    * @see grid_given.cpp
    */
   Grid();

   /**
    * Constructor that breaks the given PNG into
    * nCols x nRows blocks of the same dimensions and 
    * builds a grid of those blocks.
    * GIVEN
    * @see grid_given.cpp
    */
   Grid(PNG & imIn, int nCols, int nRows);

   /**
    * Copy constructor for a Grid.
    * Since Grids allocate dynamic memory (i.e., they use "new", we
    * must define the Big Three). This depends on your implementation
    * of the copy funtion.
    * GIVEN
    * @see grid_given.cpp
    *
    * @param other The Grid we are copying.
    */
   Grid(const Grid & other);

   /**
    * Overloaded assignment operator for Grids.
    * Part of the Big Three that we must define because the class
    * allocates dynamic memory. This depends on your implementation
    * of the copy and clear funtions.
    * GIVEN
    * @see grid_given.cpp
    *
    * @param rhs The right hand side of the assignment statement.
    */
   Grid & operator=(const Grid & rhs);

   /**
    * Accessor functions.
    * GIVEN
    * @see grid_given.cpp
    */
   int numRows() const;
   int numCols() const;
   int bheight() const;
   int bwidth() const;

   /**
    * Render returns an image consisting the blocks in the grid.
    * GIVEN
    * @see grid_given.cpp
    */
   PNG render();

   /* =============== end of given functions ====================*/

   /* =============== public PA1 FUNCTIONS =========================*/

   /**
    * Grid destructor.
    * Destroys all of the memory associated with the
    * current Grid. This function should ensure that
    * memory does not leak on destruction of a grid.
    * COMPLETE FOR PA1.
    */
   ~Grid();
   void clear();
   /**
    * Rotate row r (row 0 is the first) by count positions.
    * If row r is ABCDE (left to right) in grid g then row r
    * in grid g should be DEABC after the call g.rotateR(r, 2). 
    * COMPLETE FOR PA1.
    */
   void rotateR(int r, int count);

   /**
    * Rotate column c (column 0 is the first) by count positions.
    * If column c is ABCDE (top to bottom) in grid g then column c
    * in grid g should be DEABC after the call g.rotateC(c, 2). 
    * COMPLETE FOR PA1.
    */
   void rotateC(int c, int count);


   /* =============== end of public PA1 FUNCTIONS =========================*/

private:
   /**
    * Private member variables.
    *
    * You must use these as specified in the spec and may not rename them.
    */

   std::vector<Node *> headOfRow_; // ptr to first Node in each row
   std::vector<Node *> headOfCol_; // ptr to first Node in each col

   int bheight_;	// height of blocks in grid.
   int bwidth_;		// width of blocks in grid.

   /**
    * Private helper functions.
    *
    * You must use these as specified in the writeup and may not rename them.
    * You may place more functions here as you need them.
    */

   /* =================== private PA1 functions ============== */

   /**
    * Destroys all dynamically allocated memory associated with the
    * current Grid class. Called by destructor and op=.
    * COMPLETE FOR PA1.
    */
   /**
    * Deletes a row of Nodes in the Grid. Called by clear.
    * @param row_num, the head of the row to be deleted.
    */
   void delete_row(Node * & row_head);

   /**
    * Copies the "other" Grid into the current Grid.
    * Does not free any memory. Called by copy constructor and op=.
    * COMPLETE FOR PA1.
    * @param other, the Grid to be copied.
    */
   void copy(const Grid & other);

   /* =================== end of private PA1 functions ============== */
};

#endif
