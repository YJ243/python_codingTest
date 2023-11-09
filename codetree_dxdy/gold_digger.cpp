/*
 * 2023.11.09
*/

/*
// 내 풀이
// 1. 처음에 마름모 모양을 찾기 위해 BFS를 돌려야 하나 했지만 가로+세로 <= k로 풀면 되었었음
// 2. 중심이 격자 안에 있다는 것을 놓침
// 3. k를 어디까지 확장해야 하는지 찾지 못했음
// 3-1. 나는 ((2k+1-1)/2)-(n-1)+1 <= n 이 범위로 풀었음, 해설에서는 대각선(왼쪽위->오른쪽 아래)
//      로 가는, 즉  n*n 격자에서 가장 먼 두 점 사이의 거리가 2(n-1)이기 때문에 범위를 그렇게 정함
#include <iostream>
#include <cstdlib>

#define INT_N 20
using namespace std;
int n, m;
int maze[INT_N][INT_N];

// (start_x, start_y)를 중심으로 하고 length만큼 가서 나오는 마름모에서 그 안에 있는 금의 개수를 반환
int GetGold(int start_x, int start_y, int length){
    if(length==0 && maze[start_x][start_y]) return 1;
    int num_gold = 0;
    for(int x=0; x<n; x++){
        for(int y=0; y<n; y++){
            int distance = abs(x-start_x)+abs(y-start_y);
            if(distance<=length && maze[x][y] == 1){// 거리 안에 있고 금이 있다면}
                num_gold++;
            }
        }
    }
    return num_gold;
}
int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++)
        for(int j=0; j<n; j++)
            cin>>maze[i][j];
    int max_gold = 0;
    // Step1. 각 격자별로 탐색하는데
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // Step2. k를 0부터 늘려나가면서 2n-2보다 작거나 같을 때까지 확인
            int cur_gold = 0;
            for(int k=0; k<=2*n-2; k++){
                //cout<<k<<'\n';
                // Step3. 각 격자 칸에서 거리가 k인 부분 안에 있는 금 채굴
                cur_gold = GetGold(i,j,k);
                //cout<<cur_gold<<'\n';
                // Step4. 손해를 보지 않는 경우에만 결과 업데이트
                if(cur_gold*m >= (k*k+(k+1)*(k+1)) && max_gold < cur_gold)
                    max_gold = cur_gold;
            }
        }
    }
    cout << max_gold;
    return 0;
}

*/
#include <iostream>
#include <algorithm>
#include <cstdlib>

#define MAX_NUM 20

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];

// 주어진 k에 대해서 마름모의 넓이를 반환
int GetArea(int k){
    return k*k + (k+1)*(k+1);
}

// 주어진 k에 대하여 채굴 가능한 금의 개수를 반환
int GetNumOfGold(int row, int col, int k){
    int num_of_gold = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(abs(row-i)+abs(col-j) <= k)
                num_of_fold += grid[i][j];
        }
    }
    return num_of_gold;
}

int main(){
    int max_gold = 0;

    // 입력
    cin >> n >> m;
    for(int row=0; row<n; row++){
        for(int col=0; col<n; col++)
            cin>>grid[row][col];
    }

    // 격자의 각 위치가 마름모의 중앙일 때 채굴 가능한 금의 개수를 구하기
    for(int row=0; row<n; row++){
        for(int col=0; col<n; col++){
            for(int k=0; k<=2*(n-1); k++){
                int num_of_gold = GetNumOfGold(row, col, k);

                // 손해를 보지 않으면서 채굴할 수 있는 최대 금의 개수를 저장
                if(num_of_gold*m >= GetArea(k))
                    max_gold = max(max_gold, num_of_gold);
            }
        }
    }
    cout<<max_gold;
}
