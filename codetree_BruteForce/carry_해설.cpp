/*
 * 2023.11.13
 * 입력된 n개의 숫자중 3개를 뽑아 각 자리의 합마다 carry가 발생하는지 완전탐색 진행
*/

#include <iostream>

#define MAX_N 20

using namespace std;

int n;
int arr[MAX_N];

int main(){
    // 입력
    cin >> n;
    for(int i=0; i < n; i++)
        cin >> arr[i];

    // 모든 쌍을 다 잡아보기
    int ans = -1;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            for(int k=j+1; k<n; k++){
                bool carry = false;

                // 일의 자리에서 carry가 발생하는 경우
                if(arr[i]%10 + arr[j]%10 + arr[k]%10 >= 10) 
                    carry = true;

                // 십의 자리에서 carry가 발생하는 경우
                if(arr[i]%100 / 10 + arr[j]%100 / 10 + arr[k]%100 / 10 >= 10)
                    carry = true;
                
                // 백의 자리에서 carry가 발생하는 경우
                if(arr[i]%1000 / 100 + arr[j]%1000 / 100 + arr[k]%1000 / 100)
                    carry = true;
                
                // 천의 자리에서 carry가 발생하는 경우
                if(arr[i]%10000 / 1000 + arr[j]%10000 / 1000 + arr[k]%10000 / 1000)
                    carry = true;
                if(carry == false)
                    ans = max(ans, arr[i]+arr[j]+arr[k]);
            }
    cout << ans << '\n';
    return 0;
}