/*
 *
*/
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;
unordered_set<int> nodeNum;    // node 번호
unordered_map<int, unordered_set<int>> graph; // 각 정점에서 나가는 간선들
unordered_map<int, int> inDegree;             // 각 정점의 진입 차수
unordered_map<int, int> canGoNum;           // 나갈 수 있는 것
int newNode = -1; // 새로 생성된 정점의 번호
int donutCount = 0, barCount = 0, eightCount = 0; // 각 그래프 유형의 개수
int eightCount1=0, barCount1 = 0, donutCount1 = 0;
bool donutFlag = false, barFlag = false, eightFlag = false;

void DFS(int cur){
    for (int next : graph[cur]) { // 현재 보고 있는 노드와 연결된 모든 노드를 보는데,
        if(canGoNum[next] < 1) continue;
        if(next==newNode) continue;
        if(canGoNum[next] == 2) {
            eightCount1++;
            eightFlag = true;
        }
        canGoNum[next]--;
        if(graph[next].empty()){ // 만약 다음 탐색하려는 것에서 나가는 노드가 없다면 막대모양임
            barFlag = true;
            barCount1++;
        }
        DFS(next);
    }
}

vector<int> solution(vector<vector<int>> edges) {
    // Step 1. 그래프 만들고 각 노드마다 진입 차수 계산
    for (auto& edge : edges) {
        graph[edge[0]].insert(edge[1]); // edge[0]번 정점에서 edge[1]번 정점으로 향함
        inDegree[edge[1]]++;
        nodeNum.insert(edge[0]); nodeNum.insert(edge[1]);
        canGoNum[edge[0]]++;
    }

    // Step 2. 새로운 정점 찾기
    for (auto& node : graph) {  // 그래프의 모든 정점을 보는데
        if (inDegree[node.first] == 0) { // 만약 들어오는 건 없는데
            if(node.second.size() > 1){    // 나가는건 1보다 크다면 새로 추가한 정점임
                newNode = node.first;
            }
        }
    }

    // Step 3. 각 노드에서 갈 수 있는 개수 완성하기(마치 visited 배열 같은 역할)
    for(int node : nodeNum){
        if(canGoNum[node]==0) canGoNum[node]++;
    }
    canGoNum[newNode] = 0;

    // Step 4. 각 그래프 유형 카운트
    for(int node: nodeNum){
        if(node == newNode) continue;   // 새로운 정점이면 무시
        donutFlag = false, barFlag = false, eightFlag = false;
        if(canGoNum[node]){
            if(canGoNum[node]==2) eightCount1++;
            if(graph[node].empty()){ // 만약 현재 노드에서 나가는 노드가 없다면 막대모양임
                barFlag = true;
                barCount1++;
            }
            if(graph[node].size() == 1 && graph[node].find(node) != graph[node].end()) {
                donutFlag = true;
                donutCount1++;
            }
            canGoNum[node]--; // 하나 감소시키고
            // 연결된 모든 노드 돌기
            DFS(node);
            if(barFlag==false && eightFlag == false && donutFlag == false)
                donutCount1++;
                
        }

    }
    return {newNode, donutCount1, barCount1, eightCount1};
}
