/* Your code here! */
#include "dsets.h"
#include <vector>

 /**
     * Creates n unconnected root nodes at the end of the vector.
     * @param num The number of nodes to create
     */
void DisjointSets::addelements(int num){
    for (int i = 0; i < num; i++){
        elements_.push_back(-1);
    }
}


int DisjointSets::find(int elem){
    if (isRoot(elem)){return elem;}
    elements_[elem] = find(elements_[elem]);
    return elements_[elem];
}

/**
 * This function should be implemented as union-by-size. That is, when you
 * setunion two disjoint sets, the smaller (in terms of number of nodes)
 * should point at the larger. This function works as described in lecture,
 * except that you should not assume that the arguments to setunion are
 * roots of existing uptrees.
 *
 * Your setunion function SHOULD find the roots of its arguments before
 * combining the trees. If the two sets are the same size, make the tree
 * containing the second argument point to the tree containing the first.
 * (Note that normally we could break this tie arbitrarily, but in this case
 * we want to control things for grading.)
 *
 * @param a Index of the first element to union
 * @param b Index of the second element to union
 */
void DisjointSets::setunion(int a, int b){
    if (!inbounds(a) || !inbounds(b)) return;
    //find cardinal (representative) elements for each element
    int canA = find(a);
    int canB = find(b);
    if (canA == canB) return;
    if (elements_[canA] <= elements_[canB]) {
        elements_[canA] += elements_[canB]; 
        elements_[canB] = canA;
        return;
    }
    elements_[canB] += elements_[canA]; 
    elements_[canA] = canB;
}

/**
 * This function should return the number of nodes in the up-tree containing 
 * the element.
 * @return number of nodes in the up-tree containing the element
 */
int DisjointSets::size(int elem){
    return -elements_[find(elem)];
}


//to avoid running into issues when indexing the vector
bool DisjointSets::inbounds(int index){
    if (index >=0 && index < static_cast<int>(elements_.size())){
        return true;
    }
    return false;
}
//checks if index is a root
bool DisjointSets::isRoot(int index){
    return (elements_[index] < 0);
}