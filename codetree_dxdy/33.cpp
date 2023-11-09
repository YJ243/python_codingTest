/*
 * 2023.11.06
 * 내 풀이
*/
/*
#include <iostream>
#define INT_MAX 20

using namespace std;

int N;
int maze[INT_MAX][INT_MAX];

int main() {
    cin >> N;
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            cin>>maze[i][j];
        }
    }
    int max=-1, cur=0;
    for(int i=0; i<=N-3; i++){
        for(int j=0; j<=N-3; j++){
            cur = 0;
            for(int x=i; x<=i+2; x++){
                for(int y=j; y<=j+2; y++){
                    if(maze[x][y] == 1){
                        cur++;
                    }
                }
            }
            if(max<cur){
            max = cur;
            }
        }
    }
    cout<<max;
    return 0;
}
*/

// 해설 풀이
#include <iostream>
#include <algorithm>

#define MAX_N 20

using namespace std;

int n;
int grid[MAX_N][MAX_N];

// (row_s, col_s) ~ (row_e, col_e) 사이의 금의 개수를 계산
int GetNumOfGold(int row_s, int col_s, int row_e, int col_e){
    int num_of_gold = 0;
    for(int i=row_s; i<=row_e; i++)
        for(int j=col_s; j<=col_e;j++)
            num_of_gold += grid[i][j];
    return num_of_gold;
}
int main(){
    int max_gold = 0;

    // 입력:
    cin >> n;
    for(int row=0; row<n; row++){
        for(int col = 0; col < n; col++){
            cin>>grid[row][col];
        }
    }
    // (row,col)이 3*3 격자의 좌측 상단 모서리인 경우를 전부 탐색
    for(int row=0; row<n; row++){
        for(int col=0; col<n; col++){
            // 3*3 격자가 n*n 격자를 벗어나는 경우는 계산하지 않음
            if(row+2 >= n || col+2 >= n) continue;

            // 금의 개수를 계산
            int num_of_gold = GetNumOfGold(row, col, row+2, col+2);

            // 최대 금의 개수를 저장
            max_gold = max(max_gold, num_of_gold);
        }
    }
}