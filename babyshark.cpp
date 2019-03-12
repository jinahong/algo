/*
   -좌표 bfs
   개떡같네. 원래 queue만들었던 거 지우고 vector에 좌표 넣는방식으로 바꿈. 
   그후, my sort수행. 

   -조건 확인 제대로 하기

   상어가 지나갈 수 있는 곳: 자기랑 크기가 같은 물고기칸, 혹은 빈칸
   상어가 못지나가는 곳: 자기보다 큰 물고기칸
   상어가 먹을 수 있는 고기: 크기 작은 물고기
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr[21][21];
int visited[21][21];
int dx[4] = {0,-1,1,0};
int dy[4] = {-1,0,0,1};

typedef struct pos{
    int x, y, time;
} pos;

vector<pos> g_v;

int sharkAge = 2;
int ans;
int n;

//returning the position of shark
pos getInput()
{
    pos res;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin >> arr[j][i];
            if(arr[j][i]==9)
            {
                res = (pos){j,i, 0};
                arr[j][i] = 0;//remove shark position
            }
        }
    }
    return res;
}

bool safe(int x, int y)
{
    return (x>=0 && y>=0 && x<n && y<n) && (arr[x][y] == 0 || arr[x][y] <= sharkAge);
}
bool nodup(int x, int y)
{
    for(vector<pos>::iterator it = g_v.begin();it!=g_v.end();++it)
    {
        if(it->x == x && it->y == y)
            return false;
    }
    return true;
}
//cnt가 0이 될때까지 bfs
//무의미하게 가는 방향들이 많음....
void dfs(int cnt, pos shark, int orig_d, pos orig_s)
{
    if(cnt == 0 )
    {
        if(visited[shark.x][shark.y] != 0) return;
        if(!nodup(shark.x, shark.y)) return;
        pos tmp = shark;
        tmp.time += orig_d;
        visited[shark.x][shark.y] = tmp.time;//cnt;
        g_v.push_back(tmp);
        return;
    }

    for(int i=0;i<4;i++)
    {
        int tx = shark.x + dx[i];
        int ty = shark.y + dy[i];

        if(safe(tx, ty) )
            //                && (visited[tx][ty]>=orig_d-cnt dd|| visited[tx][ty] == 0)
            //            && (tx != orig_s.x && ty != orig_s.y))
        {
            //XXX: 변수 선언없이 바로, 구조체를 dfs넣으면 안됨!!!!!!!!!!!!!
            pos tmp_pos = {tx, ty, shark.time};
            dfs(cnt-1, tmp_pos, orig_d, orig_s);
        }
    }

}
//comparison function object (i.e. an object that satisfies the requirements of Compare) which returns ​true if the first argument is less than (i.e. is ordered before) the second. 
bool my_sort(pos& a, pos& b) 
{
    if(a.y < b.y) return true;
    else if(a.y == b.y)
    {
        if(a.x < b.x) return true;
        else return false;
    }
    else
        return false;
}
bool my_unique(pos a, pos b)
{
    if(a.x == b.x && a.y == b.y)
        return true;
    else return false;
}
//shark를 기준으로 distance만큼떨어진 좌표 반환
void push_next_pos(pos shark, int distance)
{
    g_v.clear();
    visited[shark.x][shark.y] = 1;//true;
    dfs(distance, shark, distance, shark);

    sort(g_v.begin(), g_v.end(), my_sort);
    //    g_v.erase( unique(g_v.begin(), g_v.end() , my_unique), g_v.end() );
}



bool isEnd()
{
    for(int i=0;i<n; i++)
        for(int j=0;j<n;j++)
            //먹을수있는 고기 있으면 아직 안끝남. 
            if(sharkAge > arr[j][i] && arr[j][i] > 0)
                return false;
    return true;
}

//sharks vector중에서 상어가 먹을 수 있는 fish찾기
pos searchEableFish(vector<pos> sharks)
{
    //sharks에 고기가 있는지 확인
    for(vector<pos>::iterator it = sharks.begin();it!= sharks.end();++it)
    {
        //1. 해당 위치가 고기인지 확인
        if((arr[it->x][it->y] < sharkAge) && (arr[it->x][it->y] > 0))
            return *it;
    }
    return (pos){-1,-1,-1};
}

void debug(vector<pos> vs)
{
    for(vector<pos>::iterator it = vs.begin();it!=vs.end();++it)
    {
        cout << "(" << it->x <<"," << it->y<<") ,";
    }
    cout << endl;
}


int main()
{
    vector<pos> sharks;
    cin >> n;
    //distance에 있는 shark 좌표를 가짐. 
    pos shark = getInput();
    sharks.push_back(shark);
    int eatenfish = 0;
    int distance = 0;

    while(1)
    {
        pos it = searchEableFish(sharks);
        if(it.x != -1 && it.y != -1 && it.time != -1)
        {
            for(int i=0;i<21;i++)
                for(int j=0;j<21;j++)
                    visited[i][j] = 0;//false;
            //        visited[shark.x][shark.y] = 1;
            //   cout << "eat fish(" << it.x << "," << it.y << ")" << endl;
            arr[it.x][it.y] = 0;
            eatenfish+=1;
            if(eatenfish == sharkAge)
            {
                eatenfish = 0;
                sharkAge += 1;
            }
            ans = it.time;
            distance = 1;
            shark = it;
            sharks.clear();
        }
        else
            distance+=1;

        if(isEnd()) break;
        //3. 다음에 이동할 수 있는 위치 push
        //       cout << "shark(" << shark.x << "," << shark.y <<") distance:" << distance << endl;
        push_next_pos(shark, distance);

        if(equal(g_v.begin(), g_v.end(), sharks.begin(),  my_unique))    
        {
            break;
        }
        sharks = g_v;
        // debug(sharks);
    }
    cout << ans << endl; 
}
