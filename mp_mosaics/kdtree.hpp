/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] == second[curDim]){
      return first < second;
    }
    return (first[curDim] < second[curDim]);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    float distance1 = 0;
    float distance2 = 0;
    for (int i = 0; i < Dim; i++){
      float distance1_temp = (target[i] - currentBest[i]);
      float distance2_temp = (target[i] - potential[i]);
      distance1 += distance1_temp * distance1_temp;
      distance2 += distance2_temp * distance2_temp;
    }

    if(distance1 == distance2){
      return (potential < currentBest);
    }

    return (distance2 < distance1);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    if(newPoints.empty()){
      root = NULL;
      size = 0;
      return;
    }
    root = new KDTreeNode();
    size = 0;
    vector<Point<Dim>> sort;
    sort.assign(newPoints.begin(), newPoints.end());
    std::cout << "flag3" << std::endl;
    KDTree_help(root, sort, 0);
}

template <int Dim>
void KDTree<Dim>::KDTree_help(KDTreeNode* parent, vector<Point<Dim>>& newPoints, unsigned curr_dim)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.size()>=3){
      int median_index = (newPoints.size()-1)/2;
      sort(newPoints, 0, newPoints.size() - 1, median_index, curr_dim);
      parent->point = newPoints[median_index];
      newPoints.erase(newPoints.begin() + median_index);
      KDTreeNode* left_temp = new KDTreeNode();
      parent->left = left_temp;
      vector<Point<Dim>> left_array;
      KDTreeNode* right_temp = new KDTreeNode();
      parent->right = right_temp;
      vector<Point<Dim>> right_array;
      for(unsigned i = 0; i < newPoints.size(); i++){
        if(smallerDimVal(newPoints[i], parent->point, curr_dim)){
          left_array.push_back(newPoints[i]);
        }else{
          right_array.push_back(newPoints[i]);
        }
      }
      size += 2;
      KDTree_help(parent->left, left_array, (curr_dim + 1) % Dim);
      KDTree_help(parent->right, right_array, (curr_dim + 1) % Dim);

    }else if(newPoints.size() == 2){
      size += 2;
      KDTreeNode* right_temp = new KDTreeNode();
      parent->right = right_temp;
      if(smallerDimVal(newPoints[0], newPoints[1], curr_dim)){
        parent->point = newPoints[0];
        parent->right->point = newPoints[1];
      }else{
        parent->point = newPoints[1];
        parent->right->point = newPoints[0];
      }
      
    }else if(newPoints.size() == 1){
      size++;
      parent->point = newPoints[0];
    }
    
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, unsigned left, unsigned right, unsigned curDim){
  unsigned pivot_index = right;
  Point<Dim> median = newPoints[pivot_index];
  unsigned storeIndex = left;
  for(unsigned i = left; i <= right; i++){
    if(smallerDimVal(newPoints[i], median, curDim)){
      Point<Dim> temp = newPoints[i];
      newPoints[i] = newPoints[storeIndex];
      newPoints[storeIndex] = temp;
      storeIndex++;
    }
  }
  Point<Dim> temp = newPoints[pivot_index];
  newPoints[pivot_index] = newPoints[storeIndex];
  newPoints[storeIndex] = temp;
  return storeIndex;

}

  

template <int Dim>
void KDTree<Dim>::sort(vector<Point<Dim>>& newPoints, unsigned left, unsigned right,  unsigned median_index, unsigned curDim)
{
  unsigned pivotIndex = partition(newPoints, left, right, curDim);

  if (median_index == pivotIndex) {
      return;
  } else if (median_index < pivotIndex) {
      sort(newPoints, left, pivotIndex - 1, median_index, curDim);
  } else {
      sort(newPoints, pivotIndex + 1, right, median_index, curDim);
  }
  return;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  
  if (other.root != NULL) {
    this->root = new KDTreeNode((other.root)->point);
    this->size = other.size;
    this->root->left = copy((other.root)->left);
    this->root->right = copy((other.root)->right);
  }else{
    this->root = NULL;
    this->size = 0;
  }

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (*this != rhs){
    size = 0;
    if (root != NULL) {
      deleter(root->left);
      deleter(root->right);
      delete root; root = NULL;
    }
    if (rhs.root != NULL){
      this->root = new KDTreeNode((rhs.root)->point);
      this->root->left = copy((rhs.root)->left);
      this->root->right = copy((rhs.root)->right);
      this->size = rhs.size;
    }
  }

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  if (root != NULL){
    deleter(root->left);
    deleter(root->right);
    delete root;
    root = NULL;
  }
  size = 0;
}

template <int Dim>
void KDTree<Dim>::deleter(KDTreeNode* current){
  if(current == NULL){
    return;
  }
  deleter(current->left);
  deleter(current->right);
  delete current;
  current = NULL;
  return;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* other) {
    if (other != NULL) {
        return NULL;
    }
    KDTreeNode* current = new KDTreeNode(other->point);
    current->left = copy(other->left);
    current->right = copy(other->right);
    return current;
}



template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> closest = this->root->point;
    find_closest(this->root, closest, query, 0);
    return closest;
}

template <int Dim>
void KDTree<Dim>::find_closest(KDTreeNode* traverse_node, Point<Dim>& current_closest, const Point<Dim>& query, unsigned curdim) const{
    if(traverse_node == NULL){
      return;
    }

    bool check_left = 0;
    if(smallerDimVal(query, traverse_node->point, curdim)){
      find_closest(traverse_node -> left, current_closest, query, (curdim + 1)%Dim);
      check_left = 1;
    }else{
      find_closest(traverse_node -> right, current_closest, query, (curdim + 1)%Dim);
    }

    if(shouldReplace(query, current_closest, traverse_node->point)){
      current_closest = traverse_node->point;
    }

    int distance_total = 0;
    float distance1 = 0;
    for (int i = 0; i < Dim; i++){
      float distance1_temp = (query[i] - current_closest[i]);
      distance_total += distance1_temp * distance1_temp;
    }
    distance_total = std::sqrt(distance_total);
    int distance_on_curdim = std::abs(traverse_node -> point[curdim] - query[curdim]);
    if(distance_on_curdim <= distance_total && !check_left){
      find_closest(traverse_node -> left, current_closest, query, (curdim + 1)%Dim);
    }else if(distance_on_curdim <= distance_total && check_left){
      find_closest(traverse_node -> right, current_closest, query, (curdim + 1)%Dim);
    }
}