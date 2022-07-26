struct Dijkstra{
      vector<int> val;
      Dijkstra(int s, int n){
            val = vector<int>(n, 1e9);
            val[s] = 0;
            vector<bool>vis(n, false);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> >Q;
            Q.push({0, s});
            while(!Q.empty()){
                  int x = Q.top().second;
                  Q.pop();
                  if(vis[x])continue;
                  vis[x] = true;
                  for(int i = 0; i < adj[x].size(); i++){
                        int y = adj[x][i].first, z = adj[x][i].second;
                        if(vis[y] || val[y] < val[x] + z)continue;
                        val[y] = val[x] + z;
                        Q.push({val[y], y});
                  }
            }
      }
};
