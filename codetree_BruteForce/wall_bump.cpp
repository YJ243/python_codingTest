/*
 * 2024.02.06
 * 자잘한 실수가 많아서 계속 틀림
 * 최대 몇 번 수행해야 하는지를 계산하지 못함(MAX_N*2) : 2/5
 * 1. 각 테스트케이스마다 marble 함수를 초기화하지 않았음
 * 2. 구슬이 2개 이상이면 없애는 것을 나중에 틀리고 넣음 => 코드짜고 문제 읽으면서 빠진 조건 없는지 다시한 번 확인하기
 * 3. 방향을 바꿔줄 때, 방향만 바꾸지 않고 위치도 한꺼번에 바꿔서 틀림
 * 시간복잡도: 총 T개의 테스트케이스에 대해 2*n번 구슬을 움직이고 충돌하는지 확인
 * 구슬을 움직이기 위해 모든 격자 칸을 한 번씩 보게 되므로 O(N^2),
 * 충돌한 구슬들을 찾아 지워주는 작업도 모든 격자 칸을 한 번씩만 보면 되니 O(N&2)
 * 총 시간복잡도: O(T*N^3)
*/

#include <iostream>
#define MAX_N 50
using namespace std;

int T, n, m;
pair<int, int> marble[MAX_N][MAX_N];       // 구슬 개수와 방향 정보
pair<int, int> next_marble[MAX_N][MAX_N];   // 중간 이동을 저장하는 배열
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};   // 상(0)<->하(2), 좌(3)<->우(1)

int getDirection(char d){       // 입력받은 방향에 대해서 인덱스를 반환하는 함수
    int ret;
    if(d == 'U') ret = 0;
    else if(d == 'R') ret = 1;
    else if(d == 'D') ret = 2;
    else ret = 3;
    return ret; 
}

void Initialize_next(){             // 중간 이동 정보를 저장하는 배열 초기화
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_marble[i][j].first = 0, next_marble[i][j].second = 0;
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int x, int y, int d){     // (x,y)에 있는 구슬을 d 방향으로 이동시키는 함수
    int nx = x+dirs[d][0], ny = y+dirs[d][1];   // (x,y)에서 d방향으로 움직인 위치
    
    // 다음 위치가 범위 안에 있다면
    if(InRange(nx,ny)){
        // 다음 배열에 정보 담기
        next_marble[nx][ny].first++;        // 구슬 개수 증가
        next_marble[nx][ny].second = d;     // 현재 방향 정보 담기, 만약 구슬이 하나라면 그 방향으로 나중에 이동, 구슬이 여러개라면 없앨 것이니 
    }
    else{
        // 방향을 바꿔주기
        int next_d = (d+2)%4;   // 반대 방향으로 바꿔주기
        next_marble[x][y].first++;
        next_marble[x][y].second = next_d;
    }
}

void Simulate(){
    // 0. next_marble 초기화
    Initialize_next();

    // 1. 전체 칸을 보면서 구슬이 있다면 이동시키기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(marble[i][j].first == 1){
                Move(i, j, marble[i][j].second);
            }
        }
    }

    // 2. 구슬이 2개 이상 있는 칸은 구슬 없애기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(next_marble[i][j].first >= 2){
                next_marble[i][j].first = 0, next_marble[i][j].second = 0;
            }
        }
    }

    // 3. 원래 marble 배열로 옮기기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            marble[i][j].first = next_marble[i][j].first, marble[i][j].second = next_marble[i][j].second;
        }
    }
}

void Initialize_marble(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            marble[i][j].first = 0, marble[i][j].second = 0;
}

int main() {
    cin >> T;   // 테스트 케이스 수 입력받기
    while(T--){     // 시간복잡도 O(T*n*n*n) = O(12500000)
        Initialize_marble();
        cin >> n >> m;  // n: 격자 칸수, m: 구슬 개수
        
        for(int i=0; i<m; i++){
            int x, y; char d;
            cin >> x >> y >> d;
            marble[x-1][y-1] = make_pair(1, getDirection(d));   // 구슬 개수 1개, 방향 정보 저장
        }

        int test_cnt = n*2;
        while(test_cnt--){      // 아주 오랜 시간이 흐르도록
            // 시뮬레이션 진행
            Simulate();
        }
        // 남아있는 구슬의 수 출력
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(marble[i][j].first == 1)
                    ans++;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}