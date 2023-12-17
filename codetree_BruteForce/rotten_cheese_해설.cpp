/*
 * 2023.12.17
 * 모든 치즈에 대해 해당 치즈가 상했을 때 아픈 사람의 수를 구하는 BF
 * 사람이 치즈를 먹지 않았거나, 아프기 시작한 순간이 치즈를 먹은 순간보다 빠르다면 모순
 * 1. 각각의 치즈가 상했다고 가정했을 때 아플 수 있는 최대 사람의 수를 구하기
 * 2. 각 사람이 가장 먼저 치즈를 먹은 시간을 저장
 * 3. 저장한 값과 단서를 비교했을 때 모순이 발생하면 해당 치즈는 상할 수 없음, 답에서 제외시키기
*/

#include <iostream>
#include <algorithm>

#define MAX_D 1000
#define MAX_N 50

using namespace std;

// 치즈를 먹은 정보를 나타내는 클래스 선언
class Info1{
    public:
        int p, m, t;
        Info1(int p, int m, int t){
            this->p = p;
            this->m = m;
            this->t = t;
        }
        Info1(){}
};

// 치즈를 먹은 정보를 나타내는 클래스 선언
class Info2{
    public:
        int p, t;
        Info2(int p, int t){
            this->p = p;
            this->t = t;
        }
        Info2(){}
};

Info1 info1[MAX_D];
Info2 info2[MAX_N];

int n, m, d, s;

int main(){
    // 입력
    cin >> n >> m >> d >> s;
    for(int i=0; i<d; i++){
        int p, m, t;
        cin >> p >> m >> t;
        info1[i] = Info1(p,m,t);
    }
    for(int i=0; i<s; i++){
        int p,t;
        cin >> p >> t;
        info2[i] = Info2(p, t);
    }

    int ans = 0;

    // 하나의 치즈가 상했을 때 필요한 약의 수의 최댓값을 구하기
    for(int i=1; i<=m; i++){
        // i번째 치즈가 상했을 때 필요한 약의 수를 구하기

        // 우선 i번째 치즈가 상했다고 가정할 때 모순이 발생하지 않는지 확인하기
        // time 배열을 만들어 각 사람이 언제 치즈를 먹었는지 저장하기
        int time[MAX_N+1] = {};
        for(int j=0; j<d; j++){
            // i번째 치즈에 대한 정보가 아닌 경우 넘어가기
            if(info1[j].m != i)     // 해당 치즈를 먹은 경우가 아니면 고려하지 않기
                continue;
            
            // person이 ㅑ번째 치즈를 처음 먹었거나
            // 이전보다 더 빨리 먹게 된 경우 time 배열을 갱신
            int person = info1[j].p;        // 상한 치즈를 먹은 사람 인덱스
            if(time[person] == 0)
                time[person] = info1[j].t;
            else if(time[person] > info1[j].t)
                time[person] = info1[j].t;
        }

        // possible: i번째 치즈가 상했을 수 있으면 true, 아니면 false
        bool possible = true;
        for(int j=0; j<s; j++){
            // person이 i번째 치즈를 먹지 않았거나
            // i번째 치즈를 먹은 시간보다 먼저 아픈 경우 모순
            int person = info2[j].p;
            if(time[person] == 0)
                possible = false;
            if(time[person] >= info2[j].t)
                possible = false;
        }

        // 만약 i번째 치즈가 상했을 가능성이 있다면, 몇 개의 약이 필요한지 확인
        int pill = 0;
        if(possible){
            // 한번이라도 i번째 치즈를 먹은 적이 있다면, 약이 필요
            for(int j=1; j<=n; j++){
                if(time[j] != 0)
                    pill++;
            }
        }
        ans = max(ans, pill);
    }
    cout << ans;
    return 0;
}