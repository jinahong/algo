/*

   https://www.swexpertacademy.com/main/talk/solvingClub/problemView.do?solveclubId=AWgn93MasXEDFATd&contestProbId=AV141176AIwCFAYD&probBoxId=AWjHoamqT10DFATs+&type=PROBLEM&problemBoxTitle=0228&problemBoxCnt=++2+

1. 입력의 형태가 child가 있는 경우 없는 경우 두가지로 나뉨. 
cin 이 뒤에 newline을 받아들이지 않아서, getline과 함께쓸수가 없다..
   input받는방식을 getline 2개 받는걸로 바꿨따. 

2. data structure: 굳이 tree를 만들필요는 없는것같아서, nodes에 tree의 val만저장. 

3. data type: 입력에 int, char 섞여있어서 그냥 전부다 string으로 처리함. int값(node idx)
가 필요한 경우에만 stoi, atoi함수써서 처리. 

4. ans를 global variable로 써서 개짜증나지만..
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool isOperator(string c);
bool ans;
string nodes[201];

bool isNum(string c)
{
    bool res = isOperator(c);
    return !res;
}

bool isOperator(string c)
{
    if(!c.compare("+") || !c.compare("-") || !c.compare("*") || !c.compare("/")) 
        return true;
    else return false;
}

vector<string> parseInput(string input)
{
    vector<string> res;
    int idx=0;
    //마지막 입력값을 vector에 넣어주려고, size까지 iteration
    for(int i=0;i<=input.size();i++)
    {
        char tmp[10];
        if(input[i] == ' ' || i == input.size())
        {
            tmp[idx] = '\0';
            res.push_back(tmp);
            idx = 0;
        }
        else
        {
            tmp[idx++] = input[i];
        }
    }
    return res;

}
bool makeTree(vector<string> input)
{
    int i = atoi(input[0].c_str());

    //leaf node
    if(input.size() == 2) 
    {
        nodes[i] = input[1];
        if(isOperator(nodes[i])) return false;
    }


    else if (input.size() == 4)
    {
        nodes[i] = input[1];
        if(isNum(nodes[i])) return false;
    }
    return true;
}

bool solve(int N)
{
    vector<string> stack;

    //index문제때문에 segment fault떠서 짜증남.
    for(int i = 1 ; i <= N ; i++)
    {
        //operator는 stack에 push
        if(isOperator(nodes[i]))
        {
            stack.push_back(nodes[i]);
        }
        //top이 operator이고, 숫자가 들어오면 숫자 push
        else if(isNum(nodes[i]) && !isNum(stack.back()) )
        {
            stack.push_back(nodes[i]);
        }

        else if(isNum(nodes[i]) && isNum(stack.back()))
        {
            stack.pop_back();
            if(! isOperator(stack.back()) ) return false;
            stack.pop_back();
            if(!stack.empty()) stack.push_back("0");
            else return true;
        }
    }
    //stack에 뭔가 남아있다는건 연산안된다는 뜻
    return false;

}

int main()
{
    for(int tc = 0; tc < 10 ; tc++)
    {
        string s_N;
        bool ans = true;
        getline(cin, s_N);
        int N = stoi(s_N);

        for(int i=0 ; i < N ; i++)
        {
            string input;
            getline(cin, input);
            vector<string> s_input = parseInput(input);
            //ans가 false이면 더이상 maketree할 필요없음
            if(ans) ans = makeTree(s_input);
        }
        //ans가 false이면 stack가지고 연산가능성 살펴볼필요없음
        if(ans)
        {
            ans = solve(N);
        }
        cout << "#" << tc+1 << "  " << ans << endl;
    }
}
