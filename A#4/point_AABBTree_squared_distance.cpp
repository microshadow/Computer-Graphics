#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

typedef std::pair<double, AABBTree*> pi;
// need to write an operator overloading
class comp{
public:
    bool operator() (const AABBTree* lhs, const AABBTree* rhs) const{
        return lhs->depth > rhs->depth;
    }
};

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  sqrd = 0;

  std::priority_queue<pi, std::vector<pi>, std::greater<pi>> que;
  // get the squared distance;
  double dist = point_box_squared_distance(query, root->box), current_dist = 0, new_dist;
  // push to queue
  que.push(std::make_pair(dist, root.get()));

  while (!que.empty()){
     current_dist = que.top().first;
     AABBTree* current_tree = que.top().second;
     que.pop();
     bool check_squr_dist = current_tree->left->point_squared_distance(query, min_sqrd, sqrd, current_dist, descendant);
     if(current_dist <= sqrd){
         if(current_tree->num_leaves <= 1 && (current_tree->left != nullptr) && (check_squr_dist)){
             sqrd = current_dist;
             descendant = current_tree->left;
             return true;
         }else{
             if(current_tree->left != nullptr){
                 new_dist = point_box_squared_distance(query, current_tree->left->box);
                 que.push(std::make_pair(new_dist, dynamic_cast<AABBTree*>(current_tree->left.get())));
             }
             if(current_tree->right != nullptr){
                 new_dist = point_box_squared_distance(query, current_tree->right->box);
                 que.push(std::make_pair(new_dist, dynamic_cast<AABBTree*>(current_tree->right.get())));
             }
         }

     }
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
