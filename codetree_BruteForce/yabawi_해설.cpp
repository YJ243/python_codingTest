/*
 * 2023.12.19
 * 종이컵에 대한 배열을 하나 선언해 놓고, 조약돌이 있는 위치에만 숫자 1을 적어주기
 * 그 이후 두 종이컵이 바뀜에 따라 두 값을 배열 내에서 교환
 * => 특정 종이컵에 조약돌이 위치하는지 판단하는 것이 간단해짐
*/
#include <iostream>
#include <algorkthm>

#define MAX_N 100
#define MAX_NUM 3

using namespace std;

int n;
int a[MAX_N], b[MAX_N], c[MAX_N];
int yabawi[MAX_NUM+1];

int main(){
    // 입력
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> a[i] >> b[i] >> c[i];
    int max_score = 0;

    // 시작 위치를 전부 가정해 보기
    // 그 중 최대 점수를 계산
    for(int i=1; i<=3; i++){
        // 종이컵을 전부 비워주기
        yabawi[1] = yabawi[2] = yabawi[3] = 0;

        // i번째 종이컵에 처음 조약돌을 넣고 시작
        yabawi[i] = 1;

        int score = 0;
        // 게임을 순서대로 진행
        for(int j=0; j<n; j++){
            // 두 종이컵을 교환
            swap(yabawi[a[j]], yabawi[b[j]]);

            // 교환 이후 c[j]번에 돌이 있다면 점수를 얻음
            if(yabawi[c[j]])    score++;
        }
        // 최대 점수를 갱신하기
        max_score = max(max_score, score);
    }
    cout << max_score;
    return 0;
}
