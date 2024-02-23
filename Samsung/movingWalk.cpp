/*
 * 24.02.22
 * 불안한 무빙 워크
 * 내 풀이
*/

#include <iostream>
#define MAX_N 100

using namespace std;

int n, k;

int safety[MAX_N*2];
bool people[MAX_N*2];
int turn;           // 몇 번째 실험을 진행중이었는지 나타내는 변수

void Input(){       // 입력받는 함수
    cin >> n >> k;      // n: 무빙 워크 길이, k: 실험 종료 조건인 0인 판 개수
    for(int i=0; i<2*n; i++){
        cin >> safety[i];
    }
}

bool IsFinish(){    // 시뮬레이션이 종료되었는지 확인하는 함수
    // 안전성이 0인 칸이 k개 이상이라면 종료
    int zero_cnt = 0;
    for(int i=0; i<2*n; i++){
        if(safety[i] == 0)
            zero_cnt++;
    }
    if(zero_cnt >= k)
        return true;
    return false;
}

void MoveMovingWalk(){      // 시계방향으로 한 칸 회전하기
    int last_safety = safety[(n*2)-1];
    for(int i=n*2-1; i >= 1; i--){
        safety[i] = safety[i-1];
    }
    safety[0] = last_safety;

    bool last_person = people[(n*2)-1];
    for(int i=n*2-1; i >= 1; i--){
        people[i] = people[i-1];
    }
    people[0] = last_person;
    people[n-1] = false;        // 항상 n번째는 탈출시켜주기
}

void MovePersonInWalk(){
    bool last_person = people[(n*2)-1];
    bool last_vacant = true;
    if(!last_person){    // 맨 마지막 자리에 사람이 없다면
        for(int i=(n*2)-1; i >= 1; i--){
            if(people[i-1] == false)                    // 사람이 있는 경우에만 옮기기
                continue;      
            if(people[i] == true || safety[i] == 0)     // 만약 옮겨야 될 자리에 사람이 있거나 안정성이 0이라면 X
                continue;

            people[i] = people[i-1];
            people[i-1] = false;    // 옮겼으면 비워주기
            safety[i]--;
        }
    }
    else{           // 맨 마지막 자리에 사람이 있다면
        // 0번 자리로 옮길 수 있는지 확인
        bool last_person_can_go = true;
        // 1. 만약 0번째 안정성이 0이면 아예 가지 못함
        if(safety[0] == 0)  last_person_can_go = false;    // 움직이지 않는다는 의미로 마지막은 비지 않음
        // 2. 안정성이 0이 아니라면
        else{
            if(people[0] == true){
                people[2*n-1] = false;
                // 그런데 사람이 있다면
                // 2-1. 한번 옮겨 보고 people[0] 이 true라면 last는 움직일 수 없음.
                bool ismoved[2*n];     // 옮겨졌는지 확인
                for(int i=0; i<2*n-1; i++)
                    ismoved[i] = false;
                for(int i=n*2-1; i >= 1; i--){
                    if(people[i-1] == false)    // 만약 옮길 사람이 없다면 넘어가기
                        continue;
                    if(people[i] == true || safety[i] == 0)     // 만약 옮겨져야 할 곳에 사람이 있거나 안전성이 0이면 
                        continue;
                    ismoved[i-1] = true;   // 옆으로 옮겨졌다고 표시
                }
                if(ismoved[0] == false){
                    // 옮겨지지 않았다면 temp[0]은 그 자리에 있어야 함, 즉 마지막 아이 움직일 수 없음
                    last_person_can_go = false;
                }
                people[2*n-1] = true;
            }
            if(last_person_can_go){
                // 만약 맨 마지막 사람이 맨 첫번째로 움직일 수 있다면
                // 하나씩 이동하고 원래대로 바꿔줌
                for(int i=n*2-1; i >= 1; i--){
                    if(people[i-1] == false)                    // 사람이 있는 경우에만 옮기기
                        continue;      
                    if(people[i] == true || safety[i] == 0)     // 만약 옮겨야 될 자리에 사람이 있거나 안정성이 0이라면 X
                        continue;
                    people[i] = people[i-1];
                    safety[i]--;
                }
                people[0] = last_person;
                safety[0]--;
            }
            
            else{
                // 마지막 사람 움직일 수 없다면 그대로 두기
                for(int i=n*2-2; i >= 1; i--){
                    if(people[i-1] == false)
                        continue;
                    if(people[i] == true || safety[i] == 0)
                        continue;
                    people[i] = people[i-1];    // 움직인 곳  safety 감소시키기
                    people[i-1] = false;
                    safety[i]--;
                }
            }
        }
        
    }
    people[n-1] = false;        // 항상 n번째는 탈출시켜주기
}

void UptoFirstPerson(){
    if(people[0] == false && safety[0] != 0){
        people[0] = true;
        safety[0]--;
    }
}

void Simulate(){
    // Step 1. 무빙워크 한 칸 회전
    MoveMovingWalk();

    // Step 2. 무빙워크 올라간 사람부터 한 칸 이동
    MovePersonInWalk();

    // Step 3. 1번 칸에 사람을 올릴 수 있다면 올리기
    UptoFirstPerson();
}

int main() {
    // 입력받기
    Input();    

    // 시뮬레이션 진행
    while(true){
        if(IsFinish())
            break;
        turn++;
        Simulate();
    }
    // 출력하기
    cout << turn << '\n';
    return 0;
}