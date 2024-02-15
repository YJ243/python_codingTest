/*
 * 2024.2.10
 * 여행 경로(Backtracking + DFS)
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define MAX_AIRPORT 10000
using namespace std;

vector<string> selected_tickets;
vector<vector<string> > candidates;
int visited[MAX_AIRPORT];

void dfs(string start, vector<vector<string> > &tickets){
    if((int)selected_tickets.size() == (int)tickets.size()){
        candidates.push_back(selected_tickets);
        return;
    }
    for(int i=0; i<(int)tickets.size(); i++){       // 모든 티켓에 대해서 확인해보는데
        if(start == tickets[i][0] && !visited[i]){  // start로 시작하는 티켓이면서, 아직 방문하지 않았다면
            visited[i] = true;  // 방문처리
            selected_tickets.push_back(tickets[i][1]);      // 선택된 티켓에 추가하기
            dfs(tickets[i][1], tickets);            // 그 다음 목적지를 시작으로 하는 티켓 탐색
            selected_tickets.pop_back();            // 탐색을 마치고 돌아와서는 삭제
            visited[i] = false; // 방문 표시 원래대로 돌려놓기
        }
        
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    string start = "ICN";       // 시작 공항
    for(int i=0; i<(int)tickets.size(); i++){
        if(tickets[i][0] == start){
            visited[i] = true;      // 해당 티켓 방문 처리
            selected_tickets.push_back(tickets[i][1]);
            dfs(tickets[i][1], tickets);    // 해당 티켓의 도착지를 시작으로 하는 티켓 탐색        
            visited[i] = false;     // 해당 티켓 다시 돌려놓기
            selected_tickets.pop_back();
        }
    }
    
    sort(candidates.begin(), candidates.end());     // 사전순으로 가장 앞서는 경로 찾기
    // answer 업데이트
    answer.push_back(start);
    cout << candidates.size();
    for(int i=0; i<(int)candidates[0].size(); i++)
        answer.push_back(candidates[0][i]);
    return answer;
}