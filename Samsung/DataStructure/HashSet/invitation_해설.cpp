/*
 * 2023.12.09
 * HashSet을 이용해 그룹 별로 초대받지 못한 사람 목록을 관리
 * => 나는 HashSet으로 전체 사람 중에서 초대 받은 사람만 관리하도록 하였었음. 이렇게는 생각 못함. 그냥 리스트랑 해쉬셋 두개 선언하기는 했었음
 * 1. 주어진 사람별 속해있는 그룹 정보를 인접리스트로 만들기
 * 2. 1번 사람을 시작으로 bfs 탐색 진행
 * 3. 큐에 새로운 원소를 추가하게 되는 조건 = 현재 사람 x가 속해 있는 그룹에서 x를 제거했을 때 해당 그룹에 남아있는 사람 수가 1명이 되는 경우
 *      이 때 정확히 k-1명만 초대장을 받게 되는 경우이므로 해당 사람을 queue에 넣어주기
*/

#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;

#define MAX_N 100000
#define MAX_G 250000

// 변수 선언
int n, g;
bool invited[MAX_N];

// 각 그룹마다 초대장을 받지 못한 사람들을 관리
// 그 이유는 각 그룹마다 누가 초대장을 받지 못했는지 순회하는 방식은 시간초과 나기 때문에 
unordered_set<int> groups[MAX_G];
// 각 사람이 어떤 그룹에 속하는지를 관리해주기
vector<int> people_groups[MAX_N];   // i번 사람이 몇번 그룹들에 속해있는지
queue<int> q;
int ans;

int main(){
    // 입력:
    cin >> n >> g;
    for(int i=0; i<g; i++){
        int s, x;
        cin >> s;
        for(int j=0; j<s; j++){
            cin >> x; x--;
            groups[i].insert(x);
            people_groups[x].push_back(i);
        }
    }
    q.push(0);  // 첫번째 번호표에게 초대장 주기
    invited[0] = true;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        ans++;

        // x가 들어있는 그룹에서 x를 지우기
        // hashset에는 그룹에서 초대받지 않은 인원만을 남기기
        for(int i=0; i<(int) people_groups[x].size(); i++){
            int g_num = people_groups[x][i];

            // 해당 그룹에서 x를 지우기
            groups[g_num].erase(x);
            // 초대받지 않은 인원이 한 명밖에 없다면 초대
            if((int) groups[g_num].size() == 1){
                int p_num = *(groups[g_num].begin());
                if(!invited[p_num]){
                    invited[p_num] = true;
                    q.push(p_num);
                }
            }
        }
    }

    // 초대장을 받는 인원 출력
    cout << ans;
    return 0;
}