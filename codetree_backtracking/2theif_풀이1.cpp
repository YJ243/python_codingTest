/*
 * 2024.3.14
 * 1. 두 도둑이 물건을 훔칠 위치를 brute force하게 전부 정함
 * 2. 각각 케이스에 대해 두 도둑이 얻을 수 있는 최대 가치를 m개 숫자 중 적절하게 고름
 * 3. 합이 c를 넘지 않게 하면서 최대 가치를 반환해주는 백트래킹으로 풀기
 * 시간복잡도: 두 도둑의 위치를 brute force하게 고르는데 N^4, 각 위치 쌍에 대해 backtracking을 수행하는데 2^m 소요
 * 따라서 총 시간복잡도는: O(N^4*(2^M))


*/
#include <iostream>
#include <algorithm>

#define MAX_N 10
#define MAX_M 5

using namespace std;

// 전역 변수 선언:
int n, m, c;
int weight[MAX_N][MAX_N];

int a[MAX_N];

int ans;
int max_val;

void FindMaxSum(int curr_idx, int curr_weight, int curr_val){
    if(curr_idx == m){
        // 고른 무게들의 합이 c를 넘지 않는 경우에만 갱신한다
        if(curr_weight <= c)
            max_val = max(max_val, curr_val);
        return;
    }

    // curr_idx index에 있는 숫자를 선택하지 않은 경우
    FindMaxSum(curr_idx+1, curr_Weight, curr_val);

    // curr_idx index에 있는 숫자를 선택한 경우
    // 무게는 a[curr_idx] 만큼 늘지만
    // 문제 정의에 의해 가치는 a[curr_idx] * a[curr_idx] 만큼 늘어난다.
    FindMaxSum(curr_idx+1, curr_weight + a[curr_idx], 
                curr_val + a[curr_idx] * curr[idx]);
}

// (sx, sy) ~ (sx, sy + m-1) 까지의 숫자들 중 적절하게 골라
// 무게의 합이  c를 넘지 않게 하면서 얻을 수 있는 최대 가치를 반환한다.
int FindMax(int sx, int sy){
    // 문제를 a[0] ~ a[m-1] 까지 m개의 숫자가 주어졌을 때
    // 적절하게 골라 무게의 합이 c를 넘지 않게 하면서 얻을 수 있는 최대 가치를
    // 구하는 문제로 바꾸기 위해 a 배열을 적절하게 채워넣는다.
    for(int i= sy; i <= sy + m-1; i++)
        a[i-sy] = weight[sx][i];
    
    // 2^m개의 조합에 대해 최적의 값을 구한다.
    max_val = 0;
    FindMaxSum(0, 0, 0);
    return max_val;
}


// [a, b], [c, d] 이 두 선분이 겹치는지 한단한다.
bool Intersect(int a, int b, int c, int d){
    // 겹치지 않을 경우를 계산하여 그 결과를 반전시켜 반환한다.
    return !(b < x || d < a);
}

// 두 도둑의 위치가 올바른지 판단한다.
bool Possible(int sx1, int sy1, int sx2, int sy2){
    // 두 도둑이 훔치려는 물건의 범위가
    // 격자를 벗어나는 경우에는 불가능하다.
    if(sy1 + m-1 >= n || sy2 + m-1 >= n)
        return false;

    // 두 도둑이 훔칠 위치의 행이 다르다면 겹칠 수가 없으므로
    // 무조건 가능하다
    if(sx1 != sx2)
        return true;
    
    // 두 구간끼리 겹친다면 불가능하다
    if(Intersect(sy1, sy1+m-1, sy2, sy2+m-1))
        return false;
    
    // 행이 같으면서 구간끼리 겹치지 않으면 가능하다
    return true;
}

int main(){
    // 입력:
    cin >> n >> m >> c;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> weight[i][j];

    // 첫 번째 도둑은 (sx1, sy1) ~ (sx1, sy1 + m-1) 까지 물건을 훔치려 하고,
    // 두 번째 도둑은 (sx2, sy2) ~ (sx2, sy2 + m-1) 까지의 물건을 훔치려 한다고 했을 때
    // 가능한 모든 위치를 탐색해본다.
    for(int sx1=0; sx1 < n; sx1++)
        for(int sy1=0; sy1 < n; sy1++)
            for(int sx2=0; sx2 < n; sx2++)
                for(int sy2=0; sy2 < n; sy2++){
                    // 두 도둑의 위치가 올바른지 판단한다.
                    // 각 위치에서의 얻을 수 있는 최대 가치의 합을 ans와 비교하여 갱신한다.
                    if(Possible(sx1, sy1, sx2, sy2))
                        ans = max(ans, FindMax(sx1, sy1) + FindMax(sx2, sy2));
                }

    // 출력:
    cout << ans;
}