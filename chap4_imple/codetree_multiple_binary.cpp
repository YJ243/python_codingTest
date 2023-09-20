#include <iostream>
#include <algorithm>

#define MAX_DIGIT 20

using namespace std;

int n, b;
int digits[MAX_DIGIT];
int cnt;

int main(){
    // 입력
    cin >> n >> b;

    // b진수로 변환 
    while(true){
        if(n<b){
            digits[cnt++] = n;
            break;
        }
        digits[cnt++] = n % b;
        n /= b;
    }

    // 진수 배열을 뒤집어 b진수를 출력
    for(int i=cnt-1; i >=0; i--)
        cout << digits[i];
    return 0;
}