#ifndef CREATECLUSTER_H_INCLUDE
#define CREATECLUSTER_H_INCLUDE

struct  clusterSpec {
    int port; // First Port Number Redis Cluster Master
    int timeout; //Idle Cluster Creation Timeout
    int nodes; // Number of Nodes in a Cluster
    int replicas; // No. of Slaves for each Master
    const char *address; // Addess in Socket Adress to place cluster from
};

char *clusterString(clusterSpec c1, int port);

int startCluster(clusterSpec c1);

int createCluster(clusterSpec c1);

int stopCluster(clusterSpec c1);

int watchCluster(int port);

int cleanCluster();

#endif // CREATECLUSTER_H_INCLUDED
