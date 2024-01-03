/*
 * 2023.12.19
 * 첫번째 위치에 돌이 있으면 두번째 위치로, 두번째 위치에 있다면 첫번째 위치로 바꾸는 것을 반복
 *
*/
#include <iostream>
#include <algorithm>
#define MAX_N 100

using namespace std;
int n;
int cups[MAX_N][MAX_N];
int max_score;

int main() {
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<3; j++){
            cin >> cups[i][j];
        }
    }

    for(int i=1; i<=3; i++){
        // i번 종이컵에 조약돌을 넣었을 경우
        int cur = i;
        int score = 0;
        for(int j=0; j<n; j++){
            // 만약 바꿔야 되는 컵에 조약돌이 들어있다면 첫번째와 두번째 중 다른 것을 cur에 넣기
            if(cups[j][0] == cur){
                cur = cups[j][1];
            }

            else if(cups[j][1] == cur){
                cur = cups[j][0];
            }
            // 세번째에 조약돌이 있다면 점수 증가
            if(cups[j][2] == cur) score++;

        }
        max_score = max(max_score, score);

    }
    cout << max_score;
    return 0;
}