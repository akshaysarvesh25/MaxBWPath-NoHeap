#include<stdlib.h>
#include <iostream>
#include<vector>
#include <cmath>
#include <math.h>
#include <string.h>
#include <time.h>
#include <random>
#include<algorithm>
#include <sys/time.h>

using namespace std;

#define OUTPUT_LOG 0


template <class T>
class Heap{

  private:
    std::vector<T> H;
    std::vector<T> EdgeWeight;
    T *tail;

    std::vector<T> Swap(std::vector<T> H_,int x,int y)
    {
      T temp = H_[x];
      H_[x] = H_[y];
      H_[y] = temp;


      return H_;
    }

    bool MakeHeap_Parent(std::vector<T> weight_MP, std::vector<T> H_,int n)
    {
      //cout<<"Index : "<<" : "<<(n-1)/2<<endl;
      unsigned int Parent_idx = (double)(n-1)/2;
      //cout<<"Parent_idx : "<<Parent_idx<<endl;
      if(weight_MP[n]<=weight_MP[Parent_idx])
      {
        return true;

      }

      else
      {
        std::vector<T> H1 = Swap(H_,n,Parent_idx);
        H = H1;
        int TempPos = position[H_[n]];
        position[H_[n]] = position[H_[Parent_idx]];
        position[H_[Parent_idx]] = TempPos;
        std::vector<T> weight_MP_1 = Swap(weight_MP,n,Parent_idx);
        EdgeWeight = weight_MP_1;
        return MakeHeap_Parent(weight_MP_1,H1,Parent_idx);
      }

    }

    bool MakeHeap_Child(std::vector<T> weight11,std::vector<T> H11,int i)
    {
      if((2*i)+1>(H11.size()-1))
      {
        return true;
      }

      if(weight11[((2*i)+1)]>=weight11[((2*i)+2)])
      {
        if(weight11[i]>=weight11[((2*i)+2)])
        {
          return true;
        }
        else
        {
          H = Swap(H11,i,((2*i)+1));
          int TempPos = position[H[i]];
          position[H[i]] = position[H[(2*i)+1]];
          position[H[(2*i)+1]] = TempPos;
          EdgeWeight = Swap(weight11,i,((2*i)+1));
          return MakeHeap_Child(EdgeWeight,H,((2*i)+1));
        }
      }
      else
      {
        if(weight11[i]>=weight11[((2*i)+2)])
        {
          return true;
        }

        else
        {
          H = Swap(H11,i,((2*i)+2));
          int TempPos = position[H[i]];
          position[H[i]] = position[H[(2*i)+1]];
          position[H[(2*i)+1]] = TempPos;
          EdgeWeight = Swap(weight11,i,((2*i)+2));
          return MakeHeap_Child(EdgeWeight,H,((2*i)+2));
        }
      }
    }

  public:
    /* Position of the element in the heap */
    int position[5000];

    bool Insert(T value,T weight)
    {
      if(H.size() == 0)
      {
        H.push_back(value);
        EdgeWeight.push_back(weight);
        position[value] = H.size()-1;
        //cout<<"Added an element, H.size() is : "<<H.size()<<endl;
        return true;
      }

      else
      {
        //cout<<"size : "<<H.size()<<endl;
        H.push_back(value);
        EdgeWeight.push_back(weight);

        position[value] = H.size()-1;
        //cout<<"Adding element to heap"<<endl;
        //cout<<"H.size() : "<<H.size()<<endl;
        return MakeHeap_Parent(EdgeWeight,H,(H.size()-1));

      }
    }

    void print()
    {
      #if OUTPUT_LOG
      std::cout << "\033[1;33mContents of the heap : \033[0m"<<std::endl;
      for(unsigned int i = 0;i<H.size();i++)
      {
        std::cout<<H[i]<<" "<<EdgeWeight[i]<<std::endl;
      }
      std::cout << "\033[1;33mEnd of heap\033[0m"<<std::endl;
      #endif
    }

    T MaxEdge()
    {
      return H[0];
    }

    T MaxWeight()
    {
      return EdgeWeight[0];
    }


    bool Delete(T index)
    {
      if(H.size() == 0)
      {
        cout<<"Nothing to delete"<<endl;
        return false;
      }

      else if(H.size()==1)
      {
        cout<<"Deleting the last element in the tree.."<<endl;
        H.erase(H.end()-1);
        EdgeWeight.erase(EdgeWeight.end()-1);
        return true;

      }

      else
      {
        int TempPos1 = position[H[index]];
        position[H[index]] = -1;
        H[index] = H[H.size()-1];
        position[H[H.size()-1]] = TempPos1;
        EdgeWeight[index] = EdgeWeight[EdgeWeight.size()-1];
        H.erase(H.end()-1);
        EdgeWeight.erase(EdgeWeight.end()-1);
        unsigned int P_idx = (double)(index-1)/2;

        if(EdgeWeight[index]>=EdgeWeight[P_idx])
        {
          return MakeHeap_Parent(EdgeWeight,H,index);
        }
        else if((EdgeWeight[index]<=EdgeWeight[(2*index)+1])||(EdgeWeight[index]<=EdgeWeight[(2*index)+2]))
        {
          return MakeHeap_Child(EdgeWeight,H,index);
        }
      }

    }

    int SizeOfHeapIsZero()
    {
      return H.size();
    }



};


template<class T>
class VecArray
{
private:
  std::vector<T> NodeName;
  std::vector<T> NodeWeight;

  void print(const std::vector<int> &vec)
  {
    for (const auto& i: vec)
    std::cout << i << ' ';
    std::cout << std::endl;
  }

public:
  bool Insert(T val,T wt)
  {
    NodeName.push_back(val);
    NodeWeight.push_back(wt);
  }

  bool Delete(T val)
  {
    /* Find the position of val in the array */
    std::vector<int>::iterator it = std::find(NodeName.begin(), NodeName.end(), val);
    int index = std::distance(NodeName.begin(), it);
    /* Erase the Node from NodeName */
    NodeName.erase( std::remove( NodeName.begin(), NodeName.end(), val ), NodeName.end() );
    /* Erase the Node from Nodeweight */
    NodeWeight.erase( std::remove( NodeWeight.begin(), NodeWeight.end(), NodeWeight[index] ), NodeWeight.end() );
  }

  T MaxEdge()
  {
    std::vector<int>::iterator result = std::max_element(NodeWeight.begin(),NodeWeight.end());
    int index = std::distance(NodeWeight.begin(), result);
    return NodeName[index];
  }

  T MaxWeight()
  {
    std::vector<int>::iterator result = std::max_element(NodeWeight.begin(),NodeWeight.end());
    return *result;
  }

  void print()
  {
    #if OUTPUT_LOG
    std::cout << "\033[1;33mContents of the array : \033[0m"<<std::endl;
    print(NodeName);
    print(NodeWeight);
    std::cout << "\033[1;33mEnd of heap\033[0m"<<std::endl;
    #endif
  }

  int SizeOfArrayIsZero()
  {
    return NodeName.size();
  }

};

#define NUMBER_OF_VERTICES 5000
#define NUMBER_OF_EDGES_PER_VERTEX_AVG 6
#define PERCENTAGE_VERTICES_NEIGHBORS 1000

#define INSERT_DEBUG_OUTPUT 0
#define DISPLAY_DEBUG_OUTPUT 1

using namespace std;

typedef enum
{
  STATUS_NONE = 0,
  STATUS_GRAPH_UNSEEN = 1,
  STATUS_GRAPH_FRINGE = 2,
  STATUS_GRAPH_INTREE = 3,
}NODE_STATUS;


typedef struct
{
  unsigned int NodeName;
  unsigned int NodeWeight;
}NodeAttributes;

template <class T>
struct SingleLinkedListNode{
  T data;
  T weight;
  NODE_STATUS NodeStatus;
  T Bandwidth;
  T dad;
  SingleLinkedListNode *NextNode;

  SingleLinkedListNode(){


  }

  SingleLinkedListNode(T val){

    this->data = val;
  }

  SingleLinkedListNode(T val,SingleLinkedListNode<T> NewNode){

    this->data = val;
    this->NextNode = NewNode;
  }


};




template <class T>
class LinkedList{

  private:
    SingleLinkedListNode<T> *root, *tail;

  public:
    void insert(T val,T EdgeWeight)
    {

      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode->data=val;
      tempNode->weight = EdgeWeight;
      tempNode->NodeStatus = STATUS_NONE;
      tempNode->NextNode=NULL;

      if(root)
      {
        #if INSERT_DEBUG_OUTPUT
        cout<<"Adding new elements "<<endl;
        #endif
        tail->NextNode=tempNode;
        tail=tempNode;
      }
      else
      {
        root=tempNode;
        tail=tempNode;
        tempNode=NULL;
        #if INSERT_DEBUG_OUTPUT
        cout<<"New root added : "<<val<<endl;
        #endif
      }

    }

    void display()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int i=0;
      //cout<<"\n"<<endl;
      while(tempNode!=NULL)
      {
        cout<<tempNode->data<<" -> ";
        tempNode=tempNode->NextNode;
      }
      cout<<"\n";
    }

    void MakeNodesUnseen()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int i=0;
      //cout<<"\n"<<endl;
        //cout<<tempNode->data<<" -> ";
      tempNode->NodeStatus = STATUS_GRAPH_UNSEEN;
      tempNode=tempNode->NextNode;

    }

    void MakeNodesIntree()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int i=0;
      tempNode->NodeStatus = STATUS_GRAPH_INTREE;
    }

    void MakeNodesFringe()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int i=0;
      tempNode->NodeStatus = STATUS_GRAPH_FRINGE;
    }

    void SetNodeBandwidth(T BWvalue)
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      //cout<<tempNode->data<<" -> ";
      tempNode->Bandwidth = BWvalue;

    }

    std::vector<int> GetAdjacentNodes()
    {
      std::vector<int> temp;
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      #if OUTPUT_LOG
      cout<<"Adjacent nodes : "<<endl;
      #endif
      while(tempNode!=NULL)
      {
        temp.push_back(tempNode->data);
        #if OUTPUT_LOG
        cout<<tempNode->data<<endl;
        #endif
        tempNode=tempNode->NextNode;
      }

      return temp;
    }

    std::vector<int> GetAdjacentNodesWithout(int NodeName)
    {
      std::vector<int> temp;
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      #if OUTPUT_LOG
      cout<<"Adjacent nodes : "<<endl;
      #endif
      while(tempNode!=NULL)
      {
        if(tempNode->data!=NodeName)
        {
          temp.push_back(tempNode->data);
          cout<<tempNode->data<<endl;
        }

        tempNode=tempNode->NextNode;
      }

      return temp;
    }

    std::vector<int> GetAdjacentNodesWeights()
    {
      std::vector<int> temp;
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      while(tempNode!=NULL)
      {
        temp.push_back(tempNode->weight);
        tempNode=tempNode->NextNode;
      }

      return temp;
    }

    void SetDad(int dadval)
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      tempNode->dad = dadval;
    }

    void GetDad()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      #if OUTPUT_LOG
      cout<<"dad of : "<<tempNode->data<<" is : "<<tempNode->dad<<endl;
      #endif
    }

    void ViewNodeStatus()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      #if OUTPUT_LOG
      cout<<"Node status of : "<<tempNode->data<<" is : "<<tempNode->NodeStatus<<"\n";
      cout<<"Node Bandwidth of : "<<tempNode->data<<" is : "<<tempNode->Bandwidth<<"\n";
      #endif
    }

    bool IsNodeUnseen()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      if(tempNode->NodeStatus == STATUS_GRAPH_UNSEEN)
      {
        return true;
      }

      else
      {
        return false;
      }

    }


    bool IsNodeFringe()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      if(tempNode->NodeStatus == STATUS_GRAPH_FRINGE)
      {
        return true;
      }

      else
      {
        return false;
      }

    }

    T GetBandWidth()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      return tempNode->Bandwidth;
    }

    T GetWeightOfAdjNode(T val)
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      while((tempNode!=NULL))
      {
        if(tempNode->data == val)
        {
          return tempNode->weight;
        }
        tempNode=tempNode->NextNode;
      }

      return 99999;
    }

    T GetWeight()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      return tempNode->weight;
    }

    T DisplayDadNodes()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      //cout<<tempNode->dad<<" -> ";
      //tempNode=tempNode->NextNode;

      return tempNode->dad;
    }

};
