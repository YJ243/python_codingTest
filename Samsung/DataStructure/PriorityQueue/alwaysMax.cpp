/*
2023.10.07
*/

#include <iostream>
#include <queue>

#define MAX_N 100000

using namespace std;

// 변수 선언
int n, m;
int arr[MAX_N];
priority_queue<int> pq;

int main(){
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> arr[i];

    // priority queue에 숫자들을 넣어줌
    for(int i=0; i<n; i++)
        pq.push(arr[i]);
    

    // m번에 걸쳐서
    // 최댓값을 찾아 1씩 빼주는 것을 반복
    while(m--){
        // 최댓값을 찾기
        int max_val = pq.top();
        // 최댓값을 제거
        pq.pop();
        // 1 뺀 값을 다시 넣어줌
        pq.push(max_val - 1);
    }
    cout << pq.top() << '\n';
    return 0;
}