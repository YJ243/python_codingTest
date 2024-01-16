#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#define MAX_NUM 10000

using namespace std;

int s, e;                   // s: 출발 지점, e: 도착 지점
bool visited[MAX_NUM+1];    // 각 노드를 탐색했는지 확인
int ans;                    // 필요한 최소 삼각김밥 개수


void Initialize(){
    // 시작점을 항상 end보다 작게
    if(s>e) swap(s,e);
    // visited 배열 초기화
    for(int i=1; i<=MAX_NUM; i++){
        visited[i] = false;
    }
    ans = 0;    // 정답 0으로 초기화                     

}
/*
tuple<int, int, int> getNumbers(int curr){
    int curLevel = (-1 + sqrt(1+ 4*2*(curr-1)))/2 + 1;
    int first = (curLevel-1)*(curLevel)/2 + 1;
    int last = first + curLevel -1;
    return make_tuple(curLevel, first, last);
}
*/
void bfs(){
    queue<pair<int, int> > q;   // bfs 탐색을 위한 큐 (구역번호, s로부터 이동해온 횟수)
    q.push(make_pair(s,0));
    visited[s] = true;

    while(!q.empty()){
        int curNum, curCnt;
        tie(curNum, curCnt) = q.front();
        q.pop();

        if(curNum == e){    // 만약 큐에서 나온 숫자가 end라면
            ans = curCnt;
            break;
        }
        // 현재 구역에서 갈 수 있는 다음 노드 탐색
        vector<int> next;
        int curL = (-1 + sqrt(1+8*(curNum-1)))/2+1;
        int firstN = (curL-1)*curL/2 + 1;
        int lastN = firstN+curL-1;

        //tie(curL, firstN, lastN) = getNumbers(curNum);
        
        // 1. 현재 줄에서의 +1 값과 연결되어 있다면 넣기
        if(curNum+1 <= lastN && curNum+1 <= MAX_NUM)
            next.push_back(curNum+1);
            /*
        // 2. 현재 줄에서의 -1값과 연결되어 있다면 넣기
        if(curNum-1 >= firstN && curNum-1 <= MAX_NUM)
            next.push_back(curNum-1);
        */
        // 3. 그 다음 줄에서의 연결되어 있는 두 구역
        if(curNum+curL <= MAX_NUM)
            next.push_back(curNum+curL);
        if(curNum+curL+1 <= MAX_NUM)
            next.push_back(curNum+curL+1);
        
        for(int i=0; i<(int)next.size(); i++){
            // 연결되어 있는 구역에 대해서
            int nextNum = next[i];
            //cout << curNum << ' ' << nextNum << '\n';
            if(!visited[nextNum]){     // 방문하지 않은 구역이라면
                if(nextNum == e){    // 만약 큐에서 나온 숫자가 end라면
            		ans = curCnt+1;
            		break;
        		}
                visited[nextNum] = true;
                q.push(make_pair(nextNum, curCnt+1));
                
            }
        }
        if(ans != 0) break;
    }
}

void getShortestPath(){
    
    int startLevel = (-1 + sqrt(1+8*(s-1)))/2+1;
    int endLevel = (-1 + sqrt(1+8*(e-1)))/2+1;

    int e1 = s + (endLevel-1)*(endLevel)/2-(startLevel-1)*(startLevel)/2;
    int e2 = s + (endLevel)*(endLevel+1)/2-(startLevel+1)*(startLevel)/2;

    if(e1 <= e && e <= e2){
        ans = endLevel-startLevel;
    }
    else if(e < e1){
        ans = endLevel-startLevel + (e1-e);
    }
    else if(e > e2){
        ans = endLevel-startLevel+ (e-e2);
    }
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{   
        // 입력 받기
        cin >> s >> e;

        // bfs탐색 수행
        Initialize();
        if(e-s < 3)
        	bfs();
        else{
        	// 만약 level이 3 이상 차이난다면 bfs보다 더 빠르게 수행하도록
            getShortestPath();
        }
        
        // 정답 출력
        cout << "#" << test_case << ' ' << ans << '\n';
	}
	return 0;
}