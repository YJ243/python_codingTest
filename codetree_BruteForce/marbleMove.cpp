/*
 * 2024.2.6
 * 어렵지 않은 구현 문제인데 자꾸 실수를 한다.
 * 이런 문제를 많이 풀어서 내가 어디서 실수를 하는지 꼭 확인하자!
 * 실수 1: GetDirectionIdx에서 인덱스를 잘못 지정함
 * 실수 2: GetDirectionIdx를 안부르고 char변수를 넘겨줬었음
 * 실수 3: 방향을 바꾸는데에는 시간이 전혀 소요되지 않는데, 이전 문제처럼 생각해서 시간이 소요된다고 문제를 풀었음
 * 꼼꼼하게 잘 읽고!!! 문제 푼 다음 모든 조건을 다 넣었는지 하나씩 확인해서 실수를 줄이기 
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

#define MAX_N 50

using namespace std;
int n, m, t, k;     // n: 격자 크기, m: 구슬 개수, t: 시간, k: 살아남을 수 있는 최대 구슬 수

vector<tuple<int, int, int> > marble[MAX_N][MAX_N];         // 구슬의 정보
vector<tuple<int, int, int> > next_marble[MAX_N][MAX_N];    // 중간 이동을 위한 배열
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};    // 상<->하, 좌<->우 (d+2)%4

int GetDirectionIdx(char d){    // 입력받은 방향에 대해서 인덱스를 반환하는 함수 
    int ret;
    if(d == 'U') ret = 0;
    else if(d == 'R') ret = 1;
    else if(d == 'D') ret = 2;
    else ret = 3;

    return ret;
}

void Initialize_next(){     // 중간 계산을 저장하는 배열 초기화
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            next_marble[i][j].clear();
        }
    }
}

bool InRange(int x, int y){     // (x,y)가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int x, int y){    // (x,y)에 있는 구슬을 옮기기
    for(int i=0; i<(int)marble[x][y].size(); i++){  // (x,y)에 있는 구슬을 모두 보면서 
        int v, id, d;   // 속도, 구슬 번호, 이동 방향
        tie(v, id, d) = marble[x][y][i];
        
        int curX=x, curY=y;     // 현재 칸을 curX, curY로
        for(int move=0; move<v; move++){ // v 속도만큼 움직이기
            int nx = curX+dirs[d][0], ny = curY+dirs[d][1];
            if(InRange(nx,ny)){
                // 범위 안에 있다면 좌표 업데이트
                curX = nx, curY = ny;
            }
            else{
                // 범위 안에 없다면 방향바꾸고 좌표 업데이트하기
                // 방향을 바꾸는 데에는 시간이 전혀 소요되지 않음
                d = (d+2) % 4;
                curX += dirs[d][0]; curY += dirs[d][1];
            }
        }
        next_marble[curX][curY].push_back(make_tuple(v, id, d));
    }
}

void RemoveLowPriority(int x, int y){   // (x,y)에 있는 구슬 중 k개만 빼고 우선순위가 낮은 애들 제거하기
    // 1. 속도, 인덱스 순으로 내림차순 정렬하기
    sort(next_marble[x][y].begin(), next_marble[x][y].end(), greater<tuple<int, int, int> >());
    
    // 2. 우선순위가 낮은 애들 뽑아서 제거하기
    int cnt = (int)next_marble[x][y].size() - k;
    while(cnt--){
        next_marble[x][y].pop_back();
    }
}

void Simulate(){
    // 1. 이동을 하기 전 next 배열 초기화
    Initialize_next();

    // 2. 구슬 이동
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(marble[i][j].size() > 0){
                // 만약 해당 칸에 구슬이 있다면
                Move(i,j);  // 이동시키기
                marble[i][j].clear(); // 원래 vector는 초기화시키기
            }
        }
    }

    // 3. 모두 움직이고 난 후, 사라질 구슬 탐색해서 없애기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(next_marble[i][j].size() > k){
                // k개보다 많다면
                RemoveLowPriority(i,j);
            }
        }
    }

    // 4. 원래 배열로 옮기기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(next_marble[i][j].size() > 0)
                for(int l=0; l<(int)next_marble[i][j].size(); l++){
                    int v, id, d;
                    tie(v, id, d) = next_marble[i][j][l];
                    marble[i][j].push_back(make_tuple(v, id, d));
                }
        }
    }
}

int main() {
    // 변수 선언 및 입력:
    cin >> n >> m >> t >> k;    // n: 격자 크기, m: 구슬 개수, t: 시간, k: 한 칸에 있을 수 있는 구슬 개수
    for(int i=0; i<m; i++){     // m개의 구슬 입력받기
        int r, c, v; char d;    // (r,c)에서 d방향으로 속도v로 이동 중
        cin >> r >> c >> d >> v;
        // 이후에 속도, 구슬 번호가 큰 순으로 우선순위가 높게 매겨지니까 순서는 아래와 같이 저장
        marble[r-1][c-1].push_back(make_tuple(v, i+1, GetDirectionIdx(d)));   // 구슬 위치에 (속도, 구슬 번호, 이동방향) 저장
    }

    // t초에 대해서 시뮬레이션 진행
    for(int time_val=1; time_val<=t; time_val++){
        Simulate();     // 시뮬레이션 시작
    }

    // 남아있는 구슬의 개수 구하기
    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 만약 해당 칸에 구슬이 있다면
            if(marble[i][j].size() > 0)
                // 그 안에 있는 구슬 개수만큼 저장
                ans += (int)marble[i][j].size();
        }
    }

    cout << ans << '\n';
    return 0;
}