/*
 * 2023.12.05
 * 해설 풀이
 * median보다 작은 숫자들로 구성된 max heap + median보다 큰 숫자들로만 구성된 min heap 관리
 * => 매 순간마다 O(logM)시간에 최신 중앙값을 구해줄 수 있음
 * t개의 테스트케이스에 대해 주어진 m개의 숫자마다 우선순위큐를 살펴봐야 함 = O(TMlogM)
*/

#include <iostream>
#include <queue>
#include <algorithm>

#define MAX_N 100000

using namespace std;

// 변수 선언
int t, m;
int arr[MAX_N];

void FindMedian(){
    // 중앙값(median)을 계속 관리해줌
    // 중앙값보다 작은 숫자들을 max heap으로 관리(max_pq)
    // 중앙값보다 큰 숫자들을 min heap으로 관리(min_pq)
    // 새로운 숫자가 추가될 때마다 그에 따라 median, max_pq, min_pq를 업데이트 해주기
    int median = arr[0];
    priority_queue<int> max_pq;
    priority_queue<int> min_pq;
    cout << median << ' ';

    for(int i=1; i<m; i++){
        // Case 1.
        // 짝수 번째에 새로운 숫자가 주어졌을 경우에는 양쪽 max_pq, min_pq에 들어있는 원소 수 동일
        // 중앙값은 그대로 두고 median과 arr[i]값을 비교해서 적절한 pq에 넣어주기
        if(i % 2 == 1){
            if(arr[i] < median)
                max_pq.push(arr[i]);
            else
            {
                min_pq.push(-arr[i]);
            }
        }
        // Case 2.
        // 홀수 번째에 새로운 숫자가 주어졌을 경우에는
        // max_pq, min_pq 중 개수가 1개 더 많은 곳이
        // 어디인지에 따라 다른 전략을 취해줌
        else{
            // Step1.
            // 먼저 개수가 1개 더 많은 pq에서 우선순위가 가장 큰 값을 뽑아줌=new_cand
            int new_cand;
            if((int)max_pq.size() > (int)min_pq.size()){
                new_cand = max_pq.top();
                max_pq.pop();
            }
            else{
                new_cand = -min_pq.top();
                min_pq.pop();
            }

            // Step 2.
            // 이제 max_pq, min_pq에 들어있는 숫자 개수는 동일
            // 이제 median, arr[i], new_cand에서
            // 가장 작은 값은 max_pq에, 가운데 값은 median에, 가장 큰 값은 min_pq에 넣어주기
            // 정렬을 이용해 편하게 구현
            int nums[] = {median, arr[i], new_cand};
            sort(nums, nums+3);

            // 순서대로 값을 넣어주기
            max_pq.push(nums[0]);
            median = nums[1];
            min_pq.push(-nums[2]);

            // 홀수 번째의 경우에는 중앙값 출력
            cout << median << ' ';
        }
    }
    cout << '\n';
}

int main(){
    // 입력:
    cin >> t;
    while(t--){
        cin >> m;
        for(int i=0; i<m; i++)
            cin >> arr[i];

        // 홀수 번째마다 중앙값을 찾는 것을 반복
        FindMedian();
    }
    return 0;
}