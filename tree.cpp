/*
https://www.acmicpc.net/problem/16235

봄: 나무들은 자신의 나이만큼 양분 먹고, 나이++, 나이가 어린 나무부터 양분을 먹는다. 양분 못먹는 나무는 죽
여름: 봄이 죽은 나무 나이/2만큼이 양분이 됨 
가을: 나무나이가 5의배수이면 번식, 인접한 8칸이 나이1인 나무생성.
겨울: 각 땅에 양분추가

k년도가 지난후 살아있는 나무 개수는?
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//각 땅정보가 가져야할 정보들
typedef struct info{
    vector<int> live_tree;
    vector<int> dead_tree;
    int food;
} info;

info arr[11][11];
int winter_food[11][11];

int n;// 정사각형의 땅크기, 1~10
int m;// 초기 나무 개수, 1~100
int k;

void spring()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            info* tmp = &arr[j][i];

            //정렬
            sort(tmp->live_tree.begin(), tmp->live_tree.end());

            for(vector<int>::iterator it = tmp->live_tree.begin();
                    it != tmp->live_tree.end();
                    ++it)
            {
                //나무의 양분소비, 나무 나이증가
                if(tmp->food >= *it)
                {
                    tmp->food -= *it;
                    *it += 1;
                }
                //나무 죽음
                else
                {
                    tmp->dead_tree.push_back(*it);
                    tmp->live_tree.erase(it);
                    //위에서 erase해줬기 때문에, idx맞춰주려면 --필요:ㅈ
                    --it;
                }
            }
        }
    }
}
void summer()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            info* tmp = &arr[j][i];

            for(vector<int>::iterator it = tmp->dead_tree.begin();
                    it != tmp->dead_tree.end();
                    ++it)
            {
                tmp->food +=  *it / 2;
            }
            //dead_tree초기화
            tmp->dead_tree.clear();
        }
    }
}
//각 좌표에 새로 추가될 나무의 개수
int arrForAddTree[11][11];

void addTree(int x, int y)
{
    if(x>=0 && y>=0 && x < n && y <n)
    {
        arrForAddTree[x][y]++;
    }
}
void fall()
{
    //새로 생겨날 나무를arrForAddTree에 기록함
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            info* tmp = &arr[j][i];
             for(vector<int>::iterator it = tmp->live_tree.begin();
                    it != tmp->live_tree.end();
                    ++it)
            {
                if( *it % 5 == 0)
                {
                    addTree(j+1,i+1);
                    addTree(j+1,i);
                    addTree(j,i+1);
                    addTree(j-1,i-1);
                    addTree(j-1,i);
                    addTree(j,i-1);
                    addTree(j+1,i-1);
                    addTree(j-1,i+1);
                }
            }
        }
    }
    //arrForAddTree에 있는 정보로 나무들 추가하기. 
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arrForAddTree[j][i] > 0)
            {
                for(int a = 0; a < arrForAddTree[j][i] ; a++)
                {
                    arr[j][i].live_tree.push_back(1);
                }
                //배열초기화
                arrForAddTree[j][i] = 0;
            }
        }
    }

}
void winter()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[j][i].food += winter_food[j][i];
        }
    }
}
int getAns()
{
    int res = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            res += arr[j][i].live_tree.size();
        }
    }
    return res;
}
int solve(int years)
{
    for(int i=0;i<years;i++)
    {
        spring();
        summer();
        fall();
        winter();
    }
    return getAns();
}
int main()
{
    cin >> n >> m >> k;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> winter_food[j][i];

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            arr[j][i].food = 5;

    for(int i=0;i<m;i++)
    {
        int x,y, old;
        cin >> x >> y >> old;
        arr[x-1][y-1].live_tree.push_back(old);
    }
    cout << solve(k) << endl;



}
