/*
 * 2023.11.18
 * 내 풀이
*/
#include <iostream>
#include <algorithm>
#define MAX_LOC 10001
using namespace std;

int N, K;   // N: 사람 명수, K: 사진 크기
char loc[MAX_LOC];
int main(){
    cin >> N >> K;
    int max_idx = 0;
    int min_idx = MAX_LOC;
    for(int i=0; i<N; i++){
        int idx;
        cin >> idx;
        cin >>  loc[idx];
        max_idx = max(idx, max_idx);
        min_idx = min(idx, min_idx);
    }
    int ans = 0;
    //cout << loc[min_idx] << ' ' << loc[max_idx] << '\n';
    
    for(int i=1; i<=MAX_LOC-K; i++){
        int cur = 0;
    //    cout << i << ' ' ;
        
        for(int j=i; j<=i+K; j++){
            if(loc[j] == 'G'){
                cur += 1;
            }
            else if(loc[j] == 'H'){
                cur += 2;
            }

        }
        ans = max(cur, ans);
         
    }
    cout << ans;
}