/*
 * 2024.02.13
 * 내 풀이
 * 연쇄적으로 미는 부분을 구현하다 꼬여서 풀이를 참조함
 * 체스판에서 탈락한 기사도 계속 영역을 차지하게 돼서 틀림
*/
#include <iostream>
#include <queue>
#define MAX_L 55
#define MAX_N 55
using namespace std;
int l, n, q;        // l: 체스판 크기, n: 기사들 명수, q: 왕 명령 개수    
int original_map[MAX_L][MAX_L];
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};    // 위, 오른쪽, 아래쪽, 왼쪽
struct Knight{
    int idx;    // knight 번호
    int r, c;   // knight 위치
    int h, w;   // knight 영역 크기
    int k;      // knight 체력
    int damage; // 입은 데미지

    void fill(int map[][MAX_L]){
        if(k <= 0) return;
        for(int i=r; i<r+h; i++)
            for(int j=c; j<c+w; j++)
                map[i][j] = idx;
    }


}knights[MAX_N+1];

void Input(){
    cin >> l >> n >> q;
    for(int i=0; i<l; i++){
        for(int j=0; j<l; j++){
            cin >> original_map[i][j];
        }
    }
    for(int i=1; i<=n; i++){
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        knights[i] = {i, r-1, c-1, h, w, k, 0}; // knight 정보 넣기
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < l && 0 <= y && y < l;
}

void do_Command(int start_id, int d){   // id번 기사를 d번 방향으로 연쇄적으로 미는 함수
    // 한 번 명령을 수행할 때마다 새로 기사들 맵 설정
    int knight_map[MAX_L][MAX_L] = {0,};
    for(int i=1; i<=n; i++){
        knights[i].fill(knight_map);    // 기사들 번호로 채우기
    }

    bool moving[MAX_N+1] = {false,};
    queue<int> q;   // start_id를 포함하여 밀리는 기사를 담는 큐
    moving[start_id] = true;
    q.push(start_id);

    while(!q.empty()){
        int cur_id = q.front(); q.pop();
        for(int i = knights[cur_id].r; i < knights[cur_id].r + knights[cur_id].h; i++){
            for(int j = knights[cur_id].c; j < knights[cur_id].c + knights[cur_id].w; j++){
                // (i,j)는 cur_id 기사의 영역
                int r = i, c = j;
                while(true){
                    r += dirs[d][0]; c += dirs[d][1];

                    if(!InRange(r,c)){  // 만약 범위를 벗어나면 벽이므로 움직이지 못함
                        return;
                    }
                    if(knight_map[r][c] == 0){  // 만약 빈 곳이라면
                        if(original_map[r][c] == 2){
                            // 그런데 만약 그곳이 벽이라면
                            return;     // 더이상 움직이지 못함
                        }
                        // 벽이 아니라면
                        break; // 해당 방향으로 이제 갈 수 있으니 탐색 마침
                    }
                    // 이제 범위안에 있으면서 기사가 있는 곳임
                    if(!moving[knight_map[r][c]]){
                        // 처음 만난 기사라면

                        moving[knight_map[r][c]] = true;
                        q.push(knight_map[r][c]);   // 큐에 넣어주기
                    }
                }
            }
        }
    }

    // 이제 데미지 입히기
    // 1. 먼저 이동시키기
    for(int i=1; i<=n; i++){
        if(moving[i]){
            knights[i].r += dirs[d][0];
            knights[i].c += dirs[d][1];
        }
    }

    // 2. 기사들 모두 밀린 이후에 데미지 입음
    for(int i=1; i<=n; i++){
        if(i == start_id) continue;     // 처음 명령 받은 기사는 데미지를 입지 않음
        if(moving[i]){
            for(int x=knights[i].r; x < knights[i].r + knights[i].h; x++){
                for(int y=knights[i].c; y < knights[i].c + knights[i].w; y++){

                    if(original_map[x][y] == 1){
                        // 만약 함정이 있다면
                        knights[i].k--;         // 체력 감소
                        knights[i].damage++;    // 데미지 증가 
                    }
                }
            }
        }
    }

}

void Progress(){
    while(q--){
        int i, d;
        cin >> i >> d;
        // 체스판에 있는 기사는 명령을 수행
        if(knights[i].k <= 0){
            continue;
        }
        do_Command(i, d);
    }
}

void Output(){
    int result = 0;
    for(int i=1; i<=n; i++){
        if(knights[i].k > 0){
            result += knights[i].damage;
        }
    }
    cout << result;
}
int main() {
    // 입력받기
    Input();

    // 왕의 명령 수행하기
    Progress();

    // 출력하기
    Output();
    return 0;
}