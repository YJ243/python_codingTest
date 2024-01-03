/*
 * 2023.12.20
 * 제거할 원소의 위치가 주어졌을 때, 실제 제거하지 않고 인접한 숫자간의 차의 합 계산
 * 이를 위해 prev라는 변수를 사용해 바로 직전에 적혀 있던 숫자가 무엇인지 기록해주기
*/
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstdlib>

#define MAX_N 100
using namespace std;

int n;
int arr[MAX_N];

// 제거된 원소의 위치를 removed_idx라 가정했을 때,
// 인접한 원소간의 차의 합을 계산해 반환하기
int Score(int removed_idx){
    // 합을 계산하기
    int sum = 0;

    // 바로 직전에 적혀있던 숫자를 기록하기
    // -1인 경우, 아직 숫자가 기록된 적이 없다는 뜻
    int prev = -1;

    // 각 숫자들을 순회하기
    for(int i=0; i<n; i++){
        // 지워진 원소라면 패스하기
        if(i == removed_idx) continue;

        // 이전에 적혀있던 숫자가 있는 경우에만
        // 인접한 숫자간의 차를 sum에 더해줌
        if(prev != -1)
            sum += abs(arr[i]-prev);

        // 마지막으로 적혀있던 숫자 값을 갱신
        prev = arr[i];
    }
    // 인접한 원소간의 차의 합을 반환
    
}


int main(){
    // 입력
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> arr[i];

    int min_score = INT_MAX;

    // 2배를 할 숫자의 위치 i를 결정하고,
    // 그 다음 제거할 숫자의 위치 j를 결정하여
    // 남은 숫자들의 인접한 차의 합 중 최솟값 찾기
    for(int i=0; i<n; i++){
        arr[i] *= 2;

        // 제거할 숫자의 위치를 결정하기
        for(int j=0; j<n; j++)
            min_score = min(min_score, Score(j));
        
        // 그다음 상태 진행을 위해,
        // 이전에 2배를 한 값을 다시 이전 상태로 만들어 줌
        arr[i] /= 2;
    }
    cout << min_score;
    return 0;
}