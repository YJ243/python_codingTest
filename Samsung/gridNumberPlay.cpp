/*
 * 2024.03.26
 * 격자 숫자 놀이
 * 내풀이
 * 중간에 다른 것 하다가 1시간 반 안에 풀어냄
*/
#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_N 100

using namespace std;
int r, c, k;
int grid[MAX_N][MAX_N];
int xLen, yLen;

void FindLength(){
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            if(grid[i][j] > 0)
                xLen = max(xLen, i+1);
            if(grid[i][j] > 0)
                yLen = max(yLen, j+1);
        }
    }
}

bool InRange(int x, int y){         // 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < MAX_N && 0 <= y && y < MAX_N;
}

void PlayRow(){         // 행 단위로 놀이를 수행하는 함수
    int tmp[MAX_N][MAX_N] = {};            // 놀이 수행하고 난 뒤의 격자판

    for(int i=0; i<xLen; i++){
        int numberCnt[MAX_N+1] = {};        // idx번 숫자가 몇개 들어있는지?
        vector<pair<int, int> > numbers;
        for(int j=0; j<yLen; j++){
            int num = grid[i][j];
            if(num == 0) continue;
            bool IsExist = false;
            for(int k=0; k<(int)numbers.size(); k++){
                if(num == numbers[k].second){   // 만약 숫자가 있다면
                    numbers[k] = make_pair(numbers[k].first+1, num);
                    IsExist = true;
                }
            }
            if(!IsExist)
                numbers.push_back(make_pair(1, num));
        }
        sort(numbers.begin(), numbers.end());
        for(int j=0; j < (int)numbers.size() * 2 && j < MAX_N; j += 2){
            tmp[i][j] = numbers[j/2].second;
            tmp[i][j+1] = numbers[j/2].first; 
        }
    }

    // tmp에서 grid로 옮기기
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            grid[i][j] = tmp[i][j];
        }
    }
}

void PlayColumn(){      // 열 단위로 놀이를 수행하는 함수
    int tmp[MAX_N][MAX_N] = {};            // 놀이 수행하고 난 뒤의 격자판

    for(int j=0; j<yLen; j++){
        int numberCnt[MAX_N+1] = {};        // idx번 숫자가 몇개 들어있는지?
        vector<pair<int, int> > numbers;
        for(int i=0; i<xLen; i++){
            int num = grid[i][j];
            if(num == 0) continue;
            bool IsExist = false;
            for(int k=0; k<(int)numbers.size(); k++){
                if(num == numbers[k].second){   // 만약 숫자가 있다면
                    numbers[k] = make_pair(numbers[k].first+1, num);
                    IsExist = true;
                }
            }
            if(!IsExist)
                numbers.push_back(make_pair(1, num));
        }
        sort(numbers.begin(), numbers.end());
        for(int i=0; i < (int)numbers.size() * 2 && i < 100; i += 2){
            tmp[i][j] = numbers[i/2].second;
            tmp[i+1][j] = numbers[i/2].first; 
        }
    }

    // tmp에서 grid로 옮기기
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            grid[i][j] = tmp[i][j];
        }
    }
}

void Simulate(){
    // Step 1. 행의 개수와 열의 개수 찾기
    FindLength();
    // Step 2. 연산 수행하기
    if(xLen >= yLen){
        PlayRow();      // 행 단위로 놀이 수행
    }
    else{
        PlayColumn();   // 열 단위로 놀이 수행
    }
}

int main() {
    // 입력 받기:
    cin >> r >> c >> k;
    r--; c--;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            cin >> grid[i][j];
    int ans = -1;
    for(int i=0; i<=100; i++){
        if(grid[r][c] == k){
            ans = i;
            break;
        }
        Simulate();
    }
    cout << ans;
    return 0;
}