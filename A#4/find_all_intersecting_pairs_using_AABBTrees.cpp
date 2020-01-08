#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
#include "MeshTriangle.h"
// Hint: use a list as a queue
#include <list>

typedef std::pair<AABBTree *, AABBTree *> pi;

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  std::list<pi> que;
  if(box_box_intersect(rootA->box, rootB->box)){
      que.emplace_back(rootA.get(), rootB.get());
  }

  while (!que.empty()){
      AABBTree* t_a = que.front().first;
      AABBTree* t_b = que.front().second;
      que.pop_front();

      // if they both have exact one leaf.
      if(t_a->num_leaves == 1 && t_b->num_leaves == 1){
          leaf_pairs.emplace_back(t_a->left, t_b->left);
      }else if(t_a->num_leaves == 1){  // tree A has exact one leaf
          if(box_box_intersect(t_a->box, t_b->left->box)){
              que.emplace_back(t_a, dynamic_cast<AABBTree*>(t_b->left.get()));
          }
          if(box_box_intersect(t_a->box, t_b->right->box)){
              que.emplace_back(t_a, dynamic_cast<AABBTree*>(t_b->right.get()));
          }
      }else if(t_b->num_leaves == 1){
          if(box_box_intersect(t_b->box, t_a->left->box)){
              que.emplace_back(dynamic_cast<AABBTree*>(t_a->left.get()), t_b);
          }
          if(box_box_intersect(t_b->box, t_a->right->box)){
              que.emplace_back(dynamic_cast<AABBTree*>(t_a->right.get()), t_b);
          }
      } else{
          if(box_box_intersect(t_a->left->box, t_b->left->box)){
              que.emplace_back(dynamic_cast<AABBTree *>(t_a->left.get()), dynamic_cast<AABBTree *>(t_b->left.get()));
          }
          if(box_box_intersect(t_a->left->box, t_b->right->box)){
              que.emplace_back(dynamic_cast<AABBTree *>(t_a->left.get()), dynamic_cast<AABBTree *>(t_b->right.get()));
          }
          if(box_box_intersect(t_a->right->box, t_b->left->box)){
              que.emplace_back(dynamic_cast<AABBTree *>(t_a->right.get()), dynamic_cast<AABBTree *>(t_b->left.get()));
          }
          if(box_box_intersect(t_a->right->box, t_b->right->box)){
              que.emplace_back(dynamic_cast<AABBTree *>(t_a->right.get()), dynamic_cast<AABBTree *>(t_b->right.get()));
          }
      }

  }

  ////////////////////////////////////////////////////////////////////////////
}
