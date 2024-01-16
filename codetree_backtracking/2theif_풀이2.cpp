/*
 * 2024.1.11
 * 첫번째 도둑은 같은 위치에 대해 두번째 도둑이 다 backtracking을 돌 동안 계속해서 다시 돌게 됨
 * 완탐 이전에 미리 모든 각각의 (sx, sy) ~ (sx, sy+m-1)경우에 대해 backtracking을 돌려서
 * 해당 구간 내에서 최적의 가치를 구해 그 값을 배열에 저장해놓는 preprocessing을 적용
 * 그럼 이후에 brute force search시 그 값을 그대로 이용하여 중복 계산을 없앨 수 있음
 * 시간복잡도: 처음 각각의 위치 (sx, sy)에 대해 backtracking을 돌리는데 n^2*(2^m),
 *            이후 brute force 하는데 backtracking 없이 위치를 고르기만 하면 되므로 n^4
              O(N^2*(2^M)+N^4)
              
*/
#include <iostream>
#include <algorithm>

#define MAX_N 10
#define MAX_M 5

using namespace std;

// 전역 변수 선언:
int n, m, c;
int weight[MAX_N][MAX_N];
// best_val[sx][sy]: (sx, sy) ~ (sx, sy+m-1)까지 물건을 잘 골라 얻을 수 있는 최대 가치를
//                    preprocessing 때 저장해놓을 배열
int best_val[MAX_N][MAX_N];

int a[MAX_N];

int ans;
int max_val;

void FindMaxSum(int curr_idx, int curr_weight, int curr_val){
    if(curr_idx == m){
        // 고른 무게들의 합이 c를 넘지 않는 경우에만 갱신
        if(curr_weight <= c)
            max_val = max(max_val, curr_val);
        return;
    }
    // curr_idx index에 있는 숫자를 선택하지 않은 경우
    FindMaxSum(curr_idx+1, curr_weight, curr_val);

    // curr_idx index에 있는 숫자를 선택한 경우
    // 무게는 a[curr_idx]만큼 늘지만
    // 문제 정의에 의해 가치는 a[curr_idx]*a[curr_idx]만큼 늘어남
    FindMaxSum(curr_idx+1, curr_weight+a[curr_idx], curr_val+a[curr_idx]*a[curr_idx]);

}

// (sx, sy) ~ (sx, sy+m-1)까지의 숫자들 중 적절하게 골라
// 무게의 합이 c를 넘지 않게 하면서 얻을 수 있는 최대 가치를 반환
int FindMax(int sx, int sy){
    // 문제를 a[0] ~ a[m-1]까지 m개의 숫자가 주어졌을 때
    // 적절하게 골라 무게의 합이 c를 넘지 않게 하면서 얻을 수 있는 최대 가치를
    // 구하는 문제로 바꾸기 위해 a배열을 적절하게 채워넣음
    for(int i=sy; i<=sy+m-1; i++)
        a[i-sy] = weight[sx][i];
    
    // 2^m개의 조합에 대해 최적의 값을 구하기
    max_val = 0;
    FindMaxSum(0,0,0);
    return max_val;
}
// [a,b], [c,d] 이 두 선분이 겹치는지 판단
bool Intersect(int a, int b, int c, int d){
    // 겹치지 않을 경우를 계산하여 그 결과를 반전시켜 반환
    return !(b<c || d<a);
}

// 두 도둑의 위치가 올바른지 판단
bool Possible(int sx1, int sy1, int sx2, int sy2){
    // 두 도둑이 훔치려는 물건의 범위가 격자를 벗어나는 경우에는 불가능
    if(sy1+m-1 >= n || sy2+m-1 >= n)
        return false;

    // 두 도둑이 훔칠 위치의 행이 다르다면 겹칠 수가 없으므로 무조건 가능
    if(sx1 != sx2)  return true;

    // 두 구간끼리 겹친다면 불가능
    if(Intersect(sy1, sy1+m-1, sy2, sy2+m-1))
        return false;

    // 행이 같으면서 구간끼리 겹치지 않으면 가능
    return true;
}

int main(){
    // 입력:
    cin >> n >> m >> c;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> weight[i][j];
    // preprocessing 과정
    // 미리 각각의 위치에 대해 최적의 가치를 구해 best_val 배열에 저장
    for(int sx=0; sx<n; sx++)
        for(int sy=0; sy<n; sy++)
            if(sy+m-1 < n)
                best_val[sx][sy] = FindMax(sx, sy);
    // 첫 번째 도둑은 (sx1, sy1) ~ (sx1, sy1+m-1)까지 물건을 훔치려 하고
    // 두 번째 도둑은 (sx2, sy2) ~ (sx2, sy2+m-1)까지의 물건을
    // 훔치려 한다고 했을 때 가능한 모든 위치를 탐색해보기
    for(int sx1=0; sx1<n; sx1++)
        for(int sy1=0; sy1<n; sy1++)
            for(int sx2=0; sx2<n; sx2++)
                for(int sy2=0; sy2<n; sy2++){
                    // 두 도둑의 위치가 올바른지 판단
                    // 각 위치에서의 얻을 수 있는 최대 가치의 합을 ans와 비교하여 갱신
                    // 이때는 재귀함수를 또 돌지 않고 미리 저장되어 있는 best_Val 배열을 활용해
                    // 바로 답을 구해주기
                    if(Possible(sx1, sy1, sx2, sy2)){
                        ans = max(ans, best_val[sx1][sy1]+best_val[sx2][sy2]);
                    }
                }

    // 출력:
    cout << ans;
    return 0;
}