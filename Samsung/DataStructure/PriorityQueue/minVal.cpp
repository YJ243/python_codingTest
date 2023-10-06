/*
2023.10.07
*/

#include <iostream>
#include <queue>

#define MAX_N 100000

using namespace std;

// 변수 선언
int n;
int arr[MAX_N];
priority_queue<int>pq;

int main(){
    // 입력
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    // priority queue를 이용해 진행
    for(int i=0; i<n; i++){
        // 0이 아니라면, 해당 숫자를 priority queue에 넣어줌
        // 이때 최솟값을 구하기 위해서는 -를 붙여야 함
        if(arr[i] != 0){
            pq.push(-arr[i]);
        }
        // 0이라면 가장 작은 값을 출력하고 배열에서 제거
        else{
            if(pq.empty())
                cout << 0 << '\n';
            
            // 그렇지 않다면 최솟값 제거
            else{
                int min_val = -pq.top();
                pq.pop();
                cout << min_val << '\n';
            }
        }
    }
    return 0;
}