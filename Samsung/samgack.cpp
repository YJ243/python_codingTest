#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#define MAX_NUM 10000
ø
using namespace std;

int s, e;                   
bool visited[MAX_NUM+1];    
int ans;                    
vector<int> level(MAX_NUM+1, 0);

void Initialize(){
    if(s > e) swap(s, e);
    for(int i=1; i<=MAX_NUM; i++){
        visited[i] = false;
    }
    ans = 0;    
}

void precalculateLevels() {
    for (int i = 1, curLevel = 1; i <= MAX_NUM; ++curLevel) {
        for (int j = 0; j < curLevel && i <= MAX_NUM; ++j, ++i) {
            level[i] = curLevel;
        }
    }
}

void bfs(){
    queue<pair<int, int>> q;
    q.push(make_pair(s, 0));
    visited[s] = true;

    while(!q.empty()){
        int curNum = q.front().first, curCnt = q.front().second;
        q.pop();

        if(curNum == e){
            ans = curCnt;
            break;
        }

        vector<int> next;
        int curL = level[curNum];
        
        if(curNum + 1 <= e && curNum + 1 <= curNum + curL) next.push_back(curNum + 1);
        if(curNum - 1 >= s && curNum - 1 >= curNum - curL) next.push_back(curNum - 1);
        if(curNum + curL <= e) next.push_back(curNum + curL);
        if(curNum + curL + 1 <= e) next.push_back(curNum + curL + 1);
        
        for(int nextNum : next){
            if(!visited[nextNum]){
                visited[nextNum] = true;
                q.push(make_pair(nextNum, curCnt + 1));
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    precalculateLevels();

    for(int test_case = 1; test_case <= T; ++test_case){
        cin >> s >> e;
        Initialize();
        bfs();
        cout << "#" << test_case << ' ' << ans << '\n';
    }
    return 0;
}
