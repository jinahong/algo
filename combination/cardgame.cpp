/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWgv9va6HnkDFAW0

basic: 
    9개의 카드중 9개를 선택하며, 카드의 순서가 중요한 permutation

    9!이면 연산량 개많다. 
        dfs시 visited를 18로 잡고, cardA에 해당하는 카드는 visited로 체크한 후, 
         cardB에 해당하는 카드들만 dfs수행. 시간초과됨..
         어짜피 visited에서 걸러져서 for문 body실행도 안하지만,
         for문 자체를 적게도는 것이 이로움...

- detail:
    이미 총합계는 정해져 있음.  1+2+...+17+18.
    그러므로 둘중 절반이상가진 사람이 먼저 나오면, 그사람이 이긴거. 


 */
#include <iostream>
#include <set>

using namespace std;

int cardA[10];
int cardB[10];
bool visited[10];
int win;
int lose;
int sum;

void solve(int round, int score)
{
    if(round == 9)
    {
        if(score>0) win++;
        else if(score<0)lose++;
        return;
    }
    if(score > sum/2) 
    {
        win++; return;
    }
    if(score * -1 > sum/2)
    {
        lose++; return;
    }

    //9번만 iteration
    //9개를 모두 선택해야하는 dfs이므로, 항상 0부터 시작하는 for문
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
void init()
{
    memset(visited, 0, sizeof(visited));
    win =0; lose = 0;
}

int main()
{
    int tc_cnt;
    cin >> tc_cnt;

    set<int> s;
    sum = for(int i=1;i<=18;i++) sum+=i;

    for(int tc = 1; tc <= tc_cnt;tc++)
    {
        init();
        s.clear();


        for(int i=0;i<9;i++)
        {
            cin >> cardB[i];
            s.insert(cardB[i]);
        }
        for(int i=1, cnt = 0 ; i<=18 ; i++)
        {
            if(s.find(i) == s.end()) cardA[cnt++] = i;
        }
        solve(0, 0, 0);

        cout<< "#" << tc << " "<< lose << " " << win << endl; 
    }


}
