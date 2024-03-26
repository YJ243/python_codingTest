/*
 * 2024.03.22
 * 해설 풀이2
 * n개 중 m개를 뽑는 가능한 모든 조합을 만들어 내는 도중 지금까지 선택된 숫자들의
 * xor 계산 결과값을 지칭하는 curr_val을 재귀 함수의 인자로 같이 가지고 다니면서
 * 계산이 가능하다. 즉 간단한 계산의 경우 backtracking 과정 속에서 동시에 이루어질 수 있다.
 * m개의 숫자를 전부 고르게 되었을 때 다시 선택된 m개의 숫자를 보며 xor을 할 필요가 없음
 * 시간복잡도: O(C(N,M))
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

void FindMaxXor(int curr_idx, int cnt, int curr_val){
    if(cnt == m){
        // 선택된 모든 조합에 대해 xor 연산을 적용해본다.
        ans = max(ans, curr_val);
        return;
    }
    if(curr_idx == n)
        return;
    // curr_idx index에 있는 숫자를 선택하지 않은 경우
    FindMaxXor(curr_idx+1, cnt, curr_val);

    // curr_idx index에 있는 숫자를 선택한 경우
    FindMaxXor(curr_idx+1, cnt+1, curr_val ^ A[curr_idx]);
}

int main(){
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> A[i];
    
    FindMaxXor(0,0,0);

    // 출력:
    cout << ans;
    return 0;
}