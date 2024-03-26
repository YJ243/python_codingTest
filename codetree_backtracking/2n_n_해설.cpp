/*
 * 2024.1.14
 * 두 그룹 중 첫 번째 그룹에 속할 원소가 어떤 것인지를 뽑는 backtracking 작성
 * 각 조합에 대해 첫 번째 그룹에 속하는 원소들은 전부 더하고, 두 번째 그룹에 속하는 원소들은 전부 뺐을 때
 * 나오는 결과값의 절댓값을 구해 이 중 최솟값을 출력하기
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <climits>

#define MAX_N 10
using namespace std;
int n;
int num[2*MAX_N];
bool visited[2*MAX_N];

int ans = INT_MAX;

void Calc(){
    int diff = 0;
    for(int i=0; i<2*n; i++)
        diff = (visited[i]) ? (diff+num[i]) : (diff-num[i]);
    return abs(diff);
}

void FindMin(int idx, int cnt){
    if(cnt == n){
        ans = min(ans, Calc());
        return;
    }
    if(idx == 2*n)
        return;
    
    // 현재 숫자를 첫 번째 그룹에 사용한 경우
    visited[idx] = true;
    FindMin(idx+1, cnt+1);
    visited[idx] = false;

    // 현재 숫자를 두 번째 그룹에 사용한 경우
    FindMin(idx+1, cnt);
}

int main(){
    cin >> n;

    for(int i=0; i<2*n; i++)
        cin >> num[i];
    
    FindMin(0,0);

    cout << ans;
    return 0;
}