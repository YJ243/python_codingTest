#include <iostream>
#include <queue>

using namespace std;

int a[201][201];
int visited[201][201];
int n, m;

// ©Л,го,аб,╩С
int dx[]={0,1,-1,0};
int dy[]={1,0,0,-1};

void bfs(int x, int y){
    visited[x][y] = 1;
    queue<pair<int,int>> myqueue;
    myqueue.push(make_pair(x,y));

    while(!myqueue.empty()){
        int cur[2]={0};
        cur[0] = myqueue.front().first;
        cur[1] = myqueue.front().second;

        myqueue.pop();

        for(int i=0; i<4; i++){
            int nx = cur[0] + dx[i];
            int ny = cur[1] + dy[i];

            if(nx>=0 && ny >= 0 && nx<=n-1 && ny <= m-1){
                if(visited[nx][ny]==0 && a[nx][ny]!=0){
                    a[nx][ny] = a[cur[0]][cur[1]]+1;
                    visited[nx][ny] = 1;
                    myqueue.push(make_pair(nx,ny));
                }
            }
        }

    }
}

int main(){
    cin >> n >> m;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%1d", &a[i][j]);
        }
    }

    bfs(0,0);
    cout<<a[n-1][m-1]<<'\n';
}