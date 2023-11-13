/*
 * 2023.11.13
 * arr[i]를 나눠주면 그 숫자를 봐야 하는데 계속 나누기 전 숫자인 arr[i]를 봐서 틀림
*/

#include <iostream>
#include <algorithm>

#define MAX_N 20

using namespace std;
int N;
int arr[MAX_N];

int main(){
    // 입력
    cin >> N;
    for(int i=0; i<N; i++)
        cin >> arr[i];

    // 3개의 숫자를 고르고
    int ans = -1;
    for(int i=0; i<N; i++)
        for(int j=i+1; j<N; j++)
            for(int k=j+1; k<N; k++){
                // 그 숫자를 일의 자리부터 천의 자리까지 확인
                bool IsCarry = false;
                int a = arr[i], b = arr[j], c = arr[k];
                for(int l=1; l=4; l++){
                    // 10으로 나눈 나머지(일의자리수) 확인
                    if(a%10 + b%10 + c%10 >= 10) IsCarry = true;
                    // 나머지 빼고 10으로 나누어서 계속 확인해나가기
                    a = (a-a%10) / 10;
                    b = (b-b%10) / 10;
                    c = (c-c%10) / 10;
                }
                if(!IsCarry)
                    ans = max(arr[i] + arr[j] + arr[k], ans);
            }
    cout << ans << '\n';
    return 0;
}