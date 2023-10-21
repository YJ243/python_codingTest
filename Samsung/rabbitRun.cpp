/*
2023.10.13
전체 몇번까지 가능한 경우의 수가 나오는지 확인하고, 시간복잡도를 계산해야 한다
*/
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#define NM 2005         // 토끼수는 최대 2000
using namespace std;

struct Rabbit {
    int pid;      // 토끼의 pid와 이동거리
    int x, y;           // 토끼의 좌표: x행  y열
    int jump;           // 토끼가 지금까지 이동한 횟수
    bool operator<(const Rabbit other) const {
        // a < b가 True면 a가 더 우선순위가 작다는 것이고 그건 a의 jump값이 더 크다는 것임
        if (jump != other.jump) return jump > other.jump;
        if (x+y != other.x + other.y) return x + y > other.x+other.y;
        if (x != other.x) return this.x > other.x;
        return this.pid > other.pid;
    }
};

unordered_map<int, int> dist;   // dist[i] := i번 토끼의 이동 거리
unordered_map<int, long long int> score;  // score[i] := i번 토끼의 점수
long long int total_shift;
int N, M, P;
priority_queue<Rabbit> rabbits;

void init(){        // 초기화 함수
    cin >> N >> M >> P;
    for (int i=1; i<=P; i++){
        int pid, dist;
        cin >> pid >> dist;
        rabbits.push({pid, dist, 1, 1, 0})
    }
}

void move_right(int *y, int *d){ // x, y에서 d만큼 오른쪽 이동을 시도. 만약 오른쪽 끝에 도달한다면 멈춤
    if(M-*y >= *d){ // 오른쪽 끝까지의 거리보다 작거나 같게 이동한다면, 바로 이동하기
        *y += *d;
        *d = 0;
    } else {
        *d -= M- *y;
        *y = M;
    }
}
void move_left(int *y, int *d){ // x, y에서 d만큼 왼쪽 이동을 시도. 만약 왼쪽 끝에 도달한다면 멈춤
    if(*y-1 >= *d){ // 왼쪽 끝까지의 거리보다 작거나 같게 이동한다면, 바로 이동하기
        *y -= *d;
        *d = 0;
    } else {
        *d -= *y- 1;
        *y = 1;
    }
}
void move_up(int *x, int *d){ // x, y에서 d만큼 위쪽 이동을 시도. 만위 위쪽 끝에 도달한다면 멈춤
    if(*x-1 >= *d){ // 위쪽 끝까지의 거리보다 작거나 같게 이동한다면, 바로 이동하기
        *x -= *d;
        *d = 0;
    } else {
        *d -= *x-1;
        *x = 1;
    }
}
void move_down(int *x, int *d){ // x, y에서 d만큼 아래쪽 이동을 시도. 만약 아래쪽 끝에 도달한다면 멈춤
    if(N-*x >= *d){ // 아래쪽 끝까지의 거리보다 작거나 같게 이동한다면, 바로 이동하기
        *x += *d;
        *d = 0;
    } else {
        *d -= N- *x;
        *x = N;
    }
}

pair<int, int> getGoal(int cx, int cy, int cd){    // (x,y)에서 d만큼 뛰면 어디로 가야하는지 구하는 함수
    vector<pair<int, int>> goals;

    // 오른쪽으로 이동하기
    {
        int period = (M-1) * 2;
        int x = cx, y = cy;
        int d = cd % period;

        move_right(&y, &d);
        move_left(&y, &d);
        move_right(&y, &d);
        goals.push_back({x,y});
    }
        // 왼쪽으로 이동하기
    {
        int period = (M-1) * 2;
        int x = cx, y = cy;
        int d = cd % period;

        move_left(&y, &d);
        move_right(&y, &d);
        move_left(&y, &d);
        goals.push_back({x,y});
    }
        // 아래쪽으로 이동하기
    {
        int period = (N-1) * 2;
        int x = cx, y = cy;
        int d = cd % period;

        move_down(&y, &d);
        move_up(&y, &d);
        move_down(&y, &d);
        goals.push_back({x,y});
    }
        // 위쪽으로 이동하기
    {
        int period = (N-1) * 2;
        int x = cx, y = cy;
        int d =cd % period;

        move_up(&y, &d);
        move_down(&y, &d);
        move_up(&y, &d);
        goals.push_back({x,y});
    }
    sort(goals.begin(), goals.end(), [](pair<int, int> A, pair<int, int> B){
        if (A.first + A.second != B.first + B.second) return A.first+A.second > B.first + B.second;
        return A.first > B.first;
    });

    return goals[0];
}

void getWinner(unordered_map<int, Rabbit> candidates, int S){
    // candidates: 점수를 받을 가능성이 있는 토끼들
    Rabbit r = (*candidates.begin()).second;
    for (auto it = candidates.begin(); it != candidates.end(); it++){
        Rabbit ot = (*it).second;
        if (r.x + r.y != ot.x + ot.y){
            if (r.x+r.y < ot.x + ot.y)
            r = ot;
        }
        continue;
        if (r.x != ot.x){
            if(r.x < ot.x){
                r = ot;
            }
            continue;
        }
        if(r.pid < ot.pid){
            r = ot; 
        }
    
    }
    score[r.pid] += S; 

}

void rabbit_jump(){     // k번의 점프를 수행할 함수
    int K, S;
    cin >> K >> S;
    unordered_map<int, Rabbit> candidates;      // 한 번이라도 움직인 적이 있는 토끼들
    while (K--){
        // 1. 이번에 점프할 토끼 선정하기, O(log P)
        Rabbit r = rabbits.top();
        rabbits.pop();

        // 2. 해당 토끼가 이동할 위치 선정하기
        pair<int, int> goal = getGoal(r.x, r.y, dist[r.pid]);
        
        // 3. 토끼 이동시키기
        r.x = goal.first, r.y = goal.second;
        r.jump += 1
        candidates[r.pid] = r;        
        rabbits.push(r);
        // 4. 점수 update
        score[r.pid] -= r.x + r.y;  // 이 토끼만 점수가 안 오르게 변경
        total_shift += r.x + r.y;   // 모든 토끼가 r.x + r.y만큼 오른다고 가정
    }
    // S 만큼의 점수를 받을 토끼 선정하기
    getWinner(candidates, S);
}

void rabbit_update(){   // 특정 토끼의 이동거리를 update하는 함수
    int pid, L;
    cin >> pid >> L;
    dist[pid] *= L;     
} 

void best_rabbit(){     // 최고의 토끼를 출력하는 함수
    long long int ans = 0;
    for (auto it = score.begin(); it != score.end(); it++){
        ans = max(ans, it->second);
    }
    cout << ans + total_shift;
}

int main(){
    int Q;
    cin >> Q;
    while (Q--){
        int query_type;
        cin >> query_type;
        if (query_type == 100){
            init();
        } else if (query_type == 200){
            rabbit_jump();
        } else if (query_type == 300){
            rabbit_update();
        } else if (query_type == 400){
            best_rabbit();
        }
        
    }
}