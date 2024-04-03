/*
 * 2024.03.28
 * 윷놀이 사기단
 * 해설 보고 지우고 다시 풀어서 맞음
*/

#include <iostream>
#include <algorithm>

#define MAX_TURN 10
#define PIECE_CNT 4
#define BOARD_WIDTH 40
#define START 0
#define END 20
using namespace std;
int arr[MAX_TURN];
int piece_loc[PIECE_CNT];

int n = MAX_TURN;
int max_score;
int board[BOARD_WIDTH] = {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 0,
    13, 16, 19, 0, 0,
    22, 24, 0, 0, 0,
    28, 27, 26, 0, 0,
    25, 30, 35, 40
};

bool IsBlue(int idx){       // idx번이 파란색인지 확인하기
    return idx != START && idx % 5 == 0;
}

int GetLoc(int idx, int cnt){   // idx번에서 cnt만큼 이동했을 때 도착하는 위치를 반환하는 함수
    if(idx == END)      // 도착 칸으로 이동했으면 이동 마침
        return idx;
    if(cnt == 0)        // 이동을 다 했으면 마침
        return idx;
    
    int next_idx = idx+1;   // 한칸 이동
    if(idx == 23 || idx == 27 || idx == 33)
        next_idx = 36;
    else if(idx == 19)
        next_idx = 39;
    else if(idx == 39)
        next_idx = END;
    return GetLoc(next_idx, cnt-1);
}

bool IsOverlapped(){
    for(int i=0; i<PIECE_CNT; i++)
        for(int j=i+1; j < PIECE_CNT; j++){
            if(piece_loc[i] == piece_loc[j] && piece_loc[i] != START && piece_loc[i] != END)
                return true;
        }
    return false;
}

void FindMaxScore(int idx, int score){      // idx번째 이동할 말을 고르는 함수, 현재까지 점수는 score
    if(idx == MAX_TURN){
        max_score = max(max_score, score);
        return;
    }

    for(int i=0; i<PIECE_CNT; i++){
        if(piece_loc[i] == END)     // 도착칸에 도착하지 않은 말을 골라야 함
            continue;
        
        int temp = piece_loc[i];    // backtracking 전 위치를 저장해두기
        if(IsBlue(piece_loc[i]))    // 파란색 칸에서 이동을 시작한다면 빨간색 화살표를 따라가도록 바꿔주기
            piece_loc[i] = GetLoc(piece_loc[i]+16, arr[idx]-1);
        else                        // 파란색 칸이 아니라면 계속 검은색 화살표를 따라서 가기
            piece_loc[i] = GetLoc(piece_loc[i], arr[idx]);
        
        if(!IsOverlapped()){     // 도달하게 되는 위치에 다른 말이 없을 경우에만 이동 가능
            //cout << i << "번이 " << piece_loc[i] << "로 이동함" << '\n';
            FindMaxScore(idx+1, score + board[piece_loc[i]]);
        }
        
        piece_loc[i] = temp;
        
    }
}

int main() {
    // 입력 받기:
    for(int i=0; i<n; i++)
        cin >> arr[i];
    FindMaxScore(0, 0);

    cout << max_score;
    return 0;
}