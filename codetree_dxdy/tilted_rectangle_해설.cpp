/*
 * 2024.1.16
 * 해설
 * 시간복잡도: 잡아볼 수 있는 직사각형 개수: O(N^4)개, 직사각형 경계를 순회하는데 시간 O(N) => O(N^5)
*/

#include <iostream>
#include <algorithm>

#define MAX_N 20
#define DIR_NUM 4

using namespace std;
int n;                      // 격자 크기
int grid[MAX_N][MAX_N];     // 격자


bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int GetScore(int x, int y, int k, int l){
    int dx[DIR_NUM] = {-1,-1,1,1};
    int dy[DIR_NUM] = {1,-1,-1,1};
    int move_num[DIR_NUM] = {k,l,k,l};  // 이렇게 해놓으면 %2이런식으로 하는 것 보다 훨씬 편함

    int sum_of_nums=0;

    // 기울어진 직사각형의 경계를 쭉 따라가보기
    for(int d=0; d<DIR_NUM; d++){
        for(int q=0; q<move_num[d]; q++){
            x += dx[d]; y += dy[d];

            // 기울어진 직사각형이 경계를 벗어나는 경우라면 불가능하다는 의미로
            // 답이 갱신되지 않게 0을 반환
            if(!InRange(x,y))
                return 0;
            sum_of_nums += grid[x][y];
        }
    }
    return sum_of_nums;
}

int main() {
    cin >> n;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];

    int ans = 0;

    // (i,j)를 시작으로 1,2,3,4 방향 순서대로 길이 [k,l,k,l]만큼
    // 이동하면서 그려지는 기울어진 직사각형 잡기
    // 완전탐색 진행
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=1; k<n; k++){
                for(int l=1; l<n; l++){
                    ans = max(ans, GetScore(i,j,k,l));
                }
            }
        }
    }    
    cout << ans;
    return 0;
}