/*
 * 2024.02.10
 * 단어 변환 (처음에 DFS로 풀었다가 최소 값을 찾는 부분에서 틀림)
 * BFS로 풀었어야 하는 문제, 나중에 고침
*/
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#define MAX_N 50

using namespace std;

queue<pair<string, int> > q;        // (단어, 해당 단어까지 오는데 걸린 횟수)
bool visited[MAX_N];

int bfs(string target, vector<string> &words){
    while(!q.empty()){
        string curr = q.front().first;
        int cnt = q.front().second;
        q.pop();
        if(curr == target){
            return cnt;
        }
        for(int i=0; i<words.size(); i++){
            int sameCnt = 0;
            for(int j=0; j<(int)words[i].size(); j++){
                if(words[i][j] == curr[j]) sameCnt++;
            }
            if(sameCnt == words[i].size()-1 && !visited[i]){
                visited[i] = true;
                q.push(make_pair(words[i], cnt+1));
            }
        }
    }
}
int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    bool IsExist = false;
    for(int i=0; i<(int)words.size(); i++){
        if(words[i] == target){
            // 만약 target이 words 안에 있다면
            IsExist = true;     // 존재한다는 표시
        }
    }
    if(!IsExist){
        // 만약 존재하지 않으면
        answer = 0;
        return answer;
    }
    
    for(int i=0; i<(int)words.size(); i++){
        int sameCnt = 0;
        for(int j=0; j<(int)words[i].size(); j++){
            if(words[i][j] == begin[j]) sameCnt++;
        }
        if(sameCnt == words[i].size()-1){
            visited[i] = true;
            q.push(make_pair(words[i], 1));
        }
    }
    answer = bfs(target, words);
    return answer;
}