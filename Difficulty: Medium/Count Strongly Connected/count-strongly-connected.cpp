class Solution {
public:
    
    void dfs1(int v, vector<int> adj[], vector<int>& vis, stack<int>& st) {
        vis[v] = 1;
        for (int u : adj[v]) {
            if (!vis[u]) {
                dfs1(u, adj, vis, st);
            }
        }
        st.push(v);
    }
    
    void dfs2(int v, vector<int> adj[], vector<int>& vis) {
        vis[v] = 1;
        for (int u : adj[v]) {
            if (!vis[u]) {
                dfs2(u, adj, vis);
            }
        }
    }
    
    int kosaraju(int V, vector<vector<int>>& edges) {
        vector<int> adj[V];
        
        // Step 1: Build graph
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
        }
        
        stack<int> st;
        vector<int> vis(V, 0);
        
        // Step 2: Fill stack
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs1(i, adj, vis, st);
            }
        }
        
        // Step 3: Reverse graph
        vector<int> rev[V];
        for (int i = 0; i < V; i++) {
            for (int u : adj[i]) {
                rev[u].push_back(i);
            }
        }
        
        // Step 4: DFS on reversed graph
        fill(vis.begin(), vis.end(), 0);
        int count = 0;
        
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            
            if (!vis[v]) {
                dfs2(v, rev, vis);
                count++;
            }
        }
        
        return count;
    }
};