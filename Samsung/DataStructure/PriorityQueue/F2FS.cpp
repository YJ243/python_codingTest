/*
 * 2023.12.06
 * 내 풀이 (통과X)
*/
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

#define MAX_N 100000
using namespace std;

int N;
int stay_time[MAX_N];       // 머무르는 시간
int min_time = 10000;       // 최소 시간
int open_time, cur_idx;      // 정원이 열리는 현재 시간, 현재 정원에 들어가 있는 번호

priority_queue<pair<int, int> > front_pq;        // 정원 앞의 pq
priority_queue<int> waiting_time;    // 기다리는 시간, 제일 큰 애가 나오도록

unordered_map<int,int> arrive_time; // key: 번호, value = 도착시간


bool cmp(pair<int, int>& a, pair<int, int>& b)
{
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second < b.second;
}

int main() {
    // 0. 입력
    cin >> N;
    for(int i=0; i<N; i++){
        // 도착 시간 저장 (hashmap, key=번호, value=시간)
        int arrive = 0;
        cin >> arrive;
        arrive_time[i] = arrive;

        // 머무는 시간 저장
        cin >> stay_time[i];
    }

    // 1. 도착 시간 정렬 (hahsmap의 value 오름차순으로 정렬)
    vector<pair<int, int>> vec(arrive_time.begin(), arrive_time.end()); // map을 vector로 변경

    sort(vec.begin(), vec.end(), cmp);
    //for(vector<pair<int,int> >::iterator it = vec.begin(); it != vec.end(); it++){
    //    cout << it->first << ' ';
    //}
    // 2. hashmap 1번부터 n번까지 보는데, (도착시간 순으로)
    for (auto elem : vec)
    {
        int tmp_idx=elem.first, tmp_arrive=elem.second;

        //  2-1. 도착 시간이 정원이 열리는 현재 시각보다 이후라면
        if(open_time<tmp_arrive){
            if(waiting_time.empty()){    // 맨 처음에 바로 들어갈 수 있는 경우 바로 정원 들어가기

                // 기다리는 시간 = 0, 정원이 열리는 시간 업데이트해주기
                waiting_time.push(0);
                open_time += tmp_arrive+stay_time[tmp_idx];
                //cout << "initial_open" << open_time << '\n';
            }

            else{   // 맨 처음이 아니라면
                front_pq.push(make_pair(-tmp_idx, tmp_arrive));

                // front_pq에 들어가 있는 애들 다 빼고 처리한 다음
                while(!front_pq.empty()){
                    int candidate_idx, candidate_time;
                    tie(candidate_idx, candidate_time) = front_pq.top();
                    candidate_idx *= -1;
                    front_pq.pop();
                    open_time = max(open_time, candidate_time);
                    int wait = max(0,open_time-candidate_time);
                    waiting_time.push(wait);
                    open_time += stay_time[candidate_idx];
                    //cout << candidate_idx << ' ' << open_time <<' ' <<candidate_time << ' ' <<wait<<'\n';
                }
                // 그 이후에 대기큐에 넣어주기
            }
        }
        
        //  2-2. 도착 시간이 정원이 열리는 현재 시각보다 이전이라면 pq에 들어가기 
        else{
        // 번호표의 숫자가 작은 사람부터 들어갈 수 있으니, 번호표의 숫자가 작은 애부터 나오도록 minheap으로 구현
            front_pq.push(make_pair(-tmp_idx, tmp_arrive));        // 정원 앞의 pq
            //cout << tmp_idx << ' ' << open_time << '\n';
        }
    }
    // 끝나고 남아있다면
    while(!front_pq.empty()){
        int candidate_idx, candidate_time;
        tie(candidate_idx, candidate_time) = front_pq.top();
        candidate_idx *= -1;
        front_pq.pop();
        waiting_time.push(open_time-candidate_time);
        open_time += stay_time[candidate_idx];
    }
    cout << waiting_time.top();
    return 0;
}