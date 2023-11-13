/*
 * 2023.11.07
 * 내 풀이
*/
/*
#include <iostream>
#define MAX_N 200
using namespace std;
int n, m;
int maze[MAX_N][MAX_N];

int result;
int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cin>>maze[i][j];
    }
    // Step 1. 1번 블럭&회전 경우의 수
    
    for(int i=0; i<=n-2; i++){
        for(int j=0; j<=m-2; j++){
            int cur = 0;
            for(int x=i; x<=i+1; x++){
                for(int y=j; y<=j+1; y++){
                    cur += maze[x][y];

                }
            }
            for(int x=i; x<=i+1; x++){
                for(int y=j; y<=j+1; y++){
                    cur -= maze[x][y];
                    if(cur > result)
                        result=cur;
                    cur += maze[x][y];

                }
            }
            
        }
    }
    // Step 2. 2번 블록 회전 전의 경우의 수
    for(int i=0; i<n; i++){
        for(int j=0; j<=m-3; j++){
            int cur = 0;
            for(int k=j;k<=j+2; k++){
                cur += maze[i][k];
            }
            if(result < cur)
                result=cur;  
        }
    }
    // Step 3. 2번 블록 회전 후의 경우의 수
    for(int j=0; j<m; j++){
        for(int i=0; i<=n-3; i++){
            int cur = 0;
            for(int k=i; k<=i+2; k++){
                cur += maze[k][j];
            }
            if(result < cur)
                result = cur;  
        }
    }
    cout<<result;
    return 0;
}
*/

// 해설 풀이

#include <iostream>
#include <algorithm>

#define MAX_NUM 200

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];

// 가능한 모든 모양을 전부 적어줌
int shapes[6][3][3] = {
    {{1,1,0},
    {1,0,0},
    {0,0,0}},

    {{1,1,0},
    {0,1,0},
    {0,0,0}},

    {{1,0,0},
    {1,1,0},
    {0,0,0}},

    {{0,1,0},
    {1,1,0},
    {0,0,0}},

    {{1,1,0},
    {0,0,0},
    {0,0,0}},

    {{1,0,0},
    {1,0,0},
    {1,0,0}},
};

// 주어진 위치에 대하여 가능한 모든 모양을 탐색하며 최대 합을 반환하기
int GetMaxSum(int x, int y){
    int max_sum = 0;

    for(int i=0; i<6; i++){
        bool is_possible = true;
        int sum = 0;
        for(int dx=0; dx<3; dx++){
            for(int dy=0; dy<3; dy++){
                if(shapes[i][dx] == 0) continue;
                if(x+dx >= n || y+dy >=m) is_possible = false;
                else sum += grid[x+dx][y+dy];
            }
        }
        if(is_possible)
            max_sum = max(max_sum, sum);

    }
    return max_sum;
}
int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> grid[i][j];
        }
    }
    int ans = 0;

    // 격자의 각 위치에 대하여 탐색하기
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ans = max(ans, GetMaxSum(i,j));
        }
    }
    cout<<ans;
    return 0;
}