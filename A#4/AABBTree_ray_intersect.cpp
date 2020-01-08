#include "AABBTree.h"
#include <list>

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = 0;
  double current_t = 0;

  std::list<std::shared_ptr<Object>> obj_list;
  std::shared_ptr<Object> r_ptr = std::make_shared<AABBTree> (*this);
  obj_list.push_front(r_ptr);

  // if there is element in the list
  while (!obj_list.empty()){
      AABBTree* tree_ptr = dynamic_cast<AABBTree*>(obj_list.front().get());
      obj_list.pop_front();

      bool check_hit = tree_ptr->left->ray_intersect(ray, min_t, max_t, current_t, descendant);
      if((tree_ptr->num_leaves <= 1) && (tree_ptr->left != nullptr) && (check_hit)){
          t = current_t;
          descendant = tree_ptr->left;
          return true;
      }else if(ray_intersect_box(ray, tree_ptr->box, min_t, t)){
          if(tree_ptr->left != nullptr){
              obj_list.push_front(tree_ptr->left);
          }
          if(tree_ptr->right != nullptr){
              obj_list.push_front(tree_ptr->right);
          }
      }
  }
  return false;

  ////////////////////////////////////////////////////////////////////////////
}

