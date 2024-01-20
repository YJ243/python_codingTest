/*
 * 2024.1.20
 * 내 풀이
*/
#include <iostream>
#define MAX_N 4
using namespace std;

int grid[MAX_N][MAX_N];
char dir;


void FindStraightNum(int idx){
    if(dir == 'R' || dir == 'D'){
        // 같은 수가 다음에 존재한다면 그 다음 수를 0으로 만들기
        for(int j=MAX_N-1; j>=1; j--){
            if(dir == 'R'){
                if(grid[idx][j] == 0) continue; // 0이면 넘어가기
                if(grid[idx][j] == grid[idx][j-1]){ // 만약 그 다음 수와 같다면
                    grid[idx][j] *= 2;
                    grid[idx][j-1] = 0; // 그 다음 수를 0으로 만들기
                }
            }
            else{
                if(grid[j][idx] == 0) continue;
                if(grid[j][idx] == grid[j-1][idx]){
                    grid[j][idx] *= 2;
                    grid[j-1][idx] = 0;
                }
            }
        }
    }
    else{
        // 같은 수가 다음에 존재한다면 그 다음 수를 0으로 만들기
        for(int j=0; j<MAX_N-1; j++){
            if(dir == 'L'){
                if(grid[idx][j] == 0) continue; // 0이면 넘어가기
                if(grid[idx][j] == grid[idx][j+1]){ // 만약 그 다음 수와 같다면
                    grid[idx][j] *= 2;
                    grid[idx][j+1] = 0; // 그 다음 수를 0으로 만들기
                }
            }
            else{
                if(grid[j][idx] == 0) continue;
                if(grid[j][idx] == grid[j+1][idx]){
                    grid[j][idx] *= 2;
                    grid[j+1][idx] = 0;
                }
            }
        }
    }
}
void MoveZero(int idx){        // idx번째 줄에서 0을 한쪽으로 모는 함수
    // 임시로 옮겨놓을 배열 선언
    int temp[MAX_N];
    for(int j=0; j<MAX_N; j++)
        temp[j] = 0;

    // 끝에서부터 보기
    if(dir == 'R' || dir == 'D'){
        int tempLastIdx = MAX_N-1;
        // 1-1. 줄 단위로 숫자를 오른쪽으로 몰기
        for(int j=MAX_N-1; j>=0; j--){
            if(dir == 'R'){
                if(grid[idx][j])
                    temp[tempLastIdx--] = grid[idx][j];
            }

            else{
                if(grid[j][idx]){
                    temp[tempLastIdx--] = grid[j][idx];
                }
            }
        }
        // 1-2. 원래 배열로 옮기기
        for(int j=0; j<MAX_N; j++){
            if(dir == 'R')
                grid[idx][j] = temp[j];
            else
                grid[j][idx] = temp[j];
        }
    }

    // 0번부터 보기
    else if(dir == 'L' || dir == 'U'){
        int tempLastIdx = 0;
        // 1-1. 줄 단위로 숫자를 왼쪽으로 몰기
        for(int j=0; j<MAX_N; j++){
            if(dir == 'L'){
                if(grid[idx][j])
                    temp[tempLastIdx++] = grid[idx][j];
            }
            else{
                if(grid[j][idx])
                    temp[tempLastIdx++] = grid[j][idx];
            }
        }
        // 1-2. 원래 배열로 옮기기
        for(int j=0; j<MAX_N; j++){
            if(dir == 'L')
                grid[idx][j] = temp[j];
            else
                grid[j][idx] = temp[j];
        }
    }

}

void Move(){
    // 한 줄 단위로 기
    for(int idx=0; idx<MAX_N; idx++){
        // Step 1. 0을 한쪽으로 몰기
        MoveZero(idx);
        // Step 2. 같은 숫자가 두개씩 있는지 탐색하기
        FindStraightNum(idx);
        // Step 3. 마지막으로 0을 한쪽으로 몰기
        MoveZero(idx);
    }
}

int main(){
    // 입력:
    for(int i=0; i<MAX_N; i++)
        for(int j=0; j<MAX_N; j++)
            cin >> grid[i][j];
    cin >> dir;

    Move();

    // 출력:
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}