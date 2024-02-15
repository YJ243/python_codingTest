/*
 * 2024.02.10
 * 단어 변환
*/
#include <string>
#include <vector>
#include <queue>
#define MAX_N 50

using namespace std;

int visited[MAX_N];

int possible(string a, string b){
    int cnt = 0;
    for(int i=0; i<a.length(); i++)
        if(a[i] != b[i]) cnt++;
    if(cnt==1) return 1;
    return 0;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    queue<pair<string, int> > q;        // (단어, 해당 단어까지 오는데 걸린 횟수)
    string temp;int num;
    q.push(make_pair(begin, 0));
    
    while(!q.empty()){
        temp = q.front().first;
        num = q.front();second;
        q.pop();

        if(temp.compare(target) == 0){
            answer = num;
            break;
        }

        for(int i=0; i<words.size(); i++){
            if(!visited[i] && possible(temp, words[i])){
                visited[i] = 1;
                q.push(make_pair(words[i], num+1));
            }
        }
    }

    return answer;
}