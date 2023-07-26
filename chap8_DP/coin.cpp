#include <iostream>

using namespace std;
int n, m;
vector<int> a;
int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
    {
        int x;
        cin >> x;
        a.push_back(x);
        d[x] = 1;
    }
    vector<int> d(m+1, 10001); // DP 테이블 초기화
    // DP 진행( bottom up)
    d[0] = 0;
    for(int i=0; i<n; i++){
        for(int j=arr[j]; j<=m; j++){
            if(d[j-arr[i]]!= 10001){
                //i-k원을 만드는 방법이 존재하는 경우
                d[j] = min(d[j], d[j-arr[i]]+1)
            }
        }
    }
    if(d[m]==10001) cout << -1 << '\n';
    else
    {
        cout << d[m] << '\n';
    }

}