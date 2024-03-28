/*
 * 2024.03.28
 * 윷놀이 사기단
 * runtime error가 뜨는데 어디가 문제인지 모르겠다...
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#define MAX_N 10
#define MAX_YUT 4
#define FINISH_LOC 41
using namespace std;

int arr[MAX_N];
int n = 10;
pair<int, int> malLoc[MAX_YUT];   // {0, 0}: 0번째 루트의 0번째에 있음
vector<vector<int> > board = {
    {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40},
    {10, 13, 16, 19, 25, 30, 35, 40},
    {20, 22, 24, 25, 30, 35, 40},
    {30, 28, 27, 26, 25, 30, 35, 40}
};

int ans;

void Initialize(){
    // 이동 칸 수 10개 입력받기
    for(int i=0; i<n; i++)
        cin >> arr[i];
    
    // 4개의 말들 시작 위치 저장하기
    for(int i=0; i<MAX_YUT; i++)
        malLoc[i] = make_pair(0,-1);
    
}
bool IsExist(int route_num, int in_num){
    for(int i=0; i<4; i++){
        if(malLoc[i].first == route_num && malLoc[i].second == in_num)
            return true;
    }
    return false;
}
int Move(int yut_idx, int cnt){     // yut_idx번 말을 cnt만큼 이동시키기
    int next_score = 0;
    // 일단 현재 yut_idx번째 말의 루트 번호와 위치 받아오기
    int route_num = malLoc[yut_idx].first, in_num = malLoc[yut_idx].second;
    int next_in_num = 0;
    if(route_num == 0){     // 0번째 루트를 따라서 가고 있는 경우
        next_in_num = in_num + cnt;     // 현재 위치에서 cnt만큼 가기
        if(next_in_num % 5 == 4 && next_in_num > 1){    // 만약 파란색에 도착했다면
            route_num = (next_in_num / 5)+1, next_in_num = 0;       // 그룹 바꿔주기
            if(IsExist(route_num, next_in_num)) return -1;          // 만약 이동할 곳에 다른 말이 존재한다면 -1 리턴

            next_score = board[route_num][next_in_num];             // 점수 바꿔주기
        }
        else{   // 0번째 루트에서 파란색이 아닌 곳에 위치했다면
            if(IsExist(route_num, next_in_num)) return -1;          // 현재 그룹에서 next_in_num에 다른 말이 존재한다면 -1 리턴
            if(next_in_num >= 20)  next_score = 0;                  // 만약 도착지에 도착했다면 점수 0만들기
            else
                next_score = board[route_num][next_in_num];         // 그 외의 경우 해당 칸에 있는 점수 넣기
        }
    }
    else{       // 경로가 1, 2, 3이라면
        next_in_num = in_num + cnt;     // 일단은 더하기
        if(IsExist(route_num, next_in_num)) return -1;      // 그런데 그 자리에 다른 말이 있다면 -1 리턴
        if(route_num == 1 || route_num == 3){               // 만약 그룹이 1 또는 3이라면
            if(next_in_num >= 8)    next_score = 0;         // 이동한 곳이 도착지라면 점수는 0으로
            else                                            // 도착지가 아니라면 점수 넣기
                next_score = board[route_num][next_in_num];
        }
        else {                                              // 만약 그룹이 2라면
            if(next_in_num >= 7)    next_score = 0;         // 이동한 곳이 도착지라면
            else
                next_score = board[route_num][next_in_num]; // 도착지가 아니라면 점수 넣기
        }
    }
    // 이제 이동한 곳으로 말 위치 바꿔주기
    malLoc[yut_idx] = make_pair(route_num, next_in_num);         // 현재 윷의 그룹과 위치를 바꿔주기
    return next_score;
}

bool IsArrived(int yut_idx){        // yut_idx번 말이 도착지에 도착하였는지 확인하는 함수
    // 어떤 루트의 몇번째 있는지 확인
    int route_num = malLoc[yut_idx].first, in_num = malLoc[yut_idx].second;
    if(route_num == 0 && in_num >= 20)  return true;
    else if(route_num == 1 && in_num >= 8)  return true;
    else if(route_num == 2 && in_num >= 7) return true;
    else if(route_num == 3 && in_num >= 8) return true;
    return false;
}

void Choose(int idx, int score){        // 현재 idx번째 윷을 던질 말을 선택, 도착지에 도달한 말의 개수는 finish_cnt, 현재까지의 점수는 score
    // 만약 모두 끝까지 도달했거나, 10번의 윷을 모두 던졌다면
    if(idx == MAX_N){
        ans = max(ans, score);
        cout << ans << '\n';
        return;
    }

    // 4개의 윷을 차례대로 보면서 
    for(int i=0; i<MAX_YUT; i++){
        if(IsArrived(i)) continue;              // 만약 이미 도착한 말이라면 넘어가기
        int prior_route_num = malLoc[i].first, prior_in_num = malLoc[i].second;         // i번 이동하기 전 위치 저장해놓기

        int plus_score = Move(i, arr[idx]);      // i번째 말을 arr[idx]만큼 이동시키기
        cout << i<<"번 말 움직이고 " << malLoc[i].first << ' ' << malLoc[i].second << "에 옴" << plus_score << "만큼 얻음" << '\n';
        if(plus_score == -1)        // 만약 -1을 반환했다면, 이동할 수 없는 경우이니 다음 말을 확인하기
            continue;
        
        if(IsArrived(i))
            Choose(idx+1, score);
        else
            Choose(idx+1, score + plus_score);
        
        // 원래대로 돌려놓기
        malLoc[i] = make_pair(prior_route_num, prior_in_num);
        
    }

}

int main() {
    Initialize();

    Choose(0, 0);       // 0번째 말을 고르러 가기, 현재까지 도착칸에 도달한 말의 수 0, 점수는 0
    cout << ans;
    return 0;
}