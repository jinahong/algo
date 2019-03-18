/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWgv9va6HnkDFAW0

   dfs시 visited를 18로 잡고, cardA에 해당하는 카드는 visited로 체크한 후, cardB에 해당하는 카드들만 dfs수행. 시간초과됨..
   ㅂㄷㅂㄷ, 어짜피 visited에서 걸러져서 for문 body실행도 안하지만,
   for문 자체를 적게도는 것이 이로움...

 */
#include <iostream>
#include <set>
using namespace std;
int cardA[10];
int cardB[10];
bool visited[10];
int win;
int lose;

void solve(int round, int score)
{
    if(round == 9)
    {
        if(score>0) win++;
        else if(score<0)lose++;
        return;
    }

    //9번만 iteration
    for(int j=0;j<9;j++)
    {
        if(!visited[j])
        {
            visited[j] = true;
            if(cardA[j] > cardB[round])
                solve(round+1, score + cardA[j] + cardB[round]);
            else
                solve(round+1, score - cardA[j] - cardB[round]);
            visited[j] = false;
        }
    }
}

int main()
{
    int tc_cnt;
    cin >> tc_cnt;

    set<int> s;

    for(int tc = 1; tc <= tc_cnt;tc++)
    {
        memset(visited, 0, sizeof(visited));

        for(int i=0;i<9;i++)
        {
            cin >> cardB[i];
            s.insert(cardB[i]);
        }
        for(int i=1, cnt = 0;i<=18;i++)
        {
            if(s.find(i) == s.end()) cardA[cnt++] = i;
        }
        s.clear();
        win =0;lose = 0;

        solve(0, 0);
        cout<< "#" << tc << " "<< lose << " " << win << endl; 
    }


}
