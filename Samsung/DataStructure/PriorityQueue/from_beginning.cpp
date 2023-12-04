/*
 * 2023.12.04
 * priority_queue의 삽입,삭제,검색 시간복잡도를 고려하지 않아서 틀린 문제
 * 정수/정수=정수니 (double)을 꼭 붙여야 한다
 * 뒤에서부터 보도록 하여 중복되는 연산을 계속 하지 않도록 해야 함
*/

/*
// 내 처음 로직---
// K는 1부터 N-1까지 순서대로 K개의 수를 지우고 난 뒤 남아있는 수들 최솟값을 찾는 것=O(N^2)
// 
 for(int K=1; K<=N-2; K++){
        for(int i=K; i<N; i++){
            pq.push(arr[i]);    // 앞에서부터 K개를 삭제하고 pq에 집어넣음

        }
        int sum_val = 0;
        while(pq.size() > 1){
            int val = pq.top();
            pq.pop();
            sum_val += val;
        }
        int avg_val = sum_val / (N-K-1);

        ans = max(ans, avg_val);
        pq.pop();

    }
*/

#include <iostream>
#include <queue>

#define MAX_N 100000

using namespace std;

// 변수 선언
int n;
int arr[MAX_N];
int sum_val;
double max_avg;
priority_queue<int> pq;

int main(){
    // 입력:
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> arr[i];
    // 일단 맨 마지막 원소는 넣고 시작함
    // 최솟값만 pop하여 빼줄 것이기 때문에 -를 붙여서 pq에 넣기
    pq.push(-arr[n-1]);
    sum_val += arr[n-1];

    // k가 n-2일 때부터 1일 때까지 거꾸로 탐색
    // priority queue를 이용하여 진행
    for(int i=n-2; i >= 1; i--){
        // 앞에서부터 k개를 삭제하고 나면
        // 뒤에 i ~ n-1까지의 숫자만 남음
        pq.push(-arr[i]);
        sum_val += arr[i]; // 일단 i~n-1번째까지의 합, 즉 남아있는 정수 들 다 더하고 
        // 이제 그 중 가장 작은 숫자를 찾아서
        // 그 숫자를 제외한 평균을 구하기
        double avg = (double)(sum_val - (-pq.top())) / (n-i-1);

        // 평균이 최대가 된다면 정답을 현재 평균으로 갱신
        max_avg = max(avg, max_avg);
    }

    // 평균값의 최대를 출력
    cout << fixed;
    cout.precision(2);

    cout << max_avg;
    return 0;
}