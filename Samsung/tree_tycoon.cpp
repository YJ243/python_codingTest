/*
 * 2024.02.21
 * 내 풀이
*/

#include <iostream>

#define MAX_N 15
using namespace std;

int n, m;       // n: 격자 크기, m: 리브로수를 키우는 총 년수
int tree[MAX_N][MAX_N];
bool nutrient[MAX_N][MAX_N];
int dirs[8][2] = {{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1}};

void Init(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> tree[i][j];
    for(int i=n-2; i<n; i++)
        for(int j=0; j<2; j++)
            nutrient[i][j] = true;
}

void MoveNutrient(int d, int p){    // 모든 영양분을 d방향으로 p만큼 움직이기
    bool temp[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            temp[i][j] = false;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(nutrient[i][j]){
                // 만약 영양분이 있다면 움직이기
                int nx = (i + dirs[d][0]*p + n * 10) % n;
                int ny = (j + dirs[d][1]*p + n * 10) % n;
                temp[nx][ny] = true;
            }
        }
    }
    // 다시 temp 배열을 원래대로 nutrient에 넣기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            nutrient[i][j] = temp[i][j];

}

void InputNutrient(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(nutrient[i][j]){
                tree[i][j]++;   // 해당 격자에 있는 나무 수 증가시키기
            }
        }
    }


}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){
    return InRange(x, y) && tree[x][y] >= 1;
}

void GrowTree(int x, int y){
    int dir_tree[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};
    int cnt = 0;
    for(int d=0; d<4; d++){
        int nx = x + dir_tree[d][0], ny = y + dir_tree[d][1];
        if(CanGo(nx, ny)){
            cnt++;
        }
    }
    tree[x][y] += cnt;      // 인접한 나무 개수만큼 증가시키기
}

void GrowMoreTree(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(nutrient[i][j]){
                // 영양제가 투입된 나무와 높이가 2 이상인 대각선으로 인접한 나무 개수만큼 더 성장
                GrowTree(i,j);
            }
        }
    }
}

void MakeNutrient(){
    bool temp[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            temp[i][j] = false;
    } 
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(tree[i][j] >= 2 && !nutrient[i][j]){
                tree[i][j] -= 2;
                temp[i][j] = true;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(nutrient[i][j])
                nutrient[i][j] = false;
            nutrient[i][j] = temp[i][j];
        }
    }
}

void Output(){
    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ans += tree[i][j];
        }
    }
    cout << ans << '\n';
}

int main() {
    // 초기 프로그램을 위한 입력과 변수 설정
    Init();
    while(m--){
        int d, p;           // 이동 방향과 이동 칸수 입력받기
        cin >> d >> p;
        d--;
        MoveNutrient(d, p);
        InputNutrient();
        GrowMoreTree();
        MakeNutrient();
    }
    // 출력:
    Output();    
    return 0;
}