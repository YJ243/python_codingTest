/*
 * 2023.1.4
 * 한 번에 맞았지만 중간에 실수를 많이 해서 계속 틀렸던 문제
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define NUM_BOMB 3
#define MAX_N 20

using namespace std;

int n;
int grid[MAX_N][MAX_N];         // 1: 폭탄
int tmp[MAX_N][MAX_N];          // 중간에 결과를 저장할 폭탄 격자
int ans;                        // 가장 많이 초토화시킬 수 있는 영역 

vector<pair<int, int> > bomb_loc;   // 폭탄의 좌표(1이 적힌 칸의 좌표)
vector<int> selected_bomb;          // 현재까지 선택한 폭탄 번호
// 3가지 폭탄이 초토화시킬수 있는 지역의 위치
int bomb[NUM_BOMB][5][2] = {
    {{-2,0},{-1,0},{0,0},{1,0},{2,0}},
    {{-1,0},{0,-1},{0,0},{1,0},{0,1}},
    {{-1,-1},{1,-1},{0,0},{1,1},{-1,1}}
    };

void Initialize(){  // 폭탄으로 초토화시키기 전 초기화하는 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            tmp[i][j] = grid[i][j];
        }
    }
}

bool InRange(int x, int y){     // 현재 보고 있는 좌표가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

void do_bomb(){     // 현재 선택된 폭탄들로 초토화시키는 함수
    // 현재 격자 초기화
    Initialize();

    // 폭탄 보면서 초토화시키기
    for(int i=0; i<(int)bomb_loc.size(); i++){
        int x = bomb_loc[i].first, y = bomb_loc[i].second; //  넣어야할 폭탄 위치
        int bomb_num = selected_bomb[i];
        for(int j=0; j<5; j++){
            int bombX = x+bomb[bomb_num][j][0], bombY = y+bomb[bomb_num][j][1];
            if(InRange(bombX, bombY)){
                tmp[bombX][bombY] = 1;
            }
        }
    }
}

void Check(){       // 현재 초토화된 폭탄이 몇 개인지 확인
    do_bomb();      // 먼저 폭탄으로 초토화시키기

    int cur_cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(tmp[i][j] == 1) cur_cnt++;  
        }
    }
    ans = max(ans, cur_cnt);
}


void Choose(int n){   // n번째 폭탄을 선택하는 함수
    if(n == bomb_loc.size()){   // 만약 폭탄 위치에 들어갈 폭탄을 모두 선택했다면
        Check();                // 초토화시킨 영역 확인
        return;
    }

    for(int i=0; i<NUM_BOMB; i++){
        selected_bomb.push_back(i);
        Choose(n+1);
        selected_bomb.pop_back();
    }

}

int main() {
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            if(grid[i][j]){
                bomb_loc.push_back(make_pair(i,j)); // 폭탄이 있다면 좌표 넣기
            }
        }
    
    Choose(0);   // n번째 폭탄을 선택
    cout << ans;
    return 0;
}