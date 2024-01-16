#include <iostream>
#include <algorithm>
#include <cstdlib>

#define MAX_NUM 20

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];

int GetArea(int k) {
    return k * k + (k+1) * (k+1); 
}

bool InRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

// 주어진 k에 대하여 모서리에서 채굴 가능한 금의 개수를 반환하기
int GetNumOfGoldInBorder(int row, int col, int k){
    int num_of_gold = 0;
    int dx[4] = {1,1,-1,-1}, dy[4] = {-1,1,1,-1}; // 방향에 따라 바뀌는 x와 y의 변화량 정의

    if(k == 0)
        return grid[row][col];

    int curr_x = row-k, curr_y = col;       // 순회 시작점 설정

    for(int curr_dir = 0; curr_dir<4; curr_dir++){
        for(int step = 0; step < k; step++){
            if(InRange(curr_x, curr_y)){
                num_of_gold += grid[curr_x][curr_y];
            }
            curr_x = curr_x + dx[curr_dir];
            curr_y = curr_y + dy[curr_dir];
        }
    }
}
int main(){
    int max_gold = 0;

    cin >> n >> m;
    for(int row = 0; row < n; row++)
        for(int col = 0; col < n; col++)
            cin >> grid[row][col];


    for(int row=0; row<n; row++){
        for(int col=0; col<n; col++){
            int num_of_gold = 0;
            for(int k=0; k<=2*(n-1); k++){
                // 이전 k까지 구한 금의 개수에
                // 해당 k의 모서리에 존재하는 금의 개수를 더해주기
                num_of_gold += GetNumOfGoldInBorder(row, col, k);

                if(num_of_gold*m >= GetArea(k))
                    max_gold = max(max_gold, num_of_gold);
            }
        }
    }
    return 0;
}