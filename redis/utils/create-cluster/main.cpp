#include <iostream>
#include "createcluster.h"

using namespace std;

int main(){
  clusterSpec s1 = {
    30000,
    2000,
    6,
    1,
    "127.0.0.1"
  };
  startCluster(s1);
  cout << "Worked till here!!!" <<endl;
  createCluster(s1);
  stopCluster(s1);
  cleanCluster();
  return 0;
}
