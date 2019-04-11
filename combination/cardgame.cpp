/*
https://www.swexpertacademy.com/main/talk/solvingClub/problemView.do?solveclubId=AWgn93MasXEDFATd&contestProbId=AV15Khn6AN0CFAYD&probBoxId=AWkz_0kaIEcDFASG&type=PROBLEM&problemBoxTitle=0311&problemBoxCnt=1

## sort
- string도 begin, end 매개변수 가짐 ㅋ
- sort함수 리턴값은 void, parameter는 2개 혹은 3개 받음. 
- iknowmax만들려고 sort함수도 사용

## dfs
- dfs안하려고 했다가 자꾸틀려서 dfs로 품.
-이중 포문 안에있는 dfs라서, pruing필수.


- string <-> int, to_string, stoi 사용
- string <-> char[]
 */
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

int ans;
int iknowmax;

/* arr에서 index idx_a와 idx_b간에 swap한 string을 반환*/
string swap(int idx_a, int idx_b, string arr)
{
    char tmp = arr[idx_a];
    arr[idx_a] = arr[idx_b];
    arr[idx_b] = tmp;
    return arr;
}

//arr에서 1번만 swap한 모든 경우중 최대값 리턴
int getOneSwapMax(string arr)
{
    int ans = -9999;
    for(int i=0;i<arr.size()-1;i++)
    {
        int tmp = stoi(swap(i,i+1, arr));
        if(tmp > ans)
            ans = tmp;
    }
    return ans;
}

bool solve(string arr, int chance)
{

   // pruning: chance번 swap하지 않았지만 이미 max값에 도달
    if(stoi(arr) == iknowmax && chance > 0)
    {
        if(chance % 2 == 0)
            ans = iknowmax;
        else if (chance % 2 == 1)
            ans = getOneSwapMax(arr);
        return true;
    }

    //chance모두 다씀
    if(chance == 0)
    {
        ans = ans < stoi(arr)? stoi(arr) : ans;
        return false;
    }

    for(int i = 0 ; i < arr.size() - 1 ; i++)
    {
        for(int j = i + 1 ; j < arr.size() ; j++)
        {
            //nice pruing
            if(arr[i] < arr[j])
            {
                string cand = swap(i,j,arr);
                if(solve(cand, chance-1))
                    return true;
            }
        }
    }
    return false;
}
//arr를 내림차순으로 정렬했을 때 int값을 반환
//arr를 여러번 swap했을때 최대값을 반환함.
int getMax(string arr)
{
    sort(arr.begin() , arr.end(), greater<char>());
    return stoi(arr);
}

//global variable 초기화
void init(string arr)
{
    iknowmax = getMax(arr);
    ans = stoi(arr);
}

int main()
{
    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        string arr;
        int chance;
        cin >> arr;
        cin >> chance;

        init(arr);

        solve(arr, chance);

        cout << "#" << i+1 << " " << ans << endl;
    }
}

