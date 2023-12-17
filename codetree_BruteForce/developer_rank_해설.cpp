/*
 * 2023.12.17
 * 모든 개발자에 대해 2명의 개발자를 정하고 해당 개발자의 순위 비교가 각 경기마다 바뀌지 않는지 탐색
 * 주어진 입력을 2차원 배열로 생각하고 풀기. 
 * 두 번호에 대해 하나의 열 번호가 이차원 배열의 모든 행에서 낮은 순서쌍의 개수를 찾으면 됨
 * 한 개발자가 나머지 한 개발자보다 순위가 높다고 가정하고 두 개발자를 골라 모든 경우를 다 따져보기
 * k번의 모든 경기에 대해 두 개발자의 위치를 찾고, 한 번이라도 두 개발자의 순위가 바뀐다면 답 X
*/

#include <iostream>
#define MAX_K 10
#define MAX_N 20

using namespace std;

int k, n;                       // k: 경기의 수, n: 개발자 수
int arr[MAX_K][MAX_N];

int main(){
    // 입력
    cin >> k >> n;
    for(int i=0; i<k; i++)
        for(int j=0; j<n; j++)
            cin >> arr[i][j];
    int ans = 0;

    // 모든 쌍에 대해서 불변의 순위인 쌍을 찾기
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++){
            // i번 개발자가 j번 개발자보다 항상 높은 순위인지 여부를 확인

            // i와 j가 같을 경우 넘어가기
            if(i == j) continue;

            // correct: i번 개발자가 j번 개발자보다 항상 높은 순위일 떄 true
            bool correct = true;

            // k번의 모든 경기에 대해 두 개발자의 위치를 찾고,
            // 하나라도 i번 개발자가 더 뒤에 있으면 correct를 false로 바꿈
            for(int x=0; x<k; x++){
                int index_i = 0, index_j = 0;

                for(int y=0; y<n; y++){
                    if(arr[x][y] == i) index_i = y;
                    if(arr[x][y] == j) index_j = y;
                }

                if(index_i > index_j)
                    correct = false;
            }
            if(correct) ans++;
        }

    cout << ans;
    return 0;
}