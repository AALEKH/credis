#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include "createcluster.h"
#include <vector>

using namespace std;

char *clusterString(clusterSpec c1, int port){
  string test;
  char *command = new char[4096];
  test = "cd redis/utils/create-cluster && ../../src/redis-server --port ";
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

// Returns command for Master Id Extraction

char *clusterMasterNodeConnectId(clusterSpec c1 ){
  string test;
  int port = c1.port + 1;
  char *command = new char[4096];
  test = "redis-cli -p ";
  strcat(command, test.c_str());
  strcat(command, to_string(port).c_str());
  test = " cluster nodes | grep master | awk '{print $1}'";
  strcat(command, test.c_str());
  return command;
}

// Returns command for Master Address Extraction
char *clusterMasterNodeConnectAddress(clusterSpec c1 ){
  string test;
  int port = c1.port + 1;
  char *command = new char[4096];
  test = "redis-cli -p ";
  strcat(command, test.c_str());
  strcat(command, to_string(port).c_str());
  test = " cluster nodes | grep master | awk '{print $2}'";
  strcat(command, test.c_str());
  return command;
}

int arrayOfId(char *command) {
    
    vector<char *> arrId;
    FILE* pipe;
    char buffer[2048];
    pipe = popen(command, "r");
    while(!feof(pipe)) {
        if(fgets(buffer, 2048, pipe) != NULL)
            arrId.push_back(buffer);
    }
    pclose(pipe);

    for(int i=0; i< arrId.size(); i++){
        cout << "the elements of array are" << arrId[i] << endl;
    }
    return 0;
}

int arrayOfAddress(char *command){

    vector<char *> arrAddress;
    FILE* pipe;
    char buffer[2048];
    pipe = popen(command, "r");
    while(!feof(pipe)) {
        if(fgets(buffer, 2048, pipe) != NULL)
            arrAddress.push_back(buffer);
    }
    pclose(pipe);

    for(int j=0; j < arrAddress.size(); j++){
        cout << "the elements of array are" << arrAddress[j] << endl;
    }
    return 0;
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
  string yesString = "cd redis/utils/create-cluster && echo yes | ";
  string colon = ":";
  strcat(command, yesString.c_str());
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
    strcat(run, "cd redis/utils/create-cluster && ../../src/redis-cli -p ");
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
  string command_t = "cd redis/utils/create-cluster && ../../src/redis-cli -p ";
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
  system("cd redis/utils/create-cluster && rm -rf *.log");
  system("cd redis/utils/create-cluster && rm -rf appendonly*.aof");
  system("cd redis/utils/create-cluster && rm -rf dump*.rdb");
  system("cd redis/utils/create-cluster && rm -rf nodes*.conf");
  return 0;
}

/*
Example Run \/ \/

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
*/

// Array of Id and Array of Address Extracted
//  int main(){
//     vector<char *> arrIdGlobal;
//     vector<char *> arrAddressGlobal;
//     FILE* pipe;
//     char buffer[2048];
//     clusterSpec s1 = {
//      30000,
//      2000,
//      6,
//      1,
//      "127.0.0.1"
//     };
//     arrayOfId(clusterMasterNodeConnectId(s1));
//     arrayOfId(clusterMasterNodeConnectAddress(s1));
//     return 0;
// }

