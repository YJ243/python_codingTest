/*
 * 2024.02.08
 * 벽이 없는 충돌 실험
 * 실수 1: 좌표평면을 격자로 바꿀 때 MAX_XY+1까지인데, +1을 못봐서 계속 틀렸었음
 * 실수 2: 격자판을 초기화하는 위치를 제대로 잡지 못함, 매 이동 끝에 다시 -1로 바꿔주어야 함
 * 실수 3: 맨 처음에 (x,y)를 좌표평면처럼 생각해서 방향을 잘못 씀
 * 실수 4: else if(next_marble_numbers[nx][ny] > 0) 여기서 그냥 else로 했더니 틀림. 0이 잡혀서
*/
#include <iostream>
#include <vector>
#include <tuple>

#define ASCII_NUM 128
#define MAX_XY 4000
#define OFFSET 2000
#define BLANK -1

using namespace std;

int T, N;                                           // T: 테스트 케이스 개수, N: 구슬 개수
int elapsed_time;                                   // 진행한 시간                                   
int last_collision_time;                            // 마지막으로 충돌한 시간
int dirIdx[ASCII_NUM];                              // 입력으로 들어온 char를 방향 인덱스로 바꿔주는 배열
int next_marble_numbers[MAX_XY+2][MAX_XY+2];        // 구슬의 다음 위치를 담고 있는 배열
typedef tuple<int, int, int, int, int> marble;      // 구슬 정보: (x,y), w, d, id
vector<marble> cur_marble;                          // 현재 구슬 배열
vector<marble> next_marble;                         // 다음 구슬 배열
int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};       // u, d, r, l (x,y)로 보아야 함!

void Initialize(){          // 구슬의 다음 위치 배열 초기화하는 함수
    for(int i=0; i<=MAX_XY; i++){
        for(int j=0; j<=MAX_XY; j++){
            next_marble_numbers[i][j] = BLANK;
        }
    }
}

void collide(int x, int y, marble new_m){     // (x,y) 자리에서 원래 있던 구슬과 새로운 구슬 new_id 처리하기
    int nw, nd, nid;
    tie(ignore, ignore,nw,nd,nid) = new_m;      // 새로운 구슬의 무게, 방향, 번호 담기

    int old_id = next_marble_numbers[x][y];         // 이동하려는 곳에 원래 위치해 있는 구슬의 번호
    // 현재(current) 다음 구슬의 목록을 확인하면서
    int cx, cy, cw, cd, cid;                
    for(int i=0; i<(int)next_marble.size(); i++){
        tie(cx, cy, cw, cd, cid) = next_marble[i];
        if(cid == old_id){      // 현재 보고 있는 위치의 구슬 정보
            if(nw > cw || (nw == cw && nid > cid)){
                // 새로 들어갈 애가 더 우선순위가 높다면
                next_marble.erase(next_marble.begin()+i);           // 다음 구슬 배열에서 원래 있던 구슬 제거
                next_marble_numbers[x][y] = nid;                    // 그 위치에 새로운 구슬 인덱스 넣기
                next_marble.push_back(make_tuple(x,y,nw,nd,nid));   // 다음 구슬 배열에 새로운 구슬 정보 넣기
            }
            break;
        }
    }
}

void Move(){        // 현재 있는 구슬을 한칸씩 옮겨주는 함수
    // 현재 남아있는 모든 구슬을 하나씩 확인하기
    for(int i=0; i<(int)cur_marble.size(); i++){
        int x, y, w, d, id;
        tie(x, y, w, d, id) = cur_marble[i];        // 현재 이동하려는 구슬 정보
        int nx = x+dirs[d][0], ny = y+dirs[d][1];   // 그 구슬이 이동하려는 다음 위치
        // 만약 이동하려는 위치가 범위를 벗어난다며 무시
        if(nx < 0 || nx > MAX_XY+1 || y < 0 || ny > MAX_XY+1) {
            continue;     
        }
        // 만약 그 다음에 이동할 위치가 비어있다면
        if(next_marble_numbers[nx][ny] == BLANK){
            next_marble_numbers[nx][ny] = id;                   // 해당 칸에 구슬 번호 집어넣기
            next_marble.push_back(make_tuple(nx,ny,w,d,id));    // 다음 구슬 목록에 추가하기
        }
        // 만약 그 다음에 이동할 위치에 다른 번호가 있다면
        else if(next_marble_numbers[nx][ny] > 0){
            last_collision_time = elapsed_time;     // 충돌 시간 업데이트
            collide(nx,ny,cur_marble[i]);           // (nx,ny) 자리에서 원래 있는 구슬과 새로운 구슬과의 충돌 처리
        }   
    }
}

void Simulate(){        // 시뮬레이션을 진행하는 함수
    int turn_cnt = MAX_XY;      // 이동은 4000번까지만 진행하기
    // 0. 구슬 번호가 어디있는지 나타내는 배열 초기화
    Initialize();
    while(turn_cnt--){
        elapsed_time++;
        // 1. 모든 구슬을 하나씩 보면서 이동시키기
        Move();

        // 2. 구슬 번호를 나타내는 배열을 초기화 배열로 바꿔주기
        for(int i=0; i<(int)next_marble.size(); i++){
            int x, y, w, d, id;
            tie(x, y, w, d, id) = next_marble[i];
            next_marble_numbers[x][y] = BLANK;
        }
        // 3. cur_marble에 next_marble 복사하기
        cur_marble = next_marble;
        // 4. 다시 다음 구슬을 담는 배열 비우기
        next_marble.clear();
    }
}

int main() {
    dirIdx['U'] = 0;
    dirIdx['D'] = 1;
    dirIdx['R'] = 2;
    dirIdx['L'] = 3;
    cin >> T;   // 테스트 케이스 수 입력받기
    while(T--){
        cur_marble.clear(); // 현재 구슬 정보 초기화
        elapsed_time = 0;
        last_collision_time = -1;
        // 구슬 개수
        cin >> N;
        // 해당 구슬들 정보 입력받기
        for(int i=1; i<=N; i++){
            int x, y, w; char d;
            cin >> x >> y >> w >> d;
            x = x*2 + OFFSET, y = y*2 + OFFSET;
            cur_marble.push_back(make_tuple(x, y, w, dirIdx[d], i));    // (x,y), 무게, 방향, 번호 집어넣기            
        }
        // 시뮬레이션 시작
        Simulate();

        cout << last_collision_time << '\n';
    }
    return 0;
}