/*
 * 2023.12.13
 * 해설
 *
*/
#include <iostream>

#define MAX_N 10

using namespace std;

int n;
int a[MAX_N], b[MAX_N], C[MAX_N];

int main(){
    // 입력
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> a[i] >> b[i] >> c[i];
    // 모든 숫자를 다 만들어 봄 (백의 자리수:i, 십의 자리수:j, 일의 자리수:k)
    int cnt = 0;
    for(int i=1; i<=9; i++)
        for(int j=1; j<=9; j++)
            for(int k=1; k<=9; k++){
                // 같은 수가 있는지 확인하기
                if(i == j || j == k || k == i) continue;

                // 해당 숫자가 정답일 때 모든 입력에 대해 올바른 답이 나왔는지 확인
                bool successed = true;
                for(int q=0; q<n; q++){
                    // x, y, z는 각각 백,십,일의 자리수
                    int x = a[q]/100;
                    int y = a[q]/10 % 10;
                    int z = a[q] % 10;

                    // cnt1: 1번 카운트, cnt2: 2번 카운트
                    int cnt1 = 0, cnt2=0;
                    if(x == i)  cnt1++;
                    if(y == j)  cnt1++;
                    if(z == k)  cnt1++;

                    // 이걸 이렇게 해결했네
                    if(x == j || x == k)    cnt2++; // 백의 자리수가 10 또는 1의 자리수에 있다면
                    if(y == i || y == k)    cnt2++;
                    if(z == i || z == j)    cnt2++;

                    // 만약 카운트 수가 다르다면 해당 숫자는 정답이 될 수 없음
                    if(cnt1 != b[q] || cnt2 != c[q]){
                        successed = false;
                        break;
                    }
                }

                if(successed) cnt++;
            }
    
    cout << cnt;
}