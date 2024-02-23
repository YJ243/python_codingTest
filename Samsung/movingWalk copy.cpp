/*
 * 24.02.22
 * 불안한 무빙 워크
 * 해설 풀이
 * 시간복잡도: 각 단계에서 모든 칸을 확인하는데 최대 O(N^2)의 시간이 걸리고, 이를 안정성이 0이 되기까지 반복
 * 단계의 횟수는 O(N)에 비례하므로, 최종적인 시간복잡도는 O(N^3)
*/

#include <iostream>
#include <tuple>

#define MAX_N 100

using namespace std;

int n, k;

pair<int, bool> u[MAX_N];
pair<int, bool> d[MAX_N];

void Shift(){
    pair<int, bool> temp = u[n-1];
    for(int i=n-1; i >= 1; i--)
        u[i] = u[i-1];
    u[0] = d[n-1];

    for(int i=n-1; i >= 1; i--)
        d[i] = d[i-1];
    d[0] = temp;
}

bool CanGo(int idx){    // 다음 번인 idx로 이동이 가능한지 확인하는 함수
    // 밖으로 나가는 것은 항상 가능하다
    if(idx == n)
        return true;
    
    // 안정성이 0보다 크면서 사람이 없는 경우에만 이동이 가능
    int stability; bool occupied;
    tie(stability, occupied) = u[idx];
    return stability > 0 && !occupied;
}

void Move(int idx){
    // 현재 위치에 있던 사람은 사라진다.
    int curr_stability;
    tie(curr_stability, ignore) = u[idx];
    u[idx] = make_pair(curr_stability, false);

    // 밖으로 나가는 것이 아니라면,
    // 안정성이 1 감소하며, 사람이 추가된다.
    if(idx + 1 < n){
        int next_stability;
        tie(next_stability, ignore) = u[idx+1];
        u[idx+1] = make_pair(next_stability - 1, true);
    }
}

void MoveAll(){
    // 현재 위치에 사람이 있고, 그 다음 위치로 이동이 가능한 경우에만 움직이기
    for(int i=n-1; i>=0; i--){
        bool occupied;
        tie(ignore, occupied) = u[i];
        if(occupied && CanGo(i+1))
            Move(i);
    }
}

void Add(){
    // 안정성이 0보다 크고 사람이 없는 경우에만
    // 첫 번째 위치에 사람을 올려놓습니다.
    int stability; bool occupied;
    tie(stability, occupied) = u[0];
    if(stability > 0 && !occupied)
        u[0] = make_pair(stability - 1, true);
}

void Simulate(){
    // Step 1. 무빙 워크를 한 칸 회전시킨다.
    Shift();

    // Step 2. 사람들을 한 칸씩 앞으로 이동시킨다.
    MoveAll();

    // Step 3. 사람을 새로 올린다.
    Add();

    // Step 4. n번 칸 위치에 사람이 있다면, 즉시 내려준다.
    bool occupied;
    tie(ignore, occupied) = u[n-1];
    if(occupied)
        Move(n-1);
}

bool Done(){
    int unstable_cnt = 0;
    for(int i=0; i<n; i++){
        int stability;
        tie(stability, ignore) = u[i];
        if(!stability) unstable_cnt++;
    }
    for(int i=0; i<n; i++){
        int stability;
        tie(stability, ignore) = d[i];
        if(!stability) unstable_cnt++;
    }

    return unstable_cnt >= k;
}

int main(){
    cin >> n >> k;

    for(int i=0; i<n; i++){
        int stability;
        cin >> stability;
        u[i] = make_pair(stability, false);
    }
    for(int i=0; i<n; i++){
        int stability;
        cin >> stability;
        d[i] = make_pair(stability, false);
    }

    int trial = 0;
    while(!Done()){
        Simulate();
        trial++;
    }
    cout << trial;
    return 0;
}