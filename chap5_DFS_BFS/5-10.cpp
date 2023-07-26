#include <iostream>
#include <queue>
using namespace std;
static int a[1000][1000];
static bool visited[1000][1000];
//static vector<vector<int>> a;

//static vector<bool> visited;
static int n,m;
int answer;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

void bfs(int x, int y){
    visited[x][y] = 1;
    queue<pair<int,int>> myqueue;
    myqueue.push(make_pair(x,y));

    while(!myqueue.empty()){
        int cur[2]={0};
        cur[0]=myqueue.front().first;
        cur[1]=myqueue.front().second;

        myqueue.pop();
        for(int i=0; i<4; i++){
            int nx = cur[0] + dx[i];
            int ny = cur[1] + dy[i];

            if(nx >=0 && ny >=0 && nx <=n-1 && ny <=m-1){
                if(a[nx][ny] == 0 && visited[nx][ny]==0){
                    myqueue.push(make_pair(nx,ny));
                    visited[nx][ny]=1;
                }
            }
        }
    }
    answer++;
}


int main(){
    cin >> n >> m;
    //a.resize(n);
    //a = vector<vector<int>>(n,vector<int>(m,0));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%1d", &a[i][j]);
        }
    }
/*
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
*/
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == 0 && visited[i][j]==0){
                bfs(i,j);
            }
        }
    }
    cout<<answer<<'\n';
}

