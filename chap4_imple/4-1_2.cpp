#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string plans;
    int n;
    cin >> n;
    cin.ignore(); // 버퍼 비우기 
    getline(cin, plans);
    


    // 먼저 이동할 계획서 내용 저장

    // L,R,U,D
    int dx[4]={0,0,-1,1};
    int dy[4]={-1,1,0,0};
    char direction[4]={'L','R','U','D'};

    int x = 1;
    int y = 1;
    int nx = 0;
    int ny = 0;

    // 이동 계획을 하나씩 확인
    for(int i=0; i<plans.size(); i++){
        for(int j=0; j<4; j++){
            if(plans[i] == direction[j]){
                // 이동 후 좌표 구하기
                nx = x+dx[j];
                ny = y + dy[j];
            }
        }
        // 공간을 벗어나는 경우 무시
        if(nx < 1 || ny < 1 || nx > n || ny > n){
            continue;
        }
        // 이동 수행
        x = nx;
        y = ny;

    }
    cout << x << ' ' << y << '\n';
}