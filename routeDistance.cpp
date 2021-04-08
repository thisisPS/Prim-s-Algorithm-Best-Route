#include<iostream>
#include <fstream>

using namespace std;

struct node{
  int vertex;
  int weight;
  struct node* next;
};

struct MST{
  int from;
  int weight;
  int vertexName;
};



void create_graph(struct node *Adj[], int n){
  string places[n], chumma;
  int theDistance[n][n];
  struct node *newnode, *last;
  int neighbours=0, value, weight;

  fstream my_file;
	my_file.open("places.txt", ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
    my_file>>chumma;
    for(int i=0;i<n;i++){
      my_file>>places[i];
    }

    for(int i=0;i<n;i++){
      my_file>>chumma;
      for(int j=0;j<n;j++){
        my_file>>theDistance[i][j];
      }
    }

	}
	my_file.close();


  for(int i=0;i<n;i++){
    last = NULL;
    for(int j=0;j<n;j++){
      if(theDistance[i][j]!=-1){
        newnode = (struct node *)malloc(sizeof(struct node));
        newnode->vertex = j;
        newnode->weight = theDistance[i][j];
        newnode->next = NULL;
        if(Adj[i] == NULL){
          Adj[i] = newnode;
        }else{
          last->next = newnode;
        }
        last = newnode;
      }
    }
  }

}

void display_graph(struct node *Adj[], int n){
  struct node *ptr;
  for(int i=0;i<n;i++){
    ptr = Adj[i];
    cout<<"\nThe Neighbours of Node "<<i<<" are : ";
    while(ptr!=NULL){
      cout<<ptr->vertex<<"\t";
      ptr = ptr->next;
    }
  }
}

int getNoOfPlaces(){
  fstream my_file;
  int count = 0;
  string line;
  my_file.open("places.txt", ios::in);
  if (!my_file) {
    cout << "No such file";
  }
  else {
    while (getline(my_file, line))
       count++;
  }
  my_file.close();
  return count-1;
}

int main(){
  int n;

  n = getNoOfPlaces();
  struct node *Adj[n];
  for(int i=0;i<n;i++){
    Adj[i] = NULL;
  }
  create_graph(Adj, n);
 //display_graph(Adj,n);
  MST mst[n];
  int addedToMST[n];

  for(int i=0;i<n;i++){
    if(i==0){
      addedToMST[i] = 1;
    }else{
      addedToMST[i] = 0;
    }
  }

  for(int i=0;i<n;i++){
    mst[i].from = -1;
    mst[i].weight = -1;
    if(i==0){
      mst[i].vertexName = 0;
    }else{
      mst[i].vertexName = -1;
    }
  }

  struct node *ptr;
  int tempFrom, tempName, tempWeight, checkWeight, weight, smallestWeight= 100, index = 1;

  while(mst[n-1].vertexName==-1){
    smallestWeight = 100;
    for(int i=0;i<n;i++){
      if(mst[i].vertexName==-1){
        break;
      }
      ptr = Adj[mst[i].vertexName];
      while(ptr!=NULL){
        if(addedToMST[ptr->vertex]!=1){
          checkWeight = ptr->weight;
          if(checkWeight < smallestWeight){
            tempFrom = mst[i].vertexName;
            tempName = ptr->vertex;
            tempWeight = ptr->weight;
            smallestWeight = tempWeight;
      //      cout<<"\n"<<tempFrom<<"\t"<<tempName<<"\t"<<smallestWeight<<"\n";
          }
        }
        ptr =  ptr->next;
      }
    }
    mst[index].vertexName = tempName;
    mst[index].from = tempFrom;
    mst[index].weight = tempWeight;
    addedToMST[tempName] = 1;
    index++;
  }
  cout<<"\n";
  string finalPlaces[n], just;
  fstream my_file;
  my_file.open("places.txt", ios::in);
  if (!my_file) {
    cout << "No such file";
  }
  else {
    my_file>>just;
    for(int i=0;i<n;i++){
      my_file>>finalPlaces[i];
    }
  }
  my_file.close();

  for(int i=1;i<n;i++){
    cout<<"\nFROM "<<finalPlaces[mst[i].from]<<" Travel For "<<mst[i].weight<<" KM & GO TO "<<finalPlaces[mst[i].vertexName];
  }
  return 0;
}
