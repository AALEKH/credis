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
    const char *address; // Addess in Socket Adress to place cluster from
};

char *clusterString(clusterSpec c1, int port){
  string test;
  char *command = new char[4096];
  test = "../../src/redis-server --port ";
  strcat(command, test.c_str());
  strcat(command, to_string(port).c_str());
  test = " --cluster-enabled yes --cluster-config-file nodes-";
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

int startCluster(clusterSpec c1) {
    int EndPort = c1.port + c1.nodes;
    stringstream ss;
    char *command;
    int port = c1.port;
    while (port < EndPort){
      port = port + 1;
      command = clusterString(c1, port);
      system(command);
    }
    free(command);
    return 0;
}

int createCluster(clusterSpec c1) {
  char *host = new char[4096];
  const char *address = c1.address;
  char *command = new char[4096];
  string blank = " ";
  string colon = ":";
  string test = "../../src/redis-trib.rb create --replicas ";
  // strcat(host, address);
  // strcat(host, ":");
  char *socketAddress;
  int EndPort = c1.port + c1.nodes;
  int port = c1.port;
  while(port < EndPort){
    port = port + 1;
    strcat(host, c1.address);
    strcat(host, colon.c_str());
    strcat(host, to_string(port).c_str());
    strcat(host, " ");
  }
  strcat(command, test.c_str());
  strcat(command, to_string(c1.replicas).c_str());
  strcat(command, blank.c_str());
  strcat(command, host);
  system(command);
  free(command);
  return 0;
}

int stopCluster(clusterSpec c1) {
  int EndPort = c1.port + c1.nodes;
  int port = c1.port;
  char *run = new char[4098];
  while (port < EndPort) {
    port = port + 1;
    strcat(run, "../../src/redis-cli -p ");
    strcat(run, to_string(port).c_str());
    strcat(run, " shutdown nosave");
    system(run);
  }
  free(run);
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

/*Example Run \/ \/

 int main(){
   clusterSpec s1 = {
     30032,
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

*/
