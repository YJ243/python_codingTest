#include <iostream>
#include <vector>

using namespace std;

// 특정한 시각 안에 '3'이 포함되어 있는지 여부
bool check(int h, int m, int s){
    if( h % 10 == 3 || m % 10 == 3 || m / 10 == 3 || s % 10 == 3 || s / 10 == 3)
        return true;
    return false;
}
부

int main(){
    int n;
    cin >> n;
    int answer = 0;
    for(int i=0; i<=n; i++){
        for(int j=0; j<=59; j++){
            for(int k=0; k<=59; k++){
                // 매 시각 안에 '3'이 포함되어 있다면 카운트 증가
                if(check(i,j,k))
                    answer++; 
            }

        }
    }
    cout << answer << '\n';
}