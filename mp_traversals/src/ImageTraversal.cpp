#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  PNG ImageTraversal::getPNG(){return png_;}
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }
  /*helper function to determine if a point is visitable*/
  bool ImageTraversal::Iterator::canVisit(Point p){
    if (p.x < tra_->png_.width() && p.y < tra_->png_.height()){
      HSLAPixel start = tra_->png_.getPixel(tra_->begin_.x,tra_->begin_.y);
      HSLAPixel target = tra_->png_.getPixel(p.x,p.y);
      if (calculateDelta(start,target)>=tra_->tolerance_){return false;}
      return true;
    }
    return false;

  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) { 
    fns_ = fns;
    begin_ = start;
    tolerance_ = tolerance;
    png_ = png;
     iter = Iterator(png,start,tolerance,this);
    /** @todo [Part 1] */
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    ImageTraversal::Iterator it = ImageTraversal::Iterator(png_,begin_,tolerance_,this);
    return it;

  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    ImageTraversal::Iterator iter = ImageTraversal::Iterator();
    iter.end = true;
    return iter;
    }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    tra_ = NULL;
    end = false;
    
  }
  ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance,ImageTraversal* tra) {
    /** @todo [Part 1] */
    tra_ = tra;
    pStart_ = start;
    visits = std::vector<std::vector<bool>>(png.width(),std::vector<bool>(png.height(),false));
    end = false;
    if (canVisit(pStart_)){
      visits[pStart_.x][pStart_.y] = true;
    } else {end = true;} 
    
  }
  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    //define and check visitability of our current point's neighbors
    Point n1 = Point(pStart_.x+1,pStart_.y);
    Point n2 = Point(pStart_.x,pStart_.y+1);
    Point n3 = Point(pStart_.x-1,pStart_.y);
    Point n4 = Point(pStart_.x,pStart_.y-1);
    if (canVisit(n1)) tra_->fns_.add(work_list_,n1);
    if (canVisit(n2)) tra_->fns_.add(work_list_,n2);
    if (canVisit(n3)) tra_->fns_.add(work_list_,n3);
    if (canVisit(n4)) tra_->fns_.add(work_list_,n4);
    
    if (work_list_.empty()){end = true; return *this;}
    /*we dont use the typical convention for pop(), so we need to first call pop(), then
    call peek to actually get the next value in the list*/
   
    Point pnext  = tra_->fns_.peek(work_list_);
    tra_->fns_.pop(work_list_);
    
    while (visits[pnext.x][pnext.y]){
      if (work_list_.empty()){end = true;return *this;}
      pnext  = tra_->fns_.peek(work_list_);
      tra_->fns_.pop(work_list_);
    }
    pStart_ = pnext;
    visits[pStart_.x][pStart_.y] = true;
    return *this;

  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return pStart_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    return (end != other.end);
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

}