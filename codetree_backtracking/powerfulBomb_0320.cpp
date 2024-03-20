/*
 * 2024.03.20
 * 내 풀이
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 20

using namespace std;

int n;
int arr[MAX_N][MAX_N];

int bomb[3][4][2] = {
    {{-1,0},{-2,0},{1,0},{2,0}},
    {{-1,0},{0,1},{1,0},{0,-1}},
    {{-1,-1},{-1,1},{1,-1},{1,1}}
};

vector<pair<int, int> > bomb_loc;
vector<int> selected;
int ans;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void updateArr(int v){
    for(int i=0; i<(int)bomb_loc.size(); i++){
        int x = bomb_loc[i].first, y = bomb_loc[i].second;
        int num = selected[i];
        for(int j=0; j<4; j++){
            int nx = x + bomb[num][j][0], ny = y + bomb[num][j][1];
            if(InRange(nx, ny)){
                arr[nx][ny] += v; 
            }
        }
    }
}

void Verify(){
    // step 1. 먼저 해당 bomb 위치에 선택한 폭탄 놓기
    updateArr(1);

    // step 2. 계산하기
    int bombed = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(arr[i][j])
                bombed++;
        }
    }
    ans = max(ans, bombed);
    
    // step 3. 다시 원래대로 돌려놓기
    updateArr(-1);
}

void Choose(int idx){
    if(idx == bomb_loc.size()){
        Verify();
        return;
    }

    for(int i=0; i<3; i++){
        selected.push_back(i);
        Choose(idx+1);
        selected.pop_back();
    }
}

int main() {
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> arr[i][j];
            if(arr[i][j])
                bomb_loc.push_back(make_pair(i,j));
        }
    }
    
    Choose(0);  // 0번째 폭탄 자리에 놓을 폭탄 선택하는 함수
    cout << ans;
    return 0;
}