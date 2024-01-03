/*
 * 2023.12.20
 * a가 더해지는 횟수, b가 더해지는 횟수를 따로 정해서 구했음
*/
#include <iostream>
#include <algorithm>
#define MAX_ABC 1000
using namespace std;
int a, b, c;
int ans;
int main() {
    cin >> a >> b >> c;
    for(int i=0; i<MAX_ABC+1; i++){
        int cur_sum = 0;
        for(int j=0; j<MAX_ABC+1; j++){
            // i는 a가 더해지는 횟수, j는 b가 더해지는 횟수
            if((i*a + j*b) <= c){
                // c보다 작거나 같다면
                cur_sum = i*a+j*b;
            }
            else
                break;
        }
        ans = max(ans, cur_sum);
    }
    cout << ans;
    return 0;
}