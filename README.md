# credis
Credis stands for Cluster Redis, build to provide cluster support over hiredis.

This code suport is meant to provide easy creation of master slave Redis Nodes

```c++
struct  clusterSpec {
    int port; // First Port Number Redis Cluster Master
    int timeout; //Idle Cluster Creation Timeout
    int nodes; // Number of Nodes in a Cluster
    int replicas; // No. of Slaves for each Master
    const char *address; // Addess in Socket Adress to place cluster from
};
```

To compile example.cpp use:
```shell
1) g++ example.cpp createCluster.cpp -o run
2) ./run
Additional Note:=>  add -std=c++11 and dont forget to use -lhiredis and -levent flags, with g++
```

Header File to Include is:
```c++
#include "createcluster.h"
```
### Order Of Execution Of Function:

1) startCluster(); </br>
2) createCluster(); </br>
3) stopCluster(s1); </br>
4) cleanCluster();

Currently this cluster creation code, is tested with cpp-hiredis-cluster [https://github.com/shinberg/cpp-hiredis-cluster] , more test and implementations are welcome.
