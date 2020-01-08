#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  this->box = objects[0]->box;
  BoundingBox b = this->box;
  Eigen::RowVector3d offset = b.max_corner - b.min_corner;
  Eigen::RowVector3d c = b.center();
  std::vector<std::shared_ptr<Object>> l, r;
  int axis;

  // if there is no leaf
  if(num_leaves == 0){
      left = nullptr;
      right = nullptr;
      return ;
  }else if(num_leaves == 1){
      // just one leaf, set it to left pointer
      left = objects[0];
      right = nullptr;
      return;
  }

  for(auto i = 0; i < num_leaves; ++i){
      insert_box_into_box(objects[i]->box, this->box);
  }

  // here is the problem, the equal senario has been ignored...
//  auto max_ = std::max(offset(0), std::max(offset(1), offset(2)));
//  // set axis
//  if(offset(0) == max_){
//      axis = 0;
//  }else if(offset(1) == max_){
//      axis = 1;
//  } else{
//      axis = 2;
//  }

  if(offset(0) >= offset(1) && offset(0) >= offset(2)){
      axis = 0;
  }else if(offset(1) >= offset(0) && offset(1) >= offset(2)){
      axis = 1;
  }else{
      axis = 2;
  }

  for(auto i = 0; i < num_leaves; ++i){
      if(axis == 0){
          if(objects[i]->box.center()(0) <= c(0)){
              l.push_back(objects[i]);
          } else{
              r.push_back(objects[i]);
          }
      }else if (axis == 1){
          if(objects[i]->box.center()(1) <= c(1)){
              l.push_back(objects[i]);
          }else{
              r.push_back(objects[i]);
          }
      }else{
          if(objects[i]->box.center()(2) <= c(2)){
              l.push_back(objects[i]);
          } else{
              r.push_back(objects[i]);
          }
      }

      if((!l.empty()) && (!r.empty())){
          left = * new std::shared_ptr<Object> (new AABBTree(l, a_depth + 1));
          right = * new std::shared_ptr<Object> (new AABBTree(r, a_depth + 1));
      }else if(!l.empty()){
          std::size_t half = l.size() / 2;
          std::vector<std::shared_ptr<Object>> bottom(l.begin(), l.begin() + half);
          std::vector<std::shared_ptr<Object>> top(l.begin() + half, l.end());
          left = * new std::shared_ptr<Object> (new AABBTree(bottom, a_depth + 1));
          right = * new std::shared_ptr<Object> (new AABBTree(top, a_depth + 1));
      }else{
          std::size_t half = r.size() / 2;
          std::vector<std::shared_ptr<Object>> bottom(r.begin(), r.begin() + half);
          std::vector<std::shared_ptr<Object>> top(r.begin() + half, r.end());
          left = * new std::shared_ptr<Object> (new AABBTree(bottom, a_depth + 1));
          right = * new std::shared_ptr<Object> (new AABBTree(top, a_depth + 1));
      }

  }

  ////////////////////////////////////////////////////////////////////////////
}
