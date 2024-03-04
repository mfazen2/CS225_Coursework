/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]){ return true;}
    if (first[curDim] == second[curDim]){return (first < second);}
    return false;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    int currdist = 0;
    int potdist = 0;
    for (int i = 0; i < Dim; i++){
      currdist += (currentBest[i]-target[i])*(currentBest[i]-target[i]);
      potdist += (potential[i]-target[i])*(potential[i]-target[i]);
    }
    if (potdist < currdist){return true;}
    if (potdist == currdist){return potential < currentBest;}
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> listcopy;
    auto iter = newPoints.begin();
    while(iter != newPoints.end()){
      listcopy.push_back((*iter));
      iter++;
    }
    int right = listcopy.size() - 1;

    this->root = TreeBuilder(listcopy,0,0,right);
}
template<int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::TreeBuilder(vector<Point<Dim>>& list, int dim, int left,int right){
  this->size = 0;
  if (list.empty() || left > right || left > static_cast<int>(list.size()) || right > static_cast<int>(list.size()) || left < 0 || right < 0){
    return NULL;
  }
  KDTreeNode * subroot;
  int med = (left + right)/2;
  auto median = list.begin()+((left + right)/2);
  auto begin = list.begin()+left;
  auto end = list.begin()+right;
  auto cmp = [](Point<Dim> lhs, Point<Dim> rhs){return lhs <= rhs;};
  select(begin,end,median,cmp);
  subroot = new KDTreeNode((*median));
  dim++;
  size++;
  //do dim%Dim to stop it from exceeding Dim value, will roll over to beginning
  subroot->left = TreeBuilder(list,dim % Dim, left,med - 1);
  subroot->right = TreeBuilder(list,dim % Dim, med+1,right);
  return subroot;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  CopyHelper(this->root,other->root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  GeneralDestructor(this->root);
  CopyHelper(this->root,rhs.root);
  return *this;
}
template <int Dim>
void KDTree<Dim>::CopyHelper(KDTreeNode *thisTree, KDTreeNode * otherTree){
  if (otherTree == NULL){
    thisTree = NULL;
  } else {
    thisTree = new KDTreeNode();
    thisTree->point = otherTree->point;
    CopyHelper(thisTree->left,otherTree->left);
    CopyHelper(thisTree->right, otherTree->right);
  }
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  GeneralDestructor(this->root);
}
template<int Dim>
void KDTree<Dim>::GeneralDestructor(KDTreeNode *& node){
  if (node != NULL){
    GeneralDestructor(node->left);
    GeneralDestructor(node->right);
    delete node;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {
    /**
     * @todo Implement this function!
     */

    return findHelper(query,root,0);
}
template <int Dim>
Point<Dim> KDTree<Dim>::findHelper(const Point<Dim>& query, KDTreeNode* node, int currdim) const {
  if (node->left == NULL && node->right == NULL){
    return node->point;
  }
  Point<Dim> best = node->point;
  Point<Dim> closest = best;
  
}

template <typename RandIter, typename Comparator>
RandIter Partition(RandIter begin, RandIter stop,RandIter pivot, Comparator cmp){
  auto pivotval = *pivot;
  std::iter_swap(pivot,stop);
  RandIter storeIndex = begin;
  int loopcount = (stop) - begin;
  for (int i = 0; i < loopcount;i++){
    RandIter temp = begin + i;
    if (cmp(*temp,pivotval)){std::iter_swap(storeIndex,temp); storeIndex++;}

  }
  std::iter_swap(stop,storeIndex);
  return storeIndex;
}
template <typename RandIter, typename Comparator> 
void select(RandIter start, RandIter end, RandIter k, Comparator cmp){
 
  RandIter temp = start;
  RandIter temp2 = start;
  RandIter tempend = end;
  while (temp != end){
    std::cout << *temp << std::endl;
    temp++;
  }
  std::cout << "\n\n" << std::endl;
  if (start == end){
    return;
  }
  RandIter right = end -1;
  while (true){
  std::cout << "looping" << std::endl;
  if (start == right){
    return;
  }
    RandIter pivot = k;
    pivot = Partition(start,right,pivot,cmp);
    if (k == pivot) {
      return;
    }
    if (cmp(*k,*pivot)){
      right = pivot - 1;
    } else {
      start = pivot + 1;
    }
  }
  while (temp2 != tempend){
    std::cout << *temp2 << std::endl;
    temp2++;
  }
}

