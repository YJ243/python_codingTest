/*
 * 2023.11.14
 * 해설 풀이
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>

#define MAX_N 20

using namespace std;

int n;
int arr[MAX_N][MAX_N];

int main(){
    // 입력
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> arr[i][j];

    // Step 1.
    // 첫번째 격자를 놓음 (i,j)
    int max_cnt = 0;
    for(int i=0; i<n; i++)
        // 격자를 벗어나지 않을 범위로만 잡음
        for(int j=0; j<n-2; j++){
            // 두 번째 격자를 놓음(k,l)
            for(int k=0; k<n; k++){
                for(int l=0; l<n-2; l++){
                    // step2. 두 격자가 겹치는 경우에는 가짓수를 세지 않음
                    if(i == k && abs(j-l) <= 2)
                        continue;

                    // Step3.  두 격자가 겹치지 않는 경우에 대해 동전 수를 세어 갱신
                    int cnt1 = arr[i][j] + arr[i][j+1] + arr[i][j+2];
                    int cnt2 = arr[k][l] + arr[k][l+1] + arr[k][l+2];
                    max_cnt = max(max_cnt, cnt1+ cnt2);
                }
            }
        }
    cout << max_cnt;
    return 0;
}