/*
  For personal practice. 
  Original source code comes from ISBN 978-89-6626-054-6
*/

/*
  Bipartite matching with Max Flow.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

const int INF = 987654321;
const int MAX_V = 2002;

// capacity[i][j] = capacity from i to j 
// flow[i][j] = current flow from i to j
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int V; // # of vertices

int NF(int source, int sink)
{
  memset(flow, 0, sizeof(flow));
  int totalFlow = 0;

  while(true) {
    // find an augment path using BFS
    vector<int> parent(MAX_V, -1);
    queue<int> q;
    parent[source] = source;
    q.push(source);
    while(!q.empty() && parent[sink] == -1) {
      int here = q.front(); q.pop();
      for(int there=0;there<V;++there) {
        if(capacity[here][there] - flow[here][there] > 0 &&
           parent[there] == -1) {
          q.push(there);
          parent[there] = here;
        }
      }
      // exit if no augement path.
      if(parent[sink] == -1) break;

      // determine augement flow amount
      int amount =INF;
      for(int p=sink;p != source;p = parent[p]) {
        amount = min(capacity[parent[p]][p]-flow[parent[p]][p]
                     , amount );        
      }
      // add new flow
      for(int p=sink;p != source;p = parent[p]) {
        flow[parent[p]][p] += amount;
        flow[p][parent[p]] -= amount;
      }
      totalFlow += amount;
    }
  }

  return totalFlow;
}


int T,N;
int s[MAX_V];
int d[MAX_V];
int t[MAX_V][MAX_V];

void print_t()
{
  for (int i=0;i<N;i++){
      for (int j=0;j<(N);j++) {
        cout << t[i][j] << " ";
      }
      cout << endl;
  }
}

int main(int argc, char *argv[])
{

  cin >> T;
  for (int test=1; test <= 1; test++) {
    
    cin >> N; V=2*N+2; 
    for (int i=0;i<N;i++) cin >> s[i];
    for (int i=0;i<N;i++) cin >> d[i];
    for (int i=0;i<N;i++) for (int j=i;j<(N);j++) { cin >> t[i][j]; t[j][i] = t[i][j];}

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    
    for (int i=0;i<N;i++)
      for (int j=0;j<(N);j++) {
        if ( s[i] + d[i] + t[i][j] <= s[j] ) {
          capacity[i][N+j] = 1;
          //printf("from %d to %d, %d,%d,%d => %d\n",i,j,s[i],d[i],t[i][j],s[j]);
        }
      }
    // source to A/ B to sink
    for (int i=0;i<N;i++){
      capacity[2*N][i] = 1;
      capacity[N+i][2*N+1] = 1;     
    }
    // # of pairwise independent game
    printf("%d\n",N-NF(2*N, 2*N+1));
    // list
  }
  return 0;
}
