/*
 * 24.04.14
 * 실수1: 기사들을 나타내는 map을 채울 때 탈락한 기사들도 채워버려서 틀림
 * 실수2: 인자에서 d는 방향인데, 지역변수에서 데미지를 나타낼 때 d로 써서 틀림
 * 실수3: 빈칸을 만난 것을 처리하기 전에 벽을 만난 것을 먼저 처리해주었어야 함
*/
#include <iostream>
#include <tuple>
#include <queue>
#include <vector>

#define MAX_L 40
#define MAX_N 30

using namespace std;

int L, N, Q;    // L: 격자 크기, N: 기사들 수, Q: 왕의 명령
int grid[MAX_L][MAX_L]; // 0: 빈칸, 1: 함정, 2: 벽
int kgrid[MAX_L][MAX_L];    // 기사들을 표시하는 격자
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};   // 상우하좌
tuple<int, int, int, int, int, int> knights[MAX_N];    // knights[i]: i번 기사의 (위치),(영역),(체력),(데미지)
bool IsEliminated[MAX_N];   // i번 기사가 탈락했는지 여부

queue<pair<int, int> > q;   // 탐색을 위한 큐
bool selected[MAX_N];

void Init(){   // 입력을 받고 초기화하는 함수
    cin >> L >> N >> Q; // L: 격자 크기, N: 기사들 수, Q: 왕의 명령
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            cin >> grid[i][j];
        }
    }
    for(int i=0; i<N; i++){ // N명의 기사들의 위치, 영역, 초기 체력 입력 받기
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        knights[i] = make_tuple(r-1, c-1, h, w, k, 0);
    }
}

void Initialize(){
    while(!q.empty())           // 큐 비우기
        q.pop();
    
    for(int i=0; i<L; i++)      // 기사 격자 초기화하기
        for(int j=0; j<L; j++)
            kgrid[i][j] = -1;
    
    for(int i=0; i<N; i++){     // N명의 기사들을 차례로 보기
        selected[i] = false;    // 이번 턴에 선택되었다는 것 false로 표기
        int r, c, h, w;
        tie(r, c, h, w, ignore, ignore) = knights[i];
        if(IsEliminated[i]) continue;
        for(int x=r; x<r+h; x++){
            for(int y=c; y<c+w; y++)
                kgrid[x][y] = i;    // 기사를 격자에 표기하기
        }        
    }
}

bool InRange(int x, int y){     // (x, y)가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < L && 0 <= y && y < L;
}

bool FindConnectedKnights(int idx, int d){
    bool CanPush = true;
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        int cx = curr.first, cy = curr.second;

        // 이제 curr위치에서 d방향으로 계속 가보기
        while(true){
            int nx = cx + dirs[d][0], ny = cy + dirs[d][1]; // 다음 위치
            // 만약 벽을 만났다면
            if(grid[nx][ny] == 2 || !InRange(nx, ny)){
                CanPush = false;
                break;
            }
            // 만약 해당 방향으로 갔는데 빈칸이라면
            else if(kgrid[nx][ny] == -1){
                break;  // 이제 이 줄은 탐색 끝
            }
            // 기사 영역을 만났다면
            else if(kgrid[nx][ny] >= 0){
                if(kgrid[nx][ny] != -1 && !selected[kgrid[nx][ny]]){
                    selected[kgrid[nx][ny]] = true;
                    int nr, nc, nh, nw;
                    tie(nr, nc, nh, nw, ignore, ignore) = knights[kgrid[nx][ny]];
                    for(int x=nr; x < nr+nh; x++){
                        for(int y=nc; y < nc+nw; y++){
                            q.push(make_pair(x, y));
                        }
                    } 
                }
                cx = nx, cy = ny;
            }
        }
        if(!CanPush)
            break;
        
    }
    return CanPush;
}

void MoveKnights(int idx, int d){   // idx번 기사를 d방향으로 한 칸 미는 함수
    // Step 1. idx와 붙어있는 기사들 찾기
    int r, c, h, w, k;
    tie(r, c, h, w, k, ignore) = knights[idx];

    selected[idx] = true;
    for(int x=r; x<r+h; x++){
        for(int y=c; y<c+w; y++){
            q.push(make_pair(x, y));
            bool Movable = FindConnectedKnights(idx, d);    // d방향으로 이어져 있는 기사 찾기
            if(!Movable)    return;
        }
    }
    // Step 2. selected에 있는 기사들 밀치고 피해 입히기

    for(int i=0; i<N; i++){
        if(selected[i]){
            int r, c, h, w, k, dmg;
            tie(r, c, h, w, k, dmg) = knights[i];
            r = r + dirs[d][0], c = c + dirs[d][1];

            if(i != idx){
                // 데미지 입히기
                for(int x=r; x < r+h; x++){
                    for(int y=c; y < c+w; y++){
                        if(grid[x][y] == 1){
                            k--;
                            dmg++;
                        }
                    }
                }
            }

            knights[i] = make_tuple(r, c, h, w, k, dmg);
            if(k <= 0)
                IsEliminated[i] = true;

        }
            
    }
    
}

void Output(){  // 생존한 기사들이 받은 총 데미지를 출력하는 함수
    int ans = 0;
    for(int i=0; i<N; i++){
        if(!IsEliminated[i]){
            int cur_damage;
            tie(ignore, ignore, ignore, ignore, ignore, cur_damage) = knights[i];
            ans += cur_damage;
        }
    }
    cout << ans << '\n';
}


int main() {
    // 입력 받기:
    Init();    
    // Q개의 왕의 명령 수행하기
    for(int i=0; i<Q; i++){
        int idx, d;
        cin >> idx >> d;
        if(IsEliminated[idx-1]) continue;
        Initialize();

        MoveKnights(idx-1, d);

            

    }
    // 출력하기
    Output();
    return 0;
}
