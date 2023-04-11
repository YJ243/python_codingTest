#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(m, vector<int>(m,0));

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    }
    int min[n]={0};
    for(int i=0; i<n; i++){
        min[i] = a[i][0];
        for(int j=1; j<m; j++)
        {
            if(min[i] > a[i][j])
                min[i] = a[i][j];

        }
    }
    int answer=min[0];
    for(int i=1; i<n; i++)
    {
        if(answer < min[i])
            answer = min[i];
    }
    cout << answer << '\n';
}