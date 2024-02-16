/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    return find(root,key)->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == NULL) {
        return subtree;
    }
    if (subtree->key > key){
        return find(subtree->left,key);
    }
    if(subtree->key < key){
        return find(subtree->right,key);
    }
    return subtree;
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    if (!root){
        root = new Node(key,value);
    } else {
        if (find(root,key) == NULL){
            insert(root,key,value);
        }
        
    }
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    Node*& insertpoint = find(subtree,key);
    insertpoint = new Node(key,value);
   
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    K k2 = second->key;
    V v2 = second->value;
    second->value = first->value;
    second->key = first->key;
    first->key = k2;
    first->value = v2;
    
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root,key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    Node*& toremove = find(subtree,key);
    if(toremove->left == NULL && toremove->right == NULL){
        delete toremove;
        toremove = nullptr;
        return;
    }
    if (toremove->left != NULL && toremove->right == NULL){
        Node* temp = toremove->left;
        delete toremove;
        toremove = temp;
        return;
    }if (toremove->right != NULL && toremove->left == NULL){
        Node*& temp = toremove->right;
        delete toremove;
        toremove = temp;
        return;
    }
    else{
        Node* predecessor = toremove->left;
        while (predecessor->right != NULL){
            predecessor = predecessor->right;
        }
        swap(predecessor,toremove);
        remove(toremove->left,key);

    }
    // your code here
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K,V> b = BST<K,V>();
    for (auto p : inList){
        b.insert(p.first,p.second);
    }
    return b;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::vector<int> out(inList.size());
    for (size_t i = 0; i < inList.size();i++){
        out[i]=0;
    }
    sort(inList.begin(),inList.end());
    size_t h = listBuild(inList).height();
    out[h]++;
    while (std::next_permutation(inList.begin(),inList.end())){
        size_t h = listBuild(inList).height();
        out[h]++;
    }
    for(int a : out){
        std::cout << a << std::endl;
    }
    return out;
}