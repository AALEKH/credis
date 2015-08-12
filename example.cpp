#include <iostream>
#include <queue>
#include <thread>
#include <assert.h>
#include "createcluster.h"
#include "cpp-hiredis-cluster/include/hirediscommand.h"
#include <boost/functional/hash.hpp>

using namespace RedisCluster;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using namespace std;


int hashCode(char *str)
{
    boost::hash<std::string> string_hash;

    return string_hash(str);
}

void processClusterCommand(const char *address, int port, char *table, char *data)
{
    Cluster<redisContext>::ptr_t cluster_p;
    redisReply * reply;
    int value = 0;
    string command;
    cluster_p = HiredisCommand<>::createCluster( address, port );
    cout << "Bus error 0" << endl;
    while (value < 20) {
      command = "FOO";
      command = command + to_string(value);

      reply = static_cast<redisReply*>( HiredisCommand<>::Command( cluster_p, "FOO", "hset %s %i %s", table, hashCode(data), data));
      if( reply->type == REDIS_REPLY_STATUS  || reply->type == REDIS_REPLY_ERROR )
      {
          cout << " Reply to SET FOO BAR " << endl;
          cout << reply->str << endl;
      }
      value = value + 1;
      freeReplyObject( reply );
    }
    delete cluster_p;
}

int main(){
  int port = 8001;
  clusterSpec s1 = {
    8000,
    2000,
    6,
    1,
    "127.0.0.1"
  };
  startCluster(s1);
  cout << "Worked till here!!!" <<endl;
  createCluster(s1);
  try
  {
    while (port < 8005) {
      /* code */
      processClusterCommand("127.0.0.1", port, "hsh", "sup data");
      port = port + 1;
    }
  } catch ( const RedisCluster::ClusterException &e )
  {
      cout << "Cluster exception: " << e.what() << endl;
  }
  return 0;
}
