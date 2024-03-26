/*
 * 2024.03.22
 * 해설 풀이1
 * 모든 조합을 만들어 낸 뒤, 각각의 조합에 대해 선택한 숫자들끼리의 xor 연산 겨로가 중 최댓값 구하기
 * xor 연산의 경우 항등원이 0이기 때문에 초기값은 0으로 설정하면 된다.
 * 시간복잡도: O(C(N,M)*M)
*/

#include <iostream>
#include <algorithm>

#define MAX_NUM 20

using namespaces std;

// 전역 변수 선언:
int n, m;
int A[MAX_NUM];
bool visited[MAX_NUM];

int ans;

int Calc() {
    // xor 연산의 항등원인 0을 초기값으로 설정합니다.
    int val = 0;
    for(int i = 0; i < n; i++)
        if(visited[i])
            val ^= A[i];
    
    return val;
}

void FindMaxXor(int curr_idx, int cnt){
    if(cnt == m){
        // 선택된 모든 조합에 대해 xor 연산을 적용해본다.
        ans = max(ans, Calc());
        return;
    }
    if(curr_idx == n)
        return;
    // curr_idx index에 있는 숫자를 선택하지 않은 경우
    FindMaxXor(curr_idx+1, cnt);

    // curr_idx index에 있는 숫자를 선택한 경우
    visited[curr_idx] = true;
    FindMaxXor(curr_idx+1, cnt+1);
    visited[curr_idx] = false;
}

int main(){
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> A[i];
    
    FindMaxXor(0,0);

    // 출력:
    cout << ans;
    return 0;
}