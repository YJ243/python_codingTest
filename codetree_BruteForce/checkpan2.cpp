/*
 * 2023.11.13
 * 풀기까지 시간이 조금 걸린 문제
*/

#include <iostream>
#define MAX_N 15

using namespace std;
int R, C;
char arr[MAX_N][MAX_N];

int main(){
    // 입력받기
    cin >> R >> C;
    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++)
            cin >> arr[i][j];

    char cur_c = arr[0][0];     // (0,0) 좌표에 있는 색깔이 처음 기준 색깔
    if(cur_c == arr[R-1][C-1]){ // (0,0) 과 (R-1,C-1) 좌표 색깔이 같다면
        cout<< 0 << '\n';       // 2곳의 점프로 도달하지 못하니 0 출력
        return 0;
    }

    int success_cnt = 0;        // 성공하는 경우의 수
    for(int i=1; i<R; i++){
        for(int j=1; j<C; j++){
            cur_c = arr[0][0];  // 탐색할 때마다 다시 cur_c를 처음 기준 색깔로 초기화
            if(arr[i][j] != cur_c && (i == R-1 && j == C-1) && success_cnt == 0){
                // 현재 색과 다른데, 맨 마지막 좌표에만 있고, 그 앞에서 이동에 성공한 경우가 없다면
                // success_cnt == 0 조건을 검사 안하면 앞의 탐색이 모두 끝나고 마지막 좌표에 도달한 경우도 세게 됨
                cout << 0 << '\n';
                return 0;
            }
            else if(arr[i][j] != cur_c){
                // 이제 여기서 탐색해야 함, (i,j)는 처음 점프한 지점
                // 적어도 한 칸 이상 오른쪽/아래쪽에 있는 위치로만 점프 가능
                cur_c = arr[i][j];  // 점프한 이후의 칸에 적혀 있는 색깔이 현재 색깔
                for(int k=i+1; k<R; k++){
                    for(int l=j+1; l<C; l++){
                        if(cur_c != arr[k][l]){
                            // (k,l)은 두 번째 점프한 지점
                            for(int x=k+1; x<R; x++){
                                for(int y=l+1; y<C; y++){
                                    // 이제 여기서 한 번 점프했을 때 마지막까지 도달 가능하면 success_cnt++;
                                    if(x==R-1 && y == C-1 && cur_c == arr[R-1][C-1])
                                        success_cnt++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<success_cnt;
    return 0;
}