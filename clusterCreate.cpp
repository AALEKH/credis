#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

using namespace std;

struct  clusterSpec {
    int port; // First Port Number Redis Cluster Master
    int timeout; //Idle Cluster Creation Timeout
    int nodes; // Number of Nodes in a Cluster
    int replicas; // No. of Slaves for each Master
    int address; // Addess in Socket Adress to place cluster from
};

char *clusterString(clusterSpec c1, int port){
  string test;
  char *command;
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

int main(){

cout << "Hello" <<endl;
return 0;
}

int startCluster(clusterSpec c1) {
    int EndPort = c1.port + c1.nodes;
    stringstream ss;
    char *command;
    // std::string test;
    int port = c1.port;
    while (port < EndPort){
      cout << "Starting Ports" << endl;
      port = port + 1;
      command = clusterString(c1, port);
      // command = to_string(ss);
      system(command);
    }
    return 0;
}

int createCluster(clusterSpec c1) {
  char *host = "";
  const char *address = to_string(c1.address).c_str();
  strcat(host, address);
  strcat(host, ":");
  char *socketAddress;
  int EndPort = c1.port + c1.nodes;
  int port = c1.port;
  while(port < EndPort){
    port = port + 1;
    strcat(host, to_string(port).c_str());
    strcat(host, " ");
  }
  system(host);
  return 0;
}

int stopCluster(clusterSpec c1) {
  int EndPort = c1.port + c1.nodes;
  int port = c1.port;
  char *run;
  while (port < EndPort) {
    port = port + 1;
    cout << " Stopping " << to_string(port) << endl;
    strcat(run, "../../src/redis-cli -p ");
    strcat(run, to_string(port).c_str());
    strcat(run, " shutdown nosave");
    system(run);
  }
  return 0;
}

int watchCluster(int port) {
  port = port + 1;
  char *command;
  string command_t = "../../src/redis-cli -p ";
  strcat(command, command_t.c_str());
  strcat(command, to_string(port).c_str());
  command_t = " cluster nodes | head -30";
  strcat(command, command_t.c_str());
  while (1) {
    /* code */
    system(command);
    usleep(2000);
  }

  return 0;
}

int cleanCluster() {
  system("rm -rf *.log");
  system("rm -rf appendonly*.aof");
  system("rm -rf dump*.rdb");
  system("rm -rf nodes*.conf");

  return 0;
}
