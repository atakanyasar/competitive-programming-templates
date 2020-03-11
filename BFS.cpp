namespace BFS{
      
      void bfs(vector<vector<int> >& adj, vector<int>& val, int s = 1){
            val[s] = 0;
            queue<int> bfs;
            bfs.push(s);
            while(!bfs.empty()){
                  int x = bfs.front();
                  bfs.pop();
                  for(auto y : adj[x]){
                        if(val[y] > val[x] + 1){
                              val[y] = val[x] + 1;
                              bfs.push(y);
                        }
                  }
            }
      }

}