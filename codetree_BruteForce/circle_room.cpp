/*
 * 2023.11.13
 * 원 모양으로 되어 있는 방
*/

#include <iostream>
#include <climits>
#define MAX_N 1003

using namespace std;

int N;
int room[MAX_N];        // room[i]: i번 방에 들어가야 하는 사람 수

int main(){
    // 입력
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> room[i];
    }
    // 각 방에 정해진 인원이 들어가는 데까지의 최소화된 거리의 합
    int min_dist = INT_MAX;
    for(int i=0; i<N; i++){ // i번째 방에서 시작
        int cur_dist = 0;   // 현재까지 거리의 합
        int next_idx = (i+1)%N; // i+1부터 탐색
        int next = i+1;         

        while(true){
            if(next_idx == i) // 처음으로 돌아오면 반복문 탈출
                break;
            cur_dist += room[next_idx]*(next-i);    // 각 방에 들어와야 하는 인원수 * 거리
            next_idx = (next_idx+1)%N;
            next++;
        }
        min_dist = min(cur_dist, min_dist);
    }
    cout << min_dist;
    return 0;
}
