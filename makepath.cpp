/*
 https://www.acmicpc.net/problem/14890
 
 basic:

 detail:
 예제를 통해서, 0, n-1번째에도 경사로가 놓일수잇음을 알 수 잇다.
 예제를 통해서 각 한 줄만 검사하지 경사로간에 방향상 겹치는건 신경쓰지 않는다. 

 optimization:
 map을 2배로 늘린다. 그럼 right_search하나로 모두 완료 가능. 

 */
#include <iostream>

using namespace std;

int n;
int arr[101*2][101];
int l;

//row 주어짐 down search
bool right_search(int row)
{
	int i=0;
	bool visited[101] ={0,};

	while(i<n-1)
	{
		if(arr[row][i] == arr[row][i+1])
		{
			i++;
			continue;
		}
		//next is higher than current
		else if((arr[row][i] + 1 == arr[row][i+1]))
		{
			bool stop = false;
			//i번째에 경사로가 놓아질수있다는 것을 확인했기 떄문에, 
			//i-1부터 i-l번째까지 l-1번검사하면됨
			for(int j=1;j<l;j++)
			{
				if(visited[i-j] 	//이미 경사로가 놓여져 있거나
					|| arr[row][i-j] != arr[row][i]) //높이가 다른경우
					stop = true;
			}
			if(!stop)
			{
				for(int j=0;j<l;j++)
				{
					visited[i-j] = true;
				}
			}
			//경사로놓을수없다면 더이상진행할필요없음
			else break;
			i+=1;
		}
		//next is lower than current
		else if(arr[row][i] == arr[row][i+1]+1)
		{
			bool stop = false;
			//i+1번부터 경사로를 놓을 수 있는지 확인
			//i+1번부터 i+l번째까지 l번 검사하면됨
			for(int j=1;j<l;j++)
			{
				if(arr[row][i+j] != arr[row][i+j+1]) 
					stop = true;
			}
			if(!stop && (i+l == n-1 || (i+l<n-1 && arr[row][i+l+1] <= arr[row][i+l])))
			{
				for(int j=1;j<=l;j++)
				{
					visited[i+j] = true;
				}
			}
			//경사로놓을수없다면 더이상진행할필요없음
			else break;
			i+=l;
		}
		else break;
	}
	if(i==n-1) return true;
	else return false;
}
int solve()
{
	int ans = 0;
	for(int i=0;i<n*2;i++)
	{
		//if(down_search(i))
		//	ans++;
		if(right_search(i))
			ans++;
	}
	return ans;
}
int main()
{
	cin >> n >> l;
	for(int i=0;i<n;i++)
		for(int col=0;col<n;col++)
			cin >> arr[i][col];

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			arr[i+n][j] = arr[j][i];

	cout << solve() << endl;
}