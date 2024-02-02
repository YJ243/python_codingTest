/*
 * 2024.1.26
 * 2. DoublyLinkedList를 이용한 시뮬레이션
 * 뱀의 상태를 더블링크드리스트를 통해 관리하면 맨 앞에 머리를 추가하는 시간과 뒤의 꼬리를 자르는 시간이 모두 O(1)
 * solution 1에서는 뱀의 머리 부분을 맨 앞에 추가하는 과정에서 시간이 O(N^2)
 * 뱀의 몸통에 대해 수행하는 연산 = 맨 뒤 꼬리를 삭제 & 맨 앞에 새로운 머리를 추가하고
 * 겹치는지 확인하기 위해 각 몸통 순회
 * 따라서 DLL을 이용하여 머리 부분을 추가하는 시간을 O(1)로 줄일 수 있음
 * 단 SLL을 사용하면 tail을 삭제하는데 시간이 O(N)이 소요되므로, 꼭 DLL을 이용해 해결해야 삽입/삭제 시간이 모두 O(1)
 * 하지만, 겹치는지 확인하기 위해서는 Solution1과 마찬가지로 뱀의 모든 위치를 확인해야하므로 시간복잡도는 1과 같음 
*/
#include <iostream>
#include <list>

#define MAX_NUM 100
#define ASCII_NUM 128

using namespace std;

int n, m, K;
bool apple[MAX_NUM+1][MAX_NUM+1];

list<pair<int, int> > snake;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

int mapper[ASCII_NUM];

int ans;

// (x, y)가 범위 안에 들어가는지 확인합니다. 
bool CanGo(int x, int y) {
    return x >= 1 && y >= 1 && x <= n && y <= n;
}

// 뱀이 꼬였는지 확인
bool IsTwisted(pair<int, int> newHead){
    // 뱀이 꼬였는지 여부는
    // 새로 들어올 머리가 기존 뱀의 몸통과 부딪히는지만 확인하면 됨
    // 머리와 그 부분이 겹치는 경우 treu를 반환
    list<pair<int, int> >:: iterator it;
    for(int it=snake.begin(); it != snake.end(); it++)
        if(newHead == (*it))
            return true;
    // 겹치지 않는 경우에는 false를 반환
    return false;
}

// 새로운 머리를 추가하기
bool PushFront(pair<int, int> newHead){
    // 몸이 꼬이는 경우
    // false를 반환
    if(IsTwisted(newHead) == true)
        return false;

    // 새로운 머리를 추가하기
    snake.insert(snake.begin(), newHead);

    // 정상적으로 머리를 추가했다는 의미로
    // true를 반환
    return true;
}


// 꼬리를 지우기
void PopBack(){
    snake.pop_back();
}

// (nx,ny) 쪽으로 뱀을 움직이기
bool MoveSnake(int nx, int ny){
    // 머리가 이동할 자리에 사과가 존재하면
    // 사과가 사라지고 
    if(apple[nx][ny]){
        apple[nx][ny] = false;
        // 꼬리는 사라지지 않고 머리만 늘어남
        // 늘어난 머리때문에 몸이 꼬이면 false 반환
        if(PushFront(make_pair(nx,ny)) == false)
            return false;
    }
    else{
        // 사과가 없으면 꼬리는 사라지게 되고
        PopBack();

        // 머리는 늘어나게 됨
        // 늘어난 머리때문에 몸이 꼬이면 false 반환
        if(PushFront(make_pair(nx,ny)) == false)
            return false;       
    }
    // 정상적으로 뱀이 움직였으므로
    // true를 반환
    return true;
}

// 뱀을 dir 방향으로 num번 움직이기
bool Move(int dir, int num){
    // num 횟수만큼 뱀을 움직임
    // 한 번 움직일 때마다 답을 갱신
    while(num--){
        ans++;

        pair<int, int> head = snake.front();

        // 뱀의 머리가 그 다음으로 움직일 위치를 구하기
        int nx = head.first + dx[dir];
        int ny = head.second + dy[dir];

        // 그 다음 위치로 갈 수 없다면 게임을 종료
        if(CanGo(nx,ny) == false)
            return false;
        

        // 뱀을 한 칸 움직이기
        // 만약 모이 꼬인다면 false를 반환
        if(MoveSnake(nx,ny) == false)
            return false;
    }
    // 정상적으로 명령을 수행했다는 의미인 true를 반환
    return true;
}

int main(){
    // 입력으로 주어진 방향을 정의한 dx, dy에 맞도록 변환하는데 쓰이는 배열을 정의하기
    mapper['D'] = 0;
    mapper['U'] = 1;
    mapper['R'] = 2;
    mapper['L'] = 3;

    // 입력:
    cin >> n >> m >> K;
	
    // 사과가 있는 위치를 표시합니다.
	for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        apple[x][y] = true;
	}

    // 뱀은 처음에 (1,1)에서 길이 1의 상태로 있음
    snake.push_back(make_pair(1,1));

    // K개의 명령을 수행하기
    for(int i=0; i<K; i++){
        // dir 방향으로 num횟수만큼 움직여야 함
        char dir; int num;
        cin >> dir >> num;

        // 움직이는 도중 게임이 종료되었을 경우
        // 더이상 진행하지 않음
        if(Move(mapper[dir], num) == false)
            break;
    }
    // 출력:
    cout << ans;
    return 0;
}