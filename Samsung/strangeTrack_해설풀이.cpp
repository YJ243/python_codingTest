/*
 * 2024.03.06
 * 이상한 원판
 * 해설 풀이
 * 회전하는 부분에 대한 처리 때문에 전체 원판을 각각 회전시키는 데 최대 O(N*M) 시간이 걸린다.
 * 인접한 수치를 확인하여 제거하는 부분에 O(N * M) 시간이 걸림, 정규화 처리에서도 마찬가지
 * 이 모든 과정을 Q회 수행하므로, 전체 시간복잡도는 O(Q*N*M)
*/

#include <iostream>

#define MAX_NUM 50
#define DIR_NUM 4
#define BLANK 0
#define CW 0
#define CCW 1

using namespace std;

int n, m, q;
int plate[MAX_NUM][MAX_NUM];
int temp[MAX_NUM];
bool removed[MAX_NUM][MAX_NUM];

void Shift(int row, int d, int k){
    // Step 1. temp 배열을 초기화한다.
    for(int col = 0; col < m; col++)
        temp[col] = BLANK;
    
    // Step 2. 회전을 진행한다.
    // 시계방향 회전시에는, 1차원 배열을 오른쪽으로 k칸 밀어준다고 생각할 수 있다.
    if(d == CW){
        for(int col = 0; col < m; col++)
            temp[(col+k)%m] = plate[row][col];
    }
    else{
        for(int col = 0; col < m; col++)
            temp[(col-k)%m] = plate[row][col];
    }

    // Step 3. 회전 이후의 결과인 temp 값을 다시 plate에 옮겨준다.
    for(int col = 0; col < m; col++)
        plate[row][col] = temp[col];
}

void Rotate(int x, int d, int k){
    // x 배수에 대해서만 밀어주는 작업을 진행한다.
    for(int i=0; i<n; i++)
        if((i + 1) % x == 0)
            Shift(i, d, k);
}

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

bool Remove(){
    bool is_removed = false;

    int dx[DIR_NUM] = {1,-1,0,0};
    int dy[DIR_NUM] = {0,0,1,-1};

    // Step 1. removed 배열을 초기화한다.
    for(int x=0; x<n; x++)
        for(int y=0; y<m; y++)
            removed[x][y] = false;

    // Step 2. 인접한 숫자 중 같은 쌍을 찾아
    // 지워야 한다는 표시를 한다.
    // 이때, 열에 대해서는 원형으로 이루어진 판이기 때문에
    // 양쪽 경계에서 인접한 곳의 위치를 구하는 부분에 유의한다.
    for(int x=0; x<n; x++)
        for(int y=0; y<m; y++){
            if(plate[x][y] == BLANK) continue;

            for(int k=0; k<4; d++){
                // 열에 대해서는 원형으로 이어져있다.
                int nx = x + dx[k], ny = (y + dy[k] + m)%m;
                if(InRange(nx, ny) && plate[nx][ny] == plate[x][y])
                    removed[x][y] = removed[nx][ny] = true;
            }
        }

    // Step 3. 지워야 할 부분들을 전부 지워준다.
    for(int x=0; x<n; x++)
        for(int y=0; y<m; y++){
            if(removed[x][y]){
                is_removed = true;
                plate[x][y] = BLANK;
            }
        }
    return is_removed;
}

void Normalize(){
    int total_sum = 0, cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(plate[i][j] != BLANK) {
                total_sum += plate[i][j];
                cnt++;
            }
    
    // 남아 있는 숫자가 있을 경우에만 정규화를 진행합니다.
    if(cnt > 0) {
        int avg = total_sum / cnt;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) {
                if(plate[i][j] == BLANK)
                    continue;
                
                if(plate[i][j] < avg)
                    plate[i][j]++;
                else if(plate[i][j] > avg)
                    plate[i][j]--;
            }
    }
}

void Simulate(int x, int d, int k){
    // Step 1. 회전을 진행한다.
    Rotate(x, d, k);

    // Stpe 2. 인접하며 동일한 숫자를 찾아 지운다.
    bool is_removed = Remove();

    // Step 3. 지워진 숫자가 없다면, 정규화를 진행한다.
    if(!is_removed)
        Normalize();
}

int main(){
    cin >> n >> m >> q;

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> plate[i][j];
    
    // q번에 걸쳐 시뮬레이션을 진행한다.
    while(q--){
        int x, d, k;
        cin >> x >> d >> k;
        Simulate(x, d, k);
    }

    int ans = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(plate[i][j] != BLANK)
                ans += plate[i][j];
    cout << ans;
    return 0;
}