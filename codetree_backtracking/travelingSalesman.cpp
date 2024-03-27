/*
 * 2024.03.26
 * 내 풀이
*/

#include <iostream>
#include <vector>
#include <climits>

#define MAX_N 10

using namespace std;
int n;
int grid[MAX_N][MAX_N];
bool visited[MAX_N];

vector<int> selected;
int ans = INT_MAX;

int Calc(){
    int curr = 0, curr_sum = 0;
    for(int i=0; i<(int)selected.size(); i++){
        int nextI = selected[i];
        if(grid[curr][nextI] == 0)
            return INT_MAX;
        curr_sum += grid[curr][nextI];
        curr = nextI;
    }
    if(grid[curr][0] == 0)
        return INT_MAX;
    curr_sum += grid[curr][0];
    return curr_sum;
}
void Choose(int cnt){
    if((int)selected.size() == n-1){
        ans = min(ans, Calc());        
        return;
    }
    if(cnt == n-1)
        return;

    for(int i=1; i<=n-1; i++){
        if(visited[i]) continue;

        visited[i] = true;
        selected.push_back(i);
        
        Choose(cnt+1);

        selected.pop_back();
        visited[i] = false;
    }    

}


int main() {
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];

    // 0 -> [1 -> 2 -> ... -> n-1] -> 0
    Choose(0);  // 가운데 1 ~ n-1의 순열 구하기  
    cout << ans;   
    return 0;
}