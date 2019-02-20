#include <iostream>

using namespace std;

int arr[1001];
int n;

void getInput()
{
    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
}

int max(int idx, int front, int back)
{
    int max = -999;
    for(int i=idx - 1; i >= idx-front; i--)
    {
        if(max < arr[i]) max = arr[i];
    }
    for(int i=idx + 1; i <= idx + back;i++)
    {
        if(max < arr[i]) max = arr[i];
    }
    //cout << "at" << idx << " max is " << max << endl;
    return max;

}
int solve()
{
    int sum = 0;

    for(int i = 2 ; i < n - 2 ; i++)
    {
        int view = arr[i] - max(i, 2, 2);
        if(view > 0) sum += view;
    }

    return sum;
}

void initGlobal()
{
    for(int i=0;i<n;i++)
        arr[i] = 0;
}

int main()
{
    for(int i=0;i<10;i++)
    {
        getInput();
        cout << solve() << endl;
        initGlobal();
    }
    return 0;
}
