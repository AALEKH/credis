#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct  clusterSpec {
    int port; // First Port Number Redis Cluster Master
    int timeout; //Idle Cluster Creation Timeout
    int nodes; // Number of Nodes in a Cluster
    int replicas; // No. of Slaves for each Master
};

int main(){

cout << "Hello" <<endl;
return 0;
}

int createCluster(clusterSpec c1) {
    int EndPort = c1.port + c1.nodes;
    stringstream ss;
    char *command;
    std::string test;
    int port = c1.port;
    while (port < EndPort){
      cout << "Starting Ports" << endl;
      port = port + 1;
      clusterString(c1, port)
      // command = to_string(ss);
      system(command);
    }
    return 0;
}

char *clusterString(clusterSpec c1, int port){
  test = "../../src/redis-server --port $PORT --cluster-enabled yes --cluster-config-file nodes-";
  strcat(command, test.c_str());
  strcat(command, to_string(port).c_str());
  test = ".conf --cluster-node-timeout ";
  strcat(command, test.c_str());
  strcat(command, to_string(c1.timeout).c_str());
  test = " --appendonly yes --appendfilename appendonly-";
  strcat(command, test.c_str());
  strcat(command, to_string(port).c_str());
  test = ".aof --dbfilename dump-";
  strcat(command, test.c_str());
  strcat(command, to_string(port).c_str());
  test = ".rdb --logfile ";
  strcat(command, test.c_str());
  strcat(command, to_string(port).c_str());
  test = ".log --daemonize yes";
  strcat(command, test.c_str());

  return command;
}
