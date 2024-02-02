/*
 * 2024.1.26
 * 내 풀이
*/
#include <iostream>
#include <vector>
#define MAX_N 100
#define ASCII_NUM 128
using namespace std;

int n, m, k;                    // n: 격자 크기, m: 사과 개수, k: 뱀 방향 변환 횟수
vector<pair<int, int> > snake;  // 뱀의 연결 관계를 저장
bool isApple[MAX_N+1][MAX_N+1]; // 해당 칸에 사과가 들어있는지 확인
// 방향 정보, 위/아래/오/왼 방향대로 0,1,2,3 저장
int directions[ASCII_NUM];
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,1,-1};
int ans;

bool InRange(int x, int y){
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

bool IsOverlapped(pair<int, int> next_head){    // next_head가 뱀의 몸통 부분과 겹치는지 확인
    for(int i=0; i<(int)snake.size(); i++){
        int cx = snake[i].first, cy = snake[i].second;
        if(cx == next_head.first && cy == next_head.second)
            return true;
    }
    return false;
}

bool Simulate(int move_dir, int dist){      // move_dir 방향으로 dist만큼 움직이는 함수
    int move_dist = dist;
    while(move_dist--){
        ans++;
        pair<int, int> head = snake.front();
        //cout << head.first << ' ' <<head.second << '\n';
        int nx = head.first + dx[move_dir], ny = head.second + dy[move_dir];    // 머리가 움직일 다음 위치

        // 1. 만약 머리가 움직일 곳이 범위를 벗어나면 false 리턴
        if(!InRange(nx, ny))    return false;
        // 2. 범위 안이라면
        // 2-1. 만약 그곳에 사과가 있다면
        if(isApple[nx][ny]){
            isApple[nx][ny] = false;    // 사과 먹었다고 표시
            snake.insert(snake.begin(), make_pair(nx,ny));

        }
        // 2-2. 만약 사과가 없다면
        else{
            // 1. 먼저 꼬리를 빼주기
            pair<int, int> tail = snake.back(); // 꼬리 위치
            snake.pop_back();   // 맨 뒤에 꼬리 빼주기
            // 2. 만약 겹친다면 false 리턴
            if(IsOverlapped(make_pair(nx,ny))){
                return false;
            }
            // 겹치지 않는다면 vector에 넣기
            snake.insert(snake.begin(), make_pair(nx,ny));
        }

    }
    return true;
}

int main(){
    // 입력:
    cin >> n >> m >> k;
    for(int i=0; i<m; i++){
        int x, y;
        cin >> x >> y;
        isApple[x][y] = true;
    }
    // 방향 정보 저장
    directions['U'] = 0;
    directions['D'] = 1;
    directions['R'] = 2;
    directions['L'] = 3;
    snake.push_back(make_pair(1,1));    // 뱀은 처음에 좌측 상단 (1,1)에 길이 1의 상태로 있음

    while(k--){
        char d; int p;
        cin >> d >> p;
        int move_dir = directions[d];
        if(!Simulate(move_dir, p)){     // move_dir 방향으로 p만큼 움직이지 못한다면
            break;                      // 반복문 빠져나가기
        }
    }
    
    // 출력:
    cout << ans;    
    return 0;
}