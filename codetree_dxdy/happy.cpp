/*
 * 2023.11.06
 * 내 풀이
*/

/*
#include <iostream>
#define INT_N 100
using namespace std;

int n,m;
int maze[INT_N][INT_N];
int main() {
    cin >> n >> m;
    if(m==1){
        cout<<n*2;
        return 0;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cin >> maze[i][j];
    }
    int happy_cnt=0;
    int prior_num=0, succession=1;
    for(int i=0;i<n;i++){
        prior_num = maze[i][0];
        succession = 1;
        for(int j=1; j<n; j++){
            if(prior_num == maze[i][j]){
                succession++;
                if(succession == m){
                    happy_cnt++;
                    break;
                }
            }
            else{
                prior_num = maze[i][j];
                succession = 1;
            }
        }
    }
    for(int j=0; j<n; j++){
        prior_num = maze[0][j];
        succession = 1;
        for(int i=1; i<n; i++){
            if(prior_num == maze[i][j]){
                succession++;
                if(succession == m){
                    happy_cnt++;
                    break;
                }
            }
            else{
                prior_num = maze[i][j];
                succession = 1;
            }
        }
    }
    
    cout<<happy_cnt;
    return 0;
}
*/

// 해설 풀이
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 100

int n, m;
int grid[MAX_N][MAX_N];

int seq[MAX_N];
bool IsHappySequence(){
    // 주어진 seq가 행복한 수열인지 판단하는 함수
    int consecutive_count = 1, max_ccnt = 1;
    for(int i=1; i<n; i++){
        if(seq[i-1] == seq[i])
            consecutive_count++;
        else
        {
            consecutive_count = 1;
        }
        max_ccnt = max(max_ccnt, consecutive_count);

    }
    // 최대로 연속한 횟수가 m 이상이면 true를 반환
    return max_ccnt >= m;
}
int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    int num_happy = 0;

    // 먼저 가로로 행복한 수열의 수를 세기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            seq[j] = grid[i][j];
        if(IsHappySequence())
            num_happy++;
    }
    // 세로로 행복한 수열의 수를 세기
    for(int j=0; j<n; j++){
        for(int i=0; i<n; i++){
            seq[i] = grid[i][j];
        }
        if(IsHappySequence())
            num_happy++;
    }
    cout << num_happy;
    return 0;
}