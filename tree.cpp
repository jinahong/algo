/*
 https://www.acmicpc.net/problem/16235

 봄: 나무들은 자신의 나이만큼 양분 먹고, 나이++, 나이가 어린 나무부터 양분을 먹는다. 양분 못먹는 나무는 죽
 여름: 봄이 죽은 나무 나이/2만큼이 양분이 됨 
 가을: 나무나이가 5의배수이면 번식, 인접한 8칸이 나이1인 나무생성.
 겨울: 각 땅에 양분추가

 k년도가 지난후 살아있는 나무 개수는?
 */
#include <iostream>
#include <algorithm>
using namespace std;

//각 땅정보가 가져야할 정보들
typedef struct info{
    int live_tree_old[100];
    int dead_tree_old[100];
    int live_tree_cnt;
    int dead_tree_cnt;

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
            cout << j<<" , " << i << " food:" << arr[j][i].food <<" , live_tree_cnt: "<< arr[j][i].live_tree_cnt << endl;
            sort(arr[j][i].live_tree_old, arr[j][i].live_tree_old + arr[j][i].live_tree_cnt);
            for(int a = 0;a < tmp->live_tree_cnt ; a++)
            {
                //나무의 양분소비, 나무 나이증가
                if(tmp->food >= tmp->live_tree_old[a])
                {
                    tmp->food -= tmp->live_tree_old[a];
                    tmp->live_tree_old[a]+=1;
                }
                //a이후의 모든 tree는 dead tree 로 옮겨야함.
                else
                {
                    if(tmp->dead_tree_cnt == 0)
                    {
                    tmp->dead_tree_cnt = tmp->live_tree_cnt - a;
                    tmp->live_tree_cnt = a;
                    cout << "dead:" <<tmp->dead_tree_cnt << " , remain:" << tmp->live_tree_cnt << endl;
                    for(int b = 0;b < tmp->dead_tree_cnt;b++, a++)
                    {
                        tmp->dead_tree_old[b] = tmp->live_tree_old[a];
                        tmp->live_tree_old[a] = 0;
                    }
                    break;
                    }
                    else {cout <<"??????????????????????" << endl;}
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
            if(tmp->dead_tree_cnt > 0)
            {
            for(int a = 0 ; a < tmp->dead_tree_cnt ; a++)
            {
                tmp->food += (tmp->dead_tree_old[a] / 2);
                tmp->dead_tree_old[a] = 0;
            }
            tmp->dead_tree_cnt = 0;
            }
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
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            info* tmp = &arr[j][i];
            for(int a = 0;a < tmp->live_tree_cnt;a++)
            {
                if(tmp->live_tree_old[a] % 5 == 0)
                {
//                    cout << "make tree" << tmp->live_tree_old[a] << endl;
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
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            //나무 추가해 주기
            if(arrForAddTree[j][i] > 0)
            {
                for(int a = 0; a < arrForAddTree[j][i];a++)
                {
                    arr[j][i].live_tree_old[arr[j][i].live_tree_cnt] = 1;
                    arr[j][i].live_tree_cnt+=1;
                }
                //배열초기화
                arrForAddTree[j][i] = 0;
            }
            //정렬
            if(arr[j][i].live_tree_cnt > 0)
             sort(arr[j][i].live_tree_old, arr[j][i].live_tree_old + arr[j][i].live_tree_cnt);
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
            res += arr[j][i].live_tree_cnt;
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
        arr[x-1][y-1].live_tree_old[0] = old;
        arr[x-1][y-1].live_tree_cnt = 1;
    }
    cout << solve(k) << endl;



}
