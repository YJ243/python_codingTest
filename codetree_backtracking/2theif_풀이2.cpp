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
// best_val[sx][sy] : (sx, sy) ~ (sx, sy+m-1) 까지 물건을
//                     잘 골라 얻을 수 있는 최대 가치를 전처리 때 저장해놓을 배열

int best_val[MAX_N][MAX_N];

int a[MAX_M];

int ans;
int max_val;

int main(){
    // 입력:
    cin >> n >> m >> c;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> weight[i][j];
    
    // preprocessing 과정이다.
    // 미리 각각의 위치에 대해 최적의 가치를 구해 best_val 배열에 저장해놓는다.
    for(int sx = 0; sx < n; sx++)
        for(int sy=0; sy<n; sy++)
            if(sy + m-1 < n)    // 만약 도둑이 훔치려는 물건의 범위가 격자 내에 있다면
                best_val[sx][sy] = FindMax(sx, sy);
}