/*
 * 2024.02.08
 * 벽이 없는 충돌 실험
 * 실수 1: 좌표평면을 격자로 바꿀 때 MAX_XY+1까지인데, +1을 못봐서 계속 틀렸었음
 * 실수 2: 격자판을 초기화하는 위치를 제대로 잡지 못함, 매 이동 끝에 다시 -1로 바꿔주어야 함
 * 실수 3: 맨 처음에 (x,y)를 좌표평면처럼 생각해서 방향을 잘못 씀
 * 실수 4: else if(next_marble_numbers[nx][ny] > 0) 여기서 그냥 else로 했더니 틀림. 0이 잡혀서
*/
#include <iostream>
#include <tuple>
#include <vector>

#define DIR_NUM 4
#define OFFSET 2000
#define COORD_SIZE 4000
#define ASCII_NUM 128
#define BLANK -1

using namespace std;

typedef tuple<int, int, int, int, int> Marble;

// 전역 변수 선언:
int t, n;

int mapper[ASCII_NUM];

int dx[DIR_NUM] = {0,1,-1,0};
int dy[DIR_NUM] = {1,0,0,-1};

int curr_time;
int last_collision_time;

vector<Marble> marbles;
vector<Marble> next_marbles;
int next_marble_index[COORD_SIZE + 1][COORD_SIZE + 1];

// 해당 구슬이 1초 후에 어디 위치에 있는지를 구해 상태를 반환
Marble Move(Marble marble){

}

// 해당 구슬과 충돌이 일어나는 구슬이 있는지 확인
// 있다면 해당 구슬의 index를 반환하고, 없다면 BLANK를 반환
// 이는 next_marble_index를 활용하면 O(1)에 바로 가능
int FindDuplicateMarble(Marble marble){

}

// 두 구슬이 같은 위치에서 충돌했을 경우
// 살아남는 구슬을 반환
Marble Collide(Marble marble1, Marble marble2){

}

// 구슬이 이미 (0,0) ~ (COORD_SIZE, COORD_SIZE) 사이를 벗어났다면
// 더 이상 충돌이 일어나지 않으므로
// Active Coordinate를 벗어났다고 판단
bool OutOfActiveCoordinate(Marble marble){

}

// 그 다음 구슬의 목록에 반영
void PushNextMarble(Marble marble){

}

// 모든 구슬들을 한 칸씩 움직이는 시뮬레이션을 진행
void Simulate(){
    for(int i=0; i<(int)marbles.size(); i++){
        // Step 1. 각 구슬에 대해 한 칸 움직인 이후의 위치를 받아오기
        Marble next_marble = Move(marbles[i]);

        // Step 2. 그 다음 구슬의 목록에 반영하기
        PushNextMarble(next_marble);
    }
    marbles = next_marbles;

    // 그 다음 Simulation 때 다시 사용해야 하므로
    // 충돌여부를 빠르게 판단하기 위해 쓰였던 next_marble_index 배열고
    // 다음 구슬의 목록을 기록했던 next_marbles를 미리 초기화해주기
    for(int i=0; i<(int)next_marbles.size(); i++){
        int x, y;
        tie(x, y, ignore, ignore, ignore) = next_marbles[i];
        next_marble_index[x][y] = BLANK;
    }
    next_marbles.clear();
}

int main(){
    mapper['U'] = 0;
    mapper['R'] = 1;
    mapper['L'] = 2;
    mapper['D'] = 3;

    // 테스트 케이스 수 입력:
    cin >> t;

    // 처음에는 구슬이 전혀 놓여있지 않다는 표시로 전부 BLANK로 채워 놓음
    for(int i=0; i<=COORD_SIZE; i++){
        for(int j=0; j <= COORD_SIZE; j++)
            next_marble_index[i][j] = BLANK;
    }

    while(t--){
        // 새로운 테스트 케이스가 시작될 때마다 기존에 사용하던 값들을 초기화해주기
        marbles.clear();
        last_collision_time = -1;

        // 입력:
        cin >> n;
        for(int i=1; i<=n; i++){
            int x, y, weight; char d;
            cin >> x >> y >> weight >> d;

            // 구슬이 움직이는 도중에 충돌하는 문제를 깔끔하게 처리하기 위해
            // 좌표를 2배로 불려 1초에 한 칸씩 이동하는 문제로 바꾸기
            // 이렇게 문제가 바뀌면 따로 구슬이 움직이는 도중 충돌하는 경우를 생각하지 않아도 됨
            x *= 2; y *= 2;

            // 좌표를 전부 양수로 만들어야 동일한 위치에서 충돌이 일어나는지를
            // 판단하는 데 사용할 next_marble_index 배열에
            // 각 구슬의 위치마다 자신의 index를 저장할 수 있으므로
            // 좌표를 전부 양수로 만들기
            // 입력으로 들어올 수 있는 좌표값 중 가장 작은 값이 -2000이므로
            // OFFSET을 2000으로 잡아 전부 더해주기
            // 같은 OFFSET을 모든 구슬에 전부 더해주는 것은 답에 전혀 영향을 미치지 않음
            x += OFFSET; y += OFFSET;
            marbles.push_back(make_tuple(x, y, weight, mapper[d], i));
        }

        // OFFSET이 더해진 구슬들의 처음 위치는 전부
        // (0,0)에서 (4000, 4000) 사이에 있기 때문에
        // COORD SIZE + 1(4001)만큼 이동하면
        // 입력으로 주어진 구슬들이 모두 (0,0) ~ (4000,4000) 영역 밖으로 벗어나게 되므로
        // 더 이상 충돌이 일어나지 않게 됨
        // 따라서 시뮬레이션을 총 COORD_SIZE번 진행하기
        for(int i=1; i<=COORD_SIZE; i++){
            curr_time = i;
            Simulate();
        }

        // 출력:
        cout << last_collision_time << '\n';
    }
    return 0;
}
