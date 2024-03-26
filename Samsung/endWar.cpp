/*
 * 2024.03.25
 * 내 풀이
 * 1시간 30분 걸림
*/

#include <iostream>
#include <climits>
#include <algorithm>

#define MAX_N 20
using namespace std;

int n;
int grid[MAX_N][MAX_N];
int ans = INT_MAX;
int dirs[4][2] = {{-1,1},{-1,-1},{1,-1},{1,1}};     // 1, 2, 3, 4 방향
int tribe[MAX_N][MAX_N];
int tribe_sum[6];
void Input(){       // 입력을 받는 함수
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
}

bool InRange(int x, int y){         // (x,y)가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool Possible(int x, int y, int a, int b){      // (x,y)에서 시작해서 13은 a, 24는 b만큼 움직여서 기울어진 직사각형을 만들 수 있는지 확인하는 함수
    int cx = x, cy = y, cl = 0;
    for(int d=0; d<4; d++){
        if(d % 2 == 0) cl = a;
        else           cl = b;
        for(int i=1; i<=cl; i++){
            int nx = cx + dirs[d][0], ny = cy + dirs[d][1];
            if(!InRange(nx, ny))
                return false;
            cx = nx, cy = ny;
        }
    }
    return true;
}

void Initialize_tribe(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            tribe[i][j] = 0;
    for(int i=0; i<6; i++)
        tribe_sum[i] = 0;
}

int Calc(int x, int y, int a, int b){
    Initialize_tribe();

    pair<int, int> dots[4];
    // 1번 부족 채우기
    int cx = x, cy = y, cl = 0, cv = 1;
    dots[0] = make_pair(cx, cy);
    tribe[cx][cy] = cv;
    for(int d=0; d<4; d++){
        if(d % 2 == 0) cl = a;
        else           cl = b;
        for(int i=1; i<=cl; i++){
            int nx = cx + dirs[d][0], ny = cy + dirs[d][1];
            tribe[nx][ny] = cv;
            cx = nx, cy = ny;
        }
        if(d <= 2)
            dots[d+1] = make_pair(cx,cy);
    }
    
    // 2번 부족 채우기
    for(int i=0; i<dots[3].first; i++){
        for(int j=0; j <= dots[2].second; j++){
            if(tribe[i][j] == 1)
                break;
            tribe[i][j] = 2;
        }
    }
    // 3번 부족 채우기
    for(int i=dots[1].first; i>=0; i--){
        for(int j=n-1; j > dots[2].second; j--){
            if(tribe[i][j] == 1)
                break;
            tribe[i][j] = 3;
        }
    }
    // 4번 부족 채우기
    for(int i=dots[3].first; i < n; i++){
        for(int j=0; j<dots[0].second; j++){
            if(tribe[i][j] == 1)
                break;
            tribe[i][j] = 4;
        }
    }
    // 5번 부족 채우기
    for(int i=n-1; i > dots[1].first; i--){
        for(int j=n-1; j >= dots[0].second; j--){
            if(tribe[i][j] == 1)
                break;
            tribe[i][j] = 5;
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(tribe[i][j] == 0) tribe_sum[1] += grid[i][j];
            for(int k=1; k<=5; k++){
                if(tribe[i][j] == k)
                    tribe_sum[k] += grid[i][j];
            }
        }
    }

    int minS = INT_MAX, maxS = INT_MIN;
    for(int i=1; i<=5; i++){
        minS = min(minS, tribe_sum[i]);
        maxS = max(maxS, tribe_sum[i]);
    }
    
    return maxS - minS;
}

void FindMinDiff(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // (i,j)는 기울어진 직사각형의 시작점
            for(int k=1; k<n; k++){
                for(int l=1; l<n; l++){
                    if(Possible(i,j,k,l)){
                        ans = min(ans, Calc(i, j, k, l));
                    }
                }
            }
        }
    }
}

int main() {
    // 입력:
    Input();

    FindMinDiff();

    // 출력:
    cout << ans;
    return 0;
}
