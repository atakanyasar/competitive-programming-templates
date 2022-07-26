#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<long double,null_type,less<long double>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

long double eps(long double x){
      static long double next = 1;
      return (next++) * 0.00000001 + x;
}