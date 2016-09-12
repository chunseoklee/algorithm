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

const int MAX = 1000;

// vertices in A and B
int n,m;

// adj[i][j] = 1 if i and j are adjacent
bool adj[MAX][MAX];

// matching pair
vector<int> aMatch, bMatch;

// dfs visited ?
vector<bool> visited;

bool dfs(int a)
{
  if(visited[a]) { return false; }

  visited[a] = true;

  for (int b = 0; b < m; b++) {
    if (adj[a][b]) {
      if ( aMatch[b] = -1 || dfs(aMatch[b]) ) {
        // found augment path
        aMatch[a] = b;
        //bMatch[b] = a;
        return true;
      }
    }
  }
  
  return false;
}

int bipartiteMatch() {
  aMatch = vector<int>(n,-1);
  bMatch = vector<int>(m,-1);

  int size = 0;
  for (int start=0; start < n; start++) {
    visited = vector<bool>(n, false);
    // find augrment path from start
    if(dfs(start)) {
      ++size;
    }
  }
  return size;
  
}

int T,N;
int s[MAX];
int d[MAX];
int t[MAX][MAX];

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
  for (int test=1; test <= T; test++) {
    
    cin >> N; n=m=N;
    for (int i=0;i<N;i++) cin >> s[i];
    for (int i=0;i<N;i++) cin >> d[i];
    for (int i=0;i<N;i++) for (int j=i;j<(N);j++) { cin >> t[i][j]; t[j][i] = t[i][j];}

    memset(adj,0, sizeof(adj));
    
    for (int i=0;i<N;i++)
      for (int j=0;j<(N);j++) {
        if ( s[i] + d[i] + t[i][j] <= s[j] ) {
          adj[i][j] = true;
          //printf("from %d to %d, %d,%d,%d => %d\n",i,j,s[i],d[i],t[i][j],s[j]);
        }
      }

    // # of pairwise independent game
    printf("%d\n",n-bipartiteMatch());
    // list
    vector<bool> printed = vector<bool>(n,false);
    for (int i=0;i<N;i++) {
      if (printed[i] == false) {
        printed[i] = true;
        cout << i+1 << " ";
        if (aMatch[i] != -1) { printed[aMatch[i]] = true;}
      }
      
    }
    cout << endl;
  }
  return 0;
}
