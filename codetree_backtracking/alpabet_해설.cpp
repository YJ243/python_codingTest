/*
 * 해설
 * 24.03.22
 * 1. Backtracking으로 'a'부터 'f'까지 각 알파벳에 대응되는 숫자를 1-4중 하나 고르기
 * 2. 그 이후 식을 왼쪽에서 오른쪽 방향으로 순서대로 읽으면서 값 계산
 * 3. 그 중 가능한 값 중 최댓값 고르기 
 * 시간복잡도: O(4^N * L): N은 6, L은 문자열 길이
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <climits>

#define MAX_N 6

using namespace std;

int n = 6;

string expression;
int num[MAX_N];
int ans = INT_MIN;

int Conv(int idx){      // convert
    return num[expression[idx] - 'a'];
}

int Calc(){
    int length = (int) expression.size();
    int value = Conv(0);
    for(int i=2; i<length; i += 2){
        if(expression[i-1] == '+')
            value += Conv(i);
        else if(expression[i-1] == '-')
            value -= Conv(i);
        else
            value *= Conv(i);l
    }
    return value;
}

// 'a'부터 'f'까지 순서대로
// 0부터 5번째 index까지의 값을
// 1~4중에 하나로 채우기
void FindMax(int cnt){
    if(cnt == n){
        ans = max(ans, Calc());
        return;
    }

    for(int i=1; i<=4; i++){
        num[cnt] = i;
        FindMax(cnt+1);
    }
}

int main() {
    cin >> expression;
    FindMax(0);
    cout << ans ;
    
    return 0;
}