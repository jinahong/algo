#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define INF 987654321
using namespace std;

struct node {
    int x,y,t;
    
    node(){ }
    node(int _x,int _y,int _t) : x(_x),y(_y),t(_t) { }
    
    bool operator > (const node &n) const{
        return t > n.t;
    }
};

int testcase;
int n,ans;
int map[101][101];
int dist[101][101];

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int bfs(){
    priority_queue<node,vector<node>,greater<node> > pq;
    pq.push(node(0,0,0));
    dist[0][0] = 0;
    
    while(!pq.empty()){
        int x = pq.top().x;
        int y = pq.top().y;
        int t = pq.top().t;
        pq.pop();
        cout << "cur:" << y << "," << x << "," <<  t  << endl;       
        // 목적지에 도달한 경우
        if(x==n-1 && y==n-1){
            break;
        }
        
        // 기존시간보다 큰 경우 제외
        if(dist[x][y] < t) continue;
        
        for(int i=0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if(nx<0 || ny<0 || nx>=n || ny>=n) continue;
            
            if(map[nx][ny] > 0){
                if(dist[nx][ny] > dist[x][y] + map[nx][ny]){
                    pq.push(node(nx,ny,t+map[nx][ny]));
                    dist[nx][ny] = dist[x][y] + map[nx][ny];
                }
            }else{
                if(dist[nx][ny] > dist[x][y]){
                    pq.push(node(nx,ny,t));
                    dist[nx][ny] = dist[x][y];
                }
            }
        }
    }
    
    return dist[n-1][n-1];
}

int main(int argc, const char * argv[]) {
    // cin,cout 속도향상
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL); cout.tie(NULL);
    
    scanf("%d",&testcase);
    for(int tc=1; tc<=testcase; tc++){
        scanf("%d",&n);
        
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                scanf("%1d",&map[i][j]);
                
                dist[i][j] = INF;
            }
        }
        
        printf("#%d %d\n",tc,bfs());
    }
    
    return 0;
}
