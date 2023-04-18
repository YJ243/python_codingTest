#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;

    int answer = 0;
    int h = 0;
    int m = 0;
    int s = 0;

    for(int i=0; i<n; i++){
        if(i % 10 == 3){
            h++;
        }
    }
    for(int i=0; i<=59; i++){
        int mod=0;
        if(i % 10 == 3){
            mod++;
        }
    }
    answer  =  ;
    cout << answer << '\n';
}