#include <iostream>
#include <set>
#include <string>
using namespace std;
string arr[4][4];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

set<string> string_set;
bool safe(int x, int y)
{
    return (x<4 && y<4 && x>=0 && y>=0);
}

void solve(int x, int y, string s,int cnt)
{
        if(cnt == 7)
        {
            string_set.insert(s);
            return;
        }
        for(int i=0;i<4;i++)
        {
            if(safe(x + dx[i], y + dy[i]))
            {
                solve(x + dx[i], y+dy[i], s + arr[x][y] , cnt+1);
            }
        }
}
void debug()
{
    for(auto it = string_set.begin(); it != string_set.end(); it++){
        cout << *it << " ";
    }
}
int main()
{
    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        for(int a = 0;a<4;a++)
            for(int b=0;b<4;b++)
                cin >> arr[b][a];
        for(int a = 0;a<4;a++)
            for(int b=0;b<4;b++)
                solve(a,b, "" ,0);

        debug();
        cout<<"#" << i+1 << " " <<  string_set.size() << endl;
    }

}
