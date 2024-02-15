/*
 * 2024.02.07
 * 벽이 없는 충돌 실험
 * 시간초과가 나옴
 * T번의 테스트 케이스에 대해서 총 1000*4번 움직여야 하며, 구슬이 충돌하는지 확인하는 데
 * 각 구슬들에 대해 다른 구슬들과 위치가 겹치는지 일일이 확인해야 되기 때문에 N^2
 * 따라서 시간복잡도는 O(T*C*N^2)의 시간이 소요됨=> Time Limit (100*4000*100*100)
*/
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define ASCII_NUM 128
#define MAX_XY 1000
using namespace std;
int T;      // 테스트 케이스 개수
int N;      // 구슬의 개수
// 구슬의 정보 저장: (무게, 번호, 위치, 방향, 사라져야 하는지)
vector<tuple<int, int, double, double, int, bool> > marble;
vector<tuple<int, int, double, double, int, bool> > next_marble;
int dir_num[ASCII_NUM];
int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; // 상,우.하,좌
int elapsed_time;   // 충돌이 일어나기까지 지난 시간
int collapse_time;  // 마지막으로 충돌이 일어난 시간

void Move(){    // 현재 좌표평면에 있는 모든 구슬에 대해서 1초마다 움직여주기
    for(int i=0; i<(int)marble.size(); i++){
        int w, id, d; double x, y; bool removed;
        tie(w, id, x, y, d, removed) = marble[i];

        double nx = x+dirs[d][0]*0.5, ny = y+dirs[d][1]*0.5;
        //cout << nx << ' ' << ny << ' ' << x << ' ' << y << '\n';
        marble[i] = make_tuple(w, id, nx, ny, d, removed);
        //cout << id<<"번 구슬 움직였음" << "(" << nx << "," << ny << ")" << d << "방향" << '\n';
    }
}

void CheckOverlapped(){     // 모든 구슬을 보면서 겹치는 것이 있는지 확인, 사라져야 될 구슬은 removed 표시

    for(int i=0; i < (int)marble.size(); i++){
        for(int j=i+1; j<(int)marble.size(); j++){
            int w1, id1, d1; double x1, y1; bool removed1;
            int w2, id2, d2; double x2, y2; bool removed2;
            tie(w1, id1, x1, y1, d1, removed1) = marble[i];
            tie(w2, id2, x2, y2, d2, removed2) = marble[j];
            //cout << "현재는 " << id1<<"번과, " << id2 << "번을 보는 중" << '\n';
            int removed_idx = 0;
            if(removed1 || removed2){   // 만약 둘 중 하나가 삭제되어야 한다면 안봐도 되니까 넘어가기
                continue;
            }
            if(x1 == x2 && y1 == y2){   // 만약 위치가 겹친다면
                //cout << w1 << ' ' << w2 << '\n';
                if(w1 < w2) removed_idx = i;    // 만약 무게가 i가 더 작다면 우선순위가 낮음
                    else if(w1 > w2) removed_idx = j;
                if(w1 == w2 && id1 < id2) removed_idx = i;
                    else if(w1 == w2 && id1 > id2) removed_idx = j;

                if(removed_idx == i){   // 만약 지워야할 인덱스가 i라면
                    //cout << "지워져야 할 인덱스" << id1 << " 남아야 할 인덱스" << id2 << '\n';
                    removed1 = true;
                    marble[i] = make_tuple(w1, id1, x1, y1, d1, removed1);
                }
                else{       // j라면
                    removed2 = true;
                    marble[j] = make_tuple(w2, id2, x2, y2, d2, removed2);
                    //cout << "지워져야 할 인덱스" << id2 << ' ' << removed2 << "남아야 할 인덱스" << id1 << ' ' << removed1 << '\n';
                }
            }
        }
    }

        for(int i=0; i<(int)marble.size(); i++){
        int w, id, d; double x, y; bool removed;
        tie(w, id, x, y, d, removed) = marble[i];
        //cout << id << "번 구슬" << x << ' ' << y << ' ' << removed << '\n';
    }
    
}
void RemoveLowPriority(){   // 현재 구슬이 겹치는게 있다면 우선순위가 낮은 구슬을 지우기
    
    
    // 1. 모든 구슬에 대해서 서로 겹치는지 확인하기
    CheckOverlapped();


    // 2. 모든 구슬에 대해서 만약 지워져야 한다면
    for(int i=0; i<(int)marble.size(); i++){
        int w, id, d; double x, y; bool removed;
        tie(w, id, x, y, d, removed) = marble[i];
        if(!removed){
            // 남아있어야 한다면
            //cout << id << "번은 남아있어야 함" << "무게는: " << w << "removed:"<<removed << '\n';
            next_marble.push_back(make_tuple(w, id, x, y, d, removed));
            
        }
        else{
            // 만약 지워져야하는게 있다면
            // 이번에 충돌이 일어났다는 의미로 collapsed_time 업데이트
            //cout << id<<"번은 이제 사라진다" << "무게는"<<w << '\n';
            collapse_time = elapsed_time;
        }
    }
    
    // 3. next_marble을 원래 구슬 배열로 넣어주기
    marble.clear();
    //cout << marble.size() << ' ' << next_marble.size() << '\n';
    for(int i=0; i<(int)next_marble.size(); i++){
        int w, id, d; double x, y; bool removed;
        tie(w, id, x, y, d, removed) = next_marble[i];

        marble.push_back(make_tuple(w, id, x, y, d, removed));
    }
    next_marble.clear();
}

// 구슬 이동에 대한 시뮬레이션 진행
void Simulate(){Q
    int cnt = MAX_XY*4;
    while(cnt--){
        elapsed_time++;  // 1초 시간 증가
        // 1. 모든 구슬에 대해 1초 움직이기
        Move();


        // 2. 현재 겹치는게 있다면 우선순위 낮은 구슬 지워주기
        RemoveLowPriority();

        //cout << "marble 개수" << marble.size() << '\n';
        
    }
    // 3. 만약 충돌이 전혀 일어나지 않았다면
    if(elapsed_time == MAX_XY*4 && marble.size() == N)
        collapse_time = -1;
}


int main() {
    cin >> T;   // 총 테스트 케이스
    dir_num['U'] = 0;   // 상
    dir_num['R'] = 1;   // 우
    dir_num['D'] = 2;   // 하
    dir_num['L'] = 3;   // 좌

    while(T--){             // 각 테스트 케이스에 걸쳐서
        marble.clear();     // 구슬 정보 초기화
        elapsed_time = 0;   // 시간 초기화
        cin >> N;           // 구슬 정보 입력받기
        for(int i=1; i<=N; i++){
            double x, y;
            int w; char d;
            cin >> x >> y >> w >> d;
            marble.push_back(make_tuple(w, i, x, y, dir_num[d], false));
        }

        // 시뮬레이션 시작
        Simulate();

        // 가장 마지막으로 충돌이 일어난 시간 출력
        cout << collapse_time << '\n';
    }   
    return 0;
}