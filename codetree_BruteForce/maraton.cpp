/*
* 2023.11.13
* 마라톤 중간에 택시타기2
*/

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <climits>

using namespace std;
int N;
vector<pair<int, int> > a; // 체크포인트 좌표

int main() {
    // 입력
    cin >> N;
    for(int i=0; i<N; i++){
        int x,y;
        cin >> x >> y;
        a.push_back(make_pair(x,y));
    }

    // 체크포인트를 하나 건너뛰었을 때 최소 거리
    int min_dist = INT_MAX;
    for(int i=1; i<N-1; i++){   // i번째 체크포인트 건너뛰기
        int next = 0;   // 다음으로 점프할 체크포인트
        int dist = 0;   // 현재 거리
        int cur_x = a[0].first, cur_y = a[0].second;    // 시작점 설정
        while(true){
            next++;     // 점프할 체크포인트 1 증가
            if(next== i)    // 그 체크포인트를 건너뛰어야 한다면
            {
                next++;     // 1 증가
            }
            if(next == N)   break;  // 마지막 체크포인트까지 다 왔다면 반복문 빠져나가기
            dist += abs(cur_x-a[next].first) + abs(cur_y-a[next].second); // 거리 계산
            cur_x = a[next].first, cur_y = a[next].second; // 점프할 체크포인트로 현재 좌표 이동
        }
        min_dist = min(dist, min_dist); // 최솟값 찾기
        
    }
    // 출력
    cout<<min_dist;
    return 0;
}