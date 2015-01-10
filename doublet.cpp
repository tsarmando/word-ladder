#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include<string.h>
#include <queue>
using namespace std;

//A graph is defined by G = (V, E, f)
//V is a set of vertices, E set of edges, 
//f a mapping of edges to vertex pairings
class doubletGraph{
	public:
	vector<string> vertex;
	map<string, int> lookup;//works
	int wordLen;
	int size;
	doubletGraph(char w[][32], int length, int n); //works
	int isSingle(string a, string b); //works
	queue<int> nbhd(int u); //
	bool isDoublet(string begin, string end);
};

doubletGraph::doubletGraph(char w[][32],int length, int n){
	int k = 0;
	for(int i = 0; i < n; i++ ){
		if( (int) strlen(w[i]) == length){
			vertex.push_back(w[i]);
			lookup[w[i]] = k;
			k++;
	}
	}
	wordLen = length;	
	size = k;
}

//Check if words differ by single character
int doubletGraph::isSingle(string a, string b){
	if( a.substr(1).compare(b.substr(1)) == 0){
		return 1;
	}
	for(int i =1; i < (int) a.length()-1; i++){
		string c[4] = {a.substr(0,i), a.substr(i+1), 
					   b.substr(0,i), b.substr(i+1)};
		if(c[0].compare(c[2]) == 0 && c[1].compare(c[3]) == 0)	
			return 1;
		}
	if( a.substr(0, a.length()-1).compare(b.substr(0, b.length()-1)) == 0) 
		return 1;
	return 0;
}


queue<int> doubletGraph::nbhd(int u){
	//a neighbourhood of a vector is the set of edges touching the vertex
	//every vertex has a neighbourhood
	queue<int> neighbours;
	for(int i = 0; i<size; i++){
		if(i != u && isSingle(vertex[u], vertex[i]) == 1){
			neighbours.push(i);
		}	
	}
	return neighbours;
}

bool doubletGraph::isDoublet(string begin, string end){
	int start = lookup[begin];
	int ending = lookup[end];
	map<int, int> marked; //denotes visited points
	marked[start] = 1;
	queue<int> pts = nbhd(start);
	
	while( !pts.empty() ){
	//Check if we touched the end

		if(pts.front() == ending)
			return true;
		else{
		//have not found end point. mark current. add all neighbours not already marked.
			marked[pts.front()] = 1;
			queue<int> tmp = nbhd(pts.front());
				while( !tmp.empty() ){
					if( marked.count( tmp.front() ) == 0)
						pts.push(tmp.front());
					tmp.pop();
				}
			pts.pop();
			}
		
	}
	return false;
}

int readWordsFromFile(char words[100000][32], const char file[])
{
    int i = 0;
    FILE *fp = fopen(file, "r");
    
    while(1)
    {
        fscanf(fp, "%s", words[i++]);       
        if(feof(fp))  break;
    }
    fclose(fp);
    return i;
}

int main(){
	static char words[100000][32];
	int  nWords = readWordsFromFile(words, "wordlist.txt");
	doubletGraph a = doubletGraph(words,3,nWords);
	if(a.isDoublet(a.vertex[a.lookup["ape"]], a.vertex[a.lookup["man"]]))
		cout << a.vertex[a.lookup["ape"]]<< " is a doublet of " << a.vertex[a.lookup["man"]] << endl;
	else
		cout << a.vertex[a.lookup["ape"]] << " is not a doublet of " <<a.vertex[a.lookup["man"]] << endl;

	return 0;
}
