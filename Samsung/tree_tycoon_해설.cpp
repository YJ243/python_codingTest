/*
 * 2024.02.21
 * �� Ǯ��
*/

#include <iostream>
#include <tuple>

#define MAX_N 15
#define DIR_NUM 8

using namespace std;

int n, m;
int height[MAX_N][MAX_N];

bool fertilizer[MAX_N][MAX_N];
bool next_fert[MAX_N][MAX_N];

// �������� �־��� ������� �� �� �� �� �� �� �� ��
int dx[DIR_NUM] = {0, -1, -1, -1,  0,  1, 1, 1};
int dy[DIR_NUM] = {1,  1,  0, -1, -1, -1, 0, 1};

void InitFertilizer() {
    for(int i = n - 2; i < n; i++)
        for(int j = 0; j < 2; j++)
            fertilizer[i][j] = true;
}

pair<int, int> NextPos(int x, int y, int d, int p){
    int nx = (x + dx[d]*p + n*p) % n;
    int ny = (y + dy[d]*p + n*p) % n;

    return make_pair(nx, ny);
}

void Move(int d, int p){
    // Step 1. �� ���� fert ��ġ�� ������ next_fert�� �ʱ�ȭ�Ѵ�.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_fert[i][j] = false;

    // Step 2. �� �������� �̵���Ų��.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(fertilizer[i][j]){
                int nx, ny;
                tie(nx, ny) = NextPos(i, j, d, p);
                next_fert[nx][ny] = true;
            }
        }
    
    // Stpe 3. next_fert ���� fert�� �Ű��ֱ�
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            fertilizer[i][j] = next_fert[i][j];
}

void Grow(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(fertilizer[i][j])
                height[i][j]++;
}

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int GetDiagCnt(int x, int y){
    int cnt = 0;
    for(int i = 1; i < DIR_NUM; i += 2) {
        int nx = x + dx[i], ny = y + dy[i];
        if(InRange(nx, ny) && height[nx][ny] >= 1)
            cnt++;
    }

    return cnt;
}

void DiagonalGrow(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(fertilizer[i][j]){
                int cnt = GetDiagCnt(i,j);
                height[i][j] += cnt;
            }
}

void DetermineFert(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            // ���� Ư�� �������� �����ְ�
            if(fertilizer[i][j])
                fertilizer[i][j] = false;
            // ���ο� Ư�� �������� �߰����ֱ�
            else if(height[i][j] >= 2){
                fertilizer[i][j] = true;
                height[i][j] -= 2;
            }
        }
}

void Simulate(int d, int p){
    // Step 1. Ư�� �������� �̵���Ų��.
    Move(d, p);

    // Step 2. Ư�� ������ ��ġ�� �ִ� ����ν��� �����Ѵ�.
    Grow();

    // Step 3. �밢�� ������ ���̰� 1 �̻��� ����ν� ��ŭ �� �����Ѵ�
    DiagonalGrow();

    // Step 4. ���ο� Ư�� �������� �߰��ϰ�, ���� �������� �����ش�.
    DetermineFert();
}

int GetScore(){
    int sum = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            sum += height[i][j];
    return sum;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> height[i][j];
    
    InitFertilizer();

    // m���� ���� �ùķ��̼��� �����Ѵ�.
    while(m--){
        int d, p;
        cin >> d >> p;

        Simulate(d-1, p);
    }

    int ans = GetScore();
    cout << ans;

    return 0;
}