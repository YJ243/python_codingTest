/*
 * 2023.12.04
 * 좌표 x,y에 대한 배열이 있을 때 곱이 최대가 되는 경우 -> 원하는 우선순위에 들어가야 함
*/

// 1. 첫번째 방법: 곱에 해당하는 값을 직접 만들어 객체의 첫번째 값으로 설정
/*
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

int main(){
    vector<pair<int, int> > points= {
        {1,7}, {3,2}, {3,1}, {6,2}
    };
    int n = 4;

    priority_queue<tuple<int, int, int> > pq;
    for(int i=0; i<n; i++){
        int x = points[i].first, y = points[i].second;
        pq.push(make_tuple(x*y, x, y));             // priority_queue에 넣어주기
        tuple<int, int, int> best_thing = pq.top(); // x*y, x, y 순으로 가장 우선순위가 높은 경우를 찾아줌

        int px, py;
        tie(ignore, px, py) = best_thing;           // 우리가 원하는 x,y 값만 tuple로부터 가져와줌
        cout << px << " " << py << '\n';
    }
    return 0;
}
*/
// 2번째 방법: 값 자체를 추가하지 않고, 직접 custom comparator를 추가해 기준에 따라 priority_queue가 동작하도록 함
// 하나의 정수 값의 최솟값 반환은 greater<int>가 필요하지만, 여기서는 직접 정렬 기준을 명시해놓은 class가 필요
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// custom comparator
// x*y 값이 더 큰게 먼저 나오도록 하는 경우
struct compare{
    bool operator()(pair<int, int> a, pair<int, int> b){
        return a.first*a.second < b.first*b.second; // a의 곱이 작으면 false==우선순위가 높음
    }
}

int main(){
    vector<pair<int, int> > points = {
        {1,7}, {3,2}, {3,1}, {6,2}
    };
    int n = 4;

    // custom comparator에 따라 priority_queue가 동작하도록 함
    priority_queue<pair<int, int>, vector<pair<int, int> >, compare> pq;
    for(int i=0; i<n; i++){
        pq.push(points[i]);     // priority_queue에 넣어주기
        pair<int, int> point = pq.top();    // 가장 우선순위가 높은 경우를 찾아주기

        cout << point.first << " " << point.second << '\n';
    }
}