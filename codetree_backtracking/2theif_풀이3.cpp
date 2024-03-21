/*
 * 2024.3.22 
 * Brute Force Search + Backtracking + Memoization
 * 풀이 1에서의 비효율은 FindMax 함수에 동일한 (sx, sy) 값이 넘어왔기 때문이다
 * 따라서 또 다시 (sx, sy) ~ (sx, sy + m-1)까지 중 최적의 가치를 찾아달라는 요청이 올 경우
 * 이전에 계산해놨던 값을 반환해주는 식으로 최적화 가능
 * 이를 Memoization
 * 시간복잡도: 각각 (sx, sy) 상태에 대해 단 한 번의 backtracking 연산만 이루어지므로
 * 모든 (sx, sy)에 대해 backtracking을 돌리는데 n^2*(2^m), brute force에 n^4
 * 총 시간복잡도는 O(N^2 * (2^M) + N^4)가 된다.
*/
#include <iostream>
#include <algorithm>

#define MAX_N 10
#define MAX_M 5

using namespace std;

// 전역 변수 선언:
int n, m, c;
int weight[MAX_N][MAX_N];
// best_val[sx][sy] : (sx, sy) ~ (sx, sy+m-1) 까지 물건을
//                     잘 골라 얻을 수 있는 최대 가치를 
//                     이미 계산한 적이 있다면 그 값을 적어놓고
//                     아직 계산해본 적이 없다면 -1이 들어있다.
int best_val[MAX_N][MAX_N];

int a[MAX_M];

int ans;
int max_val;

void FindMaxSum(int curr_idx, int curr_weight, int curr_val) {
    if(curr_idx == m) {
        // 고른 무게들의 합이 c를 넘지 않는 경우에만 갱신합니다.
        if(curr_weight <= c)
            max_val = max(max_val, curr_val);
        return;
    }

    // curr_idx index 에 있는 숫자를 선택하지 않은 경우
    FindMaxSum(curr_idx + 1, curr_weight, curr_val);
    
    // curr_idx index 에 있는 숫자를 선택한 경우
    // 무게는 a[curr_idx] 만큼 늘지만
    // 문제 정의에 의해 가치는 a[curr_idx] * a[curr_idx] 만큼 늘어납니다.
    FindMaxSum(curr_idx + 1, curr_weight + a[curr_idx], 
			   curr_val + a[curr_idx] * a[curr_idx]);
}

// (sx, sy) ~ (sx, sy + m - 1) 까지의 숫자들 중 적절하게 골라
// 무게의 합이 c를 넘지 않게 하면서 얻을 수 있는 최대 가치를 반환합니다.
int FindMax(int sx, int sy) {
    // 이미 (sx, sy) ~ (sx, sy + m-1) 사이의 최적 조합을
    // 계산해본 적이 있다는 뜻이므로, 그 값을 바로 반환한다.
    if(best_val[sx][sy] != -1)
        return best_val[sx][sy];
        
    // 문제를 a[0] ~ a[m - 1]까지 m개의 숫자가 주어졌을 때
    // 적절하게 골라 무게의 합이 c를 넘지 않게 하면서 얻을 수 있는 
	// 최대 가치를 구하는 문제로 바꾸기 위해
    // a 배열을 적절하게 채워넣습니다. 
    for(int i = sy; i <= sy + m - 1; i++)
        a[i - sy] = weight[sx][i];
    
    // 2^m개의 조합에 대해 최적의 값을 구합니다.
    max_val = 0;
    FindMaxSum(0, 0, 0);

    // 나중에 또 (sx, sy) ~ (sx, sy+m-1) 사이의 조합을
    // 계산하려는 시도가 있을 수 있으므로 best_val 배열에 caching 해놓는다.
    best_val[sx][sy] = max_val;
    return max_val;
}

// [a, b], [c, d] 이 두 선분이 겹치는지 판단합니다.
bool Intersect(int a, int b, int c, int d) {
	// 겹치지 않을 경우를 계산하여 그 결과를 반전시켜 반환합니다.
    return ! (b < c || d < a);
}

// 두 도둑의 위치가 올바른지 판단합니다.
bool Possible(int sx1, int sy1, int sx2, int sy2) {
	// 두 도둑이 훔치려는 물건의 범위가 
	// 격자를 벗어나는 경우에는 불가능합니다.
    if(sy1 + m - 1 >= n || sy2 + m - 1 >= n) 
        return false;                        
    
	// 두 도둑이 훔칠 위치의 행이 다르다면
	// 겹칠 수가 없으므로 무조건 가능합니다.
    if(sx1 != sx2)                          
        return true;                        
    
	// 두 구간끼리 겹친다면
	// 불가능합니다.
    if(Intersect(sy1, sy1 + m - 1, sy2, sy2 + m - 1)) 
        return false;                               
    
	// 행이 같으면서 구간끼리 겹치지 않으면
	// 가능합니다.
    return true;                             
}     

int main(){
    // 입력:
    cin >> n >> m >> c;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> weight[i][j];
    
    // 아직 (sx, sy) - (sx, sy + m -1) 부분은 계산해본 적이 없다는 
	// 표시로 절대 best_val이 될 수 없는 -1을 초기값으로 넣어놓습니다.
    for(int sx = 0; sx < n; sx++)
        for(int sy = 0; sy < n; sy++)
            best_val[sx][sy] = -1;
    
    // 첫 번째 도둑은 (sx1, sy1) ~ (sx1, sy1+m-1) 까지 물건을 훔치려 하고
    // 두 번째 도둑은 (sx2, sy2) ~ (sx2, sy2 + m-1) 까지의 물건을 훔치려 한다고 했을 때
    // 가능한 모든 위치를 탐색해본다.
    for(int sx1=0; sx1 < n; sx1++)
        for(int sy1=0; sy1<n; sy1++)
            for(int sx2=0; sx2 < n; sx2++)
                for(int sy2=0; sy2<n; sy2++){
                    // 두 도둑의 위치가 올바른지 판단한다.
                    // 각 위치에서 얻을 수 있는 최대 가치의 합을 ans와 비교하여 갱신한다.
                    // 이때는 재귀함수를 또 돌지 않고 미리 저장되어 있는 best_val 배열을 활용하여 바로 답을 구해준다.
                    if(Possible(sx1, sy1, sx2, sy2))
                        ans = max(ans, best_val[sx1][sy1] + best_val[sx2][sy2]);
                }    

    // 출력:
    cout << ans;

    return 0;
}