/*
 * 2024.03.22
 * 해설 풀이
 * N번의 턴에 대해 각 턴마다 K개 중 어떤 말을 움직일 것인지 선택하는 재귀함수 작성
 * 이미 점수를 획득한 말을 움직이지 않으면 총 탐색 시간을 줄일 수 있다
 * 그런데 이렇게 진행하게 되면 n번의 턴을 다 끝마치지 못하고 최대 점수를 얻는 경우도 생김
 * 따라서 꼭 모든 턴에 대해 점수를 계산하여 그 중 최댓값을 계산해야만 한다.
*/

#include <iostream>
#include <algorithm>

#define MAX_N 12
#define MAX_K 4

using namespace std;

int n, m, k;
int nums[MAX_N], pieces[MAX_K];

int ans;

// 점수를 계산한다
int Calc(){
    int score = 0;
    for(int i=0; i<k; i++)
        score += (pieces[i] >= m);
    return score;
}

void FindMax(int cnt){
    // 말을 직접  n번 움직이지 않아도
    // 최대가 될 수 있으므로 항상 답을 갱신한다
    ans = max(ans, Calc());

    // 더 이상 움직일 수 없으면 종료한다.
    if(cnt == n)
        return;
    
    for(int i=0; i<k; i++){
        // 움직여서 더 이득이 되지 않는 말은 더이상 움직이지 않는다.
        if(pieces[i] >= m)
            continue;
        pieces[i] += nums[cnt];
        FindMax(cnt+1);
        pieces[i] -= nums[cnt];
    }
}

int main(){
    cin >> n >> m >> k;
    for(int i=0; i<n; i++)
        cin >> nums[i];

    for(int i=0; i<k; i++)
        pieces[i] = 1;
    
    FindMax(0);

    cout << ans;
    return 0;
}