/**********************************
* Dijkstra's Algorihm
* Maximum Bandwidth path
*
**********************************/
#include<MaxBWPath.h>

using namespace std;
long getMicrotime();

long getMicrotime()
{
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{
  /* Heap to store the graph data */
  Heap<int> *Heap1 = new Heap<int>();
  Heap<int> *Heap2 = new Heap<int>();

  Heap<int> *Heap_test = new Heap<int>();

  VecArray<int> *VecArray1 = new VecArray<int>();

  /* Creating graphs of 5000 nodes as an adjacency list */
  LinkedList<int> *Graph_1 = new LinkedList<int>[NUMBER_OF_VERTICES];
  LinkedList<int> *Graph_2 = new LinkedList<int>[NUMBER_OF_VERTICES];

  LinkedList<int> *Graph_test = new LinkedList<int>[5];
  Graph_test[0].insert(0,99999);
  Graph_test[0].insert(1,20);
  Graph_test[0].insert(2,70);


  Graph_test[1].insert(1,99999);
  Graph_test[1].insert(3,3);
  Graph_test[1].insert(0,20);

  Graph_test[2].insert(2,99999);
  Graph_test[2].insert(0,70);
  Graph_test[2].insert(3,100);

  Graph_test[3].insert(3,99999);
  Graph_test[3].insert(1,3);
  Graph_test[3].insert(2,100);



  for(unsigned int i = 0;i<=3;i++)
  {
  cout<<i<<"->";
  Graph_test[i].display();
  }
  long time1 = getMicrotime();
  srand(time(0));
  /* Construct a cycle of connected nodes */
  for(unsigned int i = 0;i<NUMBER_OF_VERTICES;i++)
  {
    unsigned int weight_insert = rand()%100;
    if(i==(NUMBER_OF_VERTICES-1))
    {
      Graph_1[i].insert(i,99999);
      Graph_1[i].insert(0,weight_insert);
      continue;
    }
    Graph_1[i].insert(i,99999);
    Graph_1[i].insert(i+1,weight_insert);
  }

  for(unsigned int i = 0;i<NUMBER_OF_VERTICES;i++)
  {
    for(unsigned int NV = 0;NV<(NUMBER_OF_VERTICES);NV++)
    {
      if((rand()%5000)<=6)
      {
        unsigned int weight_insert = rand()%100;
        Graph_1[i].insert(NV,weight_insert);
        Graph_1[NV].insert(i,weight_insert);
      }

    }

  }

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */

  /* Make all nodes of the graph unseen */
  for(unsigned int count = 0;count<NUMBER_OF_VERTICES;count++)
  {
    Graph_1[count].MakeNodesUnseen();
    //cout<<"count is : "<<count<<endl;
  }

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */

  Graph_1[0].MakeNodesIntree();

  Graph_1[0].SetNodeBandwidth(99999);

  int Node_prev = 0;

  std::vector<int> AdjacentNodes = Graph_1[0].GetAdjacentNodes();
  std::vector<int> AdjacentNodeWeights = Graph_1[0].GetAdjacentNodesWeights();
  /*
  if(Heap_test->SizeOfHeapIsZero() == 1)
  {
    cout<<"Heap is null"<<endl;
    cout<<Heap_test->SizeOfHeapIsZero()<<endl;
  }*/

  /*
  Graph_test[0].ViewNodeStatus();
  Graph_test[1].ViewNodeStatus();
  Graph_test[2].ViewNodeStatus();
  */
  for(unsigned int count = 1;count<=(AdjacentNodes.size()-1);count++)
  {

    int AdjNode = (int)AdjacentNodes[count];
    #if OUTPUT_LOG
    cout<<"Nodename : "<<AdjNode<<endl;
    cout<<"Count : "<<count<<endl;
    #endif
    int AdjNodeWeight = (int)AdjacentNodeWeights[count];
    Graph_1[AdjNode].MakeNodesFringe();
    Graph_1[AdjNode].SetDad(0);
    Graph_1[AdjNode].GetDad();
    Graph_1[AdjNode].SetNodeBandwidth(AdjNodeWeight);
    bool b = VecArray1->Insert(AdjNode,AdjNodeWeight);

  }

  cout<<"\n__First stage done__\n"<<endl;

  /* Printing the heap data structure */
  VecArray1->print();
  cout<<"\n\nStarting the algorithm.. \n"<<"_____"<<endl;

  while(VecArray1->SizeOfArrayIsZero()!=0)
  {
    int Node = VecArray1->MaxEdge();
    int weight = VecArray1->MaxWeight();
    #if OUTPUT_LOG
    cout<<"Node and weight : "<<Node<<" "<<weight<<endl;
    #endif
    //cout<<Heap_test->SizeOfHeapIsZero()<<endl;

    VecArray1->Delete(Node);


    #if OUTPUT_LOG
    VecArray1->print();
    #endif
    Graph_1[Node].MakeNodesIntree();
    //cout<<Heap_test->SizeOfHeapIsZero()<<endl;
    //std::vector<int> AdjacentNodes = Graph_test[Node].GetAdjacentNodesWithout(Node_prev);
    std::vector<int> AdjacentNodes = Graph_1[Node].GetAdjacentNodes();//Without(Node_prev);
    std::vector<int> AdjacentNodeWeights = Graph_1[Node].GetAdjacentNodesWeights();//Without(Node_prev);
    Node_prev = Node;

    for(unsigned int count = 1;count<AdjacentNodes.size();count++)
    {
      int AdjNode = (int)AdjacentNodes[count];
      //cout<<"Status of the node "<<AdjNode<<" : "<<endl;
      Graph_1[AdjNode].ViewNodeStatus();

      int AdjNodeBW1 = Graph_1[AdjNode].GetBandWidth();
      int BW_node1 = Graph_1[Node].GetBandWidth();
      int AdjNode_Weight1 = Graph_1[Node].GetWeightOfAdjNode(AdjNode);/* TODO */


      #if OUTPUT_LOG
      cout<<"BW_Adj Node, BW_Node, AdjNode_Weight "<<AdjNodeBW1<<" , "<<BW_node1<<" , "<<AdjNode_Weight1<<endl;
      #endif

      if(Graph_1[AdjNode].IsNodeUnseen() == true)
      {
        #if OUTPUT_LOG
        cout << "\033[1;32mNode unseen  \033[0m"<<AdjNode<<std::endl;
        #endif
        Graph_1[AdjNode].MakeNodesFringe();
        Graph_1[AdjNode].SetDad(Node);
        //int BW_node = Graph_test[Node].GetBandWidth();
        //int AdjNode_Weight = Graph_test[AdjNode].GetWeight();
        #if OUTPUT_LOG
        cout<<"Weight of the adjacent node and bandwidth of the current node : "<<AdjNode_Weight1<<" & "<<BW_node1<<endl;
        #endif
        Graph_1[AdjNode].SetNodeBandwidth(std::min({BW_node1,AdjNode_Weight1}));
        int AdjNodeBW = Graph_1[AdjNode].GetBandWidth();
        VecArray1->Insert(AdjNode,AdjNodeBW);
        VecArray1->print();
      }

      else if((Graph_1[AdjNode].IsNodeFringe() == true)&&(AdjNodeBW1<(std::min({BW_node1,AdjNode_Weight1}))))
      {
        #if OUTPUT_LOG
        cout << "\033[1;32mNode is fringe : \033[0m"<<AdjNode<<std::endl;
        #endif

        VecArray1->Delete(AdjNode);


        VecArray1->print();
        Graph_1[AdjNode].SetDad(Node);
        //ToDo
        Graph_1[AdjNode].SetNodeBandwidth(std::min({BW_node1,AdjNode_Weight1}));
        int AdjNodeBW2 = Graph_1[AdjNode].GetBandWidth();
        VecArray1->Insert(AdjNode,AdjNodeBW2);
        VecArray1->print();

      }

      else
      {
        #if OUTPUT_LOG
        std::cout << "\033[1;31mNot necessary to process Element of heap : \033[0m"<<AdjNode<<std::endl;
        #endif
      }

    }
    #if OUTPUT_LOG
    cout<<"____"<<endl;
    #endif
  }

  int Node_D = 106;
  cout<<Node_D<<"<-";
  while(Graph_1[Node_D].DisplayDadNodes()!=0)
  {
    cout<<Graph_1[Node_D].DisplayDadNodes()<<"<-";
    Node_D=Graph_1[Node_D].DisplayDadNodes();
  }
  cout<<"0"<<endl;



long time2 = getMicrotime();
cout<<"Total execution time : "<<(time2-time1)*1e-6<<endl;






  return 0;
}
