#include "Factory.h"
#include <iostream>
#include<bits/stdc++.h>

using namespace std;

// A utility function to add an edge in an undirected graph.
void addEdge(map<int,vector<int>> &adjL,int srcNode, int destNode)
{
   adjL[srcNode].push_back(destNode);
   adjL[destNode].push_back(srcNode);
}

// A utility function to print the adjacency list representation of graph
void printGraph(map<int,vector<int>> &adjL)
{
    // prints the elements of graph
    cout << "Adjacency List is ..." << endl;
    for (auto& x: adjL) {
        cout << x.first << ": ";
        for(int j=0;j < x.second.size();j++)
            cout << x.second.at(j) << ' ';
	cout << endl;
    }
}

int main(void)
{
    CommIntf *pCommIntf;
    AER_Msg_t smsg,*rmsg;

    pCommIntf = Factory::Create(MPI);

    smsg.NodeAddr = 0x12345678;
    smsg.LocalUnitAddr = 0xdeadbeef;
    smsg.payload = 7;

#if 0
    pCommIntf->Send_Data(smsg);
    rmsg = pCommIntf->Recv_Data();

    cout << "Received msg is ..." << endl;
    cout << hex << "Node Address = 0x" << rmsg.NodeAddr << endl;
    cout << hex << "LocalUnit Address = 0x" << rmsg.LocalUnitAddr << endl;
    cout << "Payload = " << rmsg.payload << endl;
#endif

    map<int,vector<int>>adjList;
    vector<int>nodes;
    //before adding edges between nodes,for each node determine its neighbors
    //so that we could call addEdge between a node and its neighbors
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 4);
    addEdge(adjList, 1, 2);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 2, 3);
    addEdge(adjList, 3, 4);
    addEdge(adjList, 2, 5);
    addEdge(adjList, 5, 3);
    printGraph(adjList);

    //trigger message sending to nodes group i.e from node 2 to its neighbors 1,3,5
    nodes.push_back(2);
    nodes.push_back(1);
    nodes.push_back(3);
    nodes.push_back(5);
    rmsg = pCommIntf->Bcast_Data(smsg,nodes);

    if(rmsg != NULL) {
	cout << "Received msg is ..." << endl;
        cout << hex << "Node Address = 0x" << rmsg->NodeAddr << endl;
        cout << hex << "LocalUnit Address = 0x" << rmsg->LocalUnitAddr << endl;
        cout << "Payload = " << rmsg->payload << endl;
    }

    if(pCommIntf) {
        delete pCommIntf;
	pCommIntf = nullptr;
    }

    return 0;
}
