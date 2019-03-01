/*
https://www.swexpertacademy.com/main/talk/solvingClub/problemView.do?solveclubId=AWgn93MasXEDFATd&contestProbId=AWgqpQV6r8gDFAW0&probBoxId=AWjHoamqT10DFATs+&type=PROBLEM&problemBoxTitle=0228&problemBoxCnt=2

 */
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>


using namespace std;

int num[10];
char colors[10];
int chk[10];

bool isSet(vector<int> vec)
{
    if(vec[0] == vec[1] && vec[1] == vec[2])
        return true;
    else if (vec[0] + 2 == vec[1] + 1 && vec[1] + 1 == vec[2])
        return true;
    else return false;
}
/*
   dfs

    color에 해당하는 색 중 3개를 골라서 set에 해당하는지 확인하는 함수
level: 9개 카드중 color에 해당하는 카드 갯수
cnt: 카드갯수, 3이 max

 */
int search6(int level, int cnt, char color)
{
    //카드 3개 골랐음!
    if(cnt == 3)
    {
        vector<int> vec;
        for(int i=0;i<9;i++)
        {
            if(chk[i] == level && colors[i] == color)
                vec.push_back(num[i]);
        }

        sort(vec.begin(), vec.end());
        //고른 3개가 set이 맞는지 확인
        if(isSet(vec))
        {
            // 계산해야할 카드가 더 있음
            if(level > 3)
            {
                return search6(level-3, 0, color);
            }
            else return true;
        }
        else return false;
    }
    //카드 3개 고르는 작업중
    for(int i=0;i<9;i++)
    {
        if(chk[i] == 0 && colors[i] == color)
        {
            chk[i] = level;
            if(search6(level, cnt+1, color)) return true;
            chk[i] = 0;
        }
    }
    return false;
}
/*
 set만들수있으려면 해당 color 를 가지는 카드개수가 3의 배수이어야함.
 3의 배수 카드를 가지는 경우에만 search 함. 
 */
int makeset(char color)
{
    //search함수를 위한 init
    for(int i=0;i<9;i++)
        chk[i] = 0;

    int cnt=0;
    for(int i = 0 ; i <9;i++)
    {
        if(colors[i] == color)
            cnt++;
    }
    if(cnt % 3 == 0 && search6(cnt, 0, color))
        return cnt;
    else return 0;
}

string solve()
{
    int r = makeset('R');
    int g = makeset('G');
    int b = makeset('B');
    if(r + g + b == 9) return "Win";
    else return "Continue";
}

int main()
{
    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        char wp;
        for(int i=0;i<9;i++)
            scanf("%1d", &num[i]);
        scanf("%1c", &wp);

        for(int i=0;i<9;i++)
            scanf("%1c", &colors[i]);
        scanf("%1c", &wp);

        cout << "#" << i+1 << " " << solve() << endl;
    }
}
