#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int main() {
    using ll = int;
    const ll INF = std::numeric_limits<ll>::max();
    int V; std::cout << "Routers: "; if(!(std::cin>>V)||V<=0) return 1;
    std::vector<std::vector<ll>> g(V, std::vector<ll>(V));
    for(int i=0;i<V;++i) for(int j=0;j<V;++j) std::cin>>g[i][j];
    int src; std::cout<<"Source (0.."<<V-1<<"): "; if(!(std::cin>>src)||src<0||src>=V) return 1;

    std::vector<ll> dist(V, INF);
    std::vector<int> parent(V, -1);
    std::vector<bool> used(V,false);
    dist[src]=0;

    for(int it=0; it<V; ++it){
        int u=-1;
        for(int i=0;i<V;++i) if(!used[i] && (u==-1 || dist[i]<dist[u])) u=i;
        if(u==-1 || dist[u]==INF) break;
        used[u]=true;
        for(int v=0; v<V; ++v){
            if(!used[v] && g[u][v] && dist[u]!=INF && dist[u]+g[u][v]<dist[v]){
                dist[v]=dist[u]+g[u][v];
                parent[v]=u;
            }
        }
    }

    std::cout<<"\nFrom "<<src<<"\n";
    for(int i=0;i<V;++i){
        if(i==src) continue;
        if(dist[i]==INF){ std::cout<<src<<" -> "<<i<<": INF (no path)\n"; continue; }
        std::vector<int> path;
        for(int cur=i; cur!=-1; cur=parent[cur]) path.push_back(cur);
        std::reverse(path.begin(), path.end());
        std::cout<<src<<" -> "<<i<<": "<<dist[i]<<"   Path: ";
        for(size_t k=0;k<path.size();++k){ if(k) std::cout<<"->"; std::cout<<path[k]; }
        std::cout<<"\n";
    }
}
