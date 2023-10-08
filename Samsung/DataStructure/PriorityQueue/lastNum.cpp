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
priority_queue<int> pq;

int main(){
    // 입력:
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    // priority queue에 숫자를 넣어줌
    for(int i=0; i<n; i++)
        pq.push(arr[i]);

    // 마지막 숫자가 남을 때까지 가장 큰 숫자 2개를 뽑아서 제거
    // 그 이후 그 차이를 다시 집어넣음
    while(pq.size() >= 2){
        // 가장 큰 숫자 2개를 뽑고 제거
        int x = pq.top(); pq.pop();
        int y = pq.top(); pq.pop();

        // 두 숫자의 차이를 다시 넣어줌 
        // 차이가 0인 경우에는 다시 넣지 않음
        int diff = x-y;
        if(diff != 0)
            pq.push(diff);
    }

    // 마지막으로 남은 숫자가 정확히 하나라면 그 숫자를 출력
    // 아무 숫자도 남지 않으면 -1을 출력
    if(pq.size() == 1)
        cout << pq.top();
    else
    {
        cout << -1;
    }
    return 0;
    


}