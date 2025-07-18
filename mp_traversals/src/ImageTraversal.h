/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include <deque>
#include <vector>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

using namespace cs225;

/**
 * @brief Namespace containing everything required for an image traversal.
 * 
 */
namespace Traversals {
  /**
  * The expected type for an add function for a traversal
  * The first parameter is the deque storing a list of points to be processed
  * The second parameter is the new Point that should be added to the deque
  */
  typedef void (*add_function) (std::deque<Point> &, const Point &);
  
  /**
  * The expected type for a pop function for a traversal
  * The first parameter is the deque storing a list of points to be processed
  * The function then removes the next Point from the deque
  */
  typedef void (*pop_function) (std::deque<Point> &);

  /**
  * The expected type for a peek function for a traversal
  * The first parameter is the deque storing a list of points to be processed
  * The function returns the next Point to be processed (without removing it from the deque)
  */
  typedef Point (*peek_function) (std::deque<Point> &);

  /**
   * The set of functions describing a traversal's operation.
   */
  typedef struct TraversalFunctions {
    add_function add;
    pop_function pop;
    peek_function peek;
  } TraversalFunctions;

  void bfs_add(std::deque<Point> & work_list, const Point & point);
  void dfs_add(std::deque<Point> & work_list, const Point & point);

  void bfs_pop(std::deque<Point> & work_list);
  void dfs_pop(std::deque<Point> & work_list);

  Point bfs_peek(std::deque<Point> & work_list);
  Point dfs_peek(std::deque<Point> & work_list);

  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);

  /**
  * A base class for traversal algorithms on images.
  * This class provides a traversal of the image by returning instances of ImageTraversal::Iterator.
  */
  class ImageTraversal {
  public:
    /**
    * A forward iterator through an ImageTraversal.
    */
    class Iterator : std::iterator<std::forward_iterator_tag, Point> {
    public:
      Iterator();
      Iterator(PNG png, Point start, double tolerance,ImageTraversal* tra);
      Iterator & operator++();
      Point operator*();
      bool operator!=(const Iterator &other);
      bool canVisit(Point p);
      size_t size() const;
      bool empty() const;
      bool end;
      /** @todo [Part 1] */
      /** add member functions if neccesary*/
    private:
      /** @todo [Part 1] */
      /** add private members here if neccesary*/
      ImageTraversal* tra_;
      std::deque<Point> work_list_;
      Point pStart_;
      //record points were visited  
      std::vector<std::vector<bool>> visits;
    };

    /**
    * Constructor for the given traversal
    */
    ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns);

    /**
    * Returns an iterator for the traversal starting at the first point (specified in the constructor).
    */
    Iterator begin();
    PNG getPNG();
    /**
    * Returns an iterator for the traversal one past the end of the traversal.
    */
    Iterator end();
    /*canVisit helper function*/
    

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    TraversalFunctions fns_;
    Iterator iter;
    Point begin_;
    PNG png_;
    double tolerance_;
  };
}