#include <iostream>
#include <vector>

using namespace std;


// 나이트가 이동할 수 있는 8가지 방향 정의
int dx[8]={1,-1,1,-1,2,2,-2,-2};
int dy[8]={2,2,-2,-2,1,-1,1,-1};


int main(){
    int answer = 0;
    // 현재 나이트의 위치 입력받기
    string loc;
    cin >> loc;
    int y = (int)loc[0] - 'a'+1; // 열, column
    int x = loc[1] - '0'; // 행, row
    cout << x << ' '<< y << '\n';

    for(int i=0; i<8; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 해당 위치로 이동이 가능하다면 카운트 증가       
        if (nx >=1 && ny >= 1 && nx <= 8 && ny <= 8){
            answer++;
        }
    }
    cout << answer << '\n';
}