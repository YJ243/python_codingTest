#include <iostream>
#include <vector>

using namespace std;

bool check(int h, int m, int s){
    if( h % 10 == 3 || m % 10 == 3 || m / 10 == 3 || s % 10 == 3 || s / 10 == 3)
        return true;
    return false;
}


int main(){
    int n;
    cin >> n;
    int answer = 0;
    for(int i=0; i<=n; i++){
        for(int j=0; j<=59; j++){
            for(int k=0; k<=59; k++){
                if(check(i,j,k))
                    answer++; 
            }

        }
    }
    cout << answer << '\n';
}