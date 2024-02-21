/*
 * 2024.02.21
 * ���̱ⱸ ž��
 * �ؼ� Ǯ��
 * ����Ž���� �����ϸ� �� �л��� ��� ��ġ�� �̵��ؾ� �ϴ��� ����� �� ����
 * �� �� (�����ϴ� ģ�� ��, ��ĭ ��, -�� ��ȣ, -�� ��ȣ) ������ ���� ���� ū ������ �̵��ϸ� ��
 * ������ �켱������ ���� ó���� tuple�� �̿��ϸ� ���� �����ϰ� ������ �����ϴ�.
 * n^2���� �л��� ���� n^2�� ũ���� ������ ����Ž���� �����ؾ� �ϹǷ� �� �ð����⵵:O(N^4)
 * ģ������ Ȯ���ϱ� ���� ���� �迭�� ����
 * tuple�� ��!
*/

#include <iostream>
#include <cmath>
#include <tuple>

#define MAX_N 20
#define MAX_NUM 400
#define DIR_NUM 4
#define EMPTY 0

using namespace std;

// ĭ�� ����
typedef tuple<int, int, int, int> Cell;

int n;

int target_num[MAX_NUM + 1];
bool friends[MAX_NUM+1][MAX_NUM+1];

// ���� �ⱸ ž�� ��ȣ
int rides[MAX_N+1][MAX_N+1];

int dx[DIR_NUM] = {-1, 1, 0, 0};
int dy[DIR_NUM] = {0, 0, -1, 1};

bool InRange(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

// num2�� num1�� �����ϴ� ģ������ �Ǵ��մϴ�.
bool IsFriend(int num1, int num2) {
    return friends[num1][num2];
}

// �켱������ ���� ���� ����ϱ� ����
// (�����ϴ� ģ�� ��, �� ĭ�� ��, -�� ��ȣ, -�� ��ȣ)
// ������� ���� �־��ش�.
Cell GetCurrCell(int num, int x, int y){
    int friend_cnt = 0, blank_cnt = 0;
    for(int i=0; i<DIR_NUM; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(!InRange(nx, ny))
            continue;
        if(ridex[nx][ny] == EMPTY)
            blank_cnt++;
        else if(IsFriend(num, rides[nx][ny]))
            friend_cnt++;
    }
    return make_tuple(friend_cnt, blank_cnt, -x, -y);
}

void Move(int num){
    // Step 1. ���� �켱������ ���� ĭ�� �����Ѵ�.
    Cell best_cell = make_tuple(0,0,-(n+1),-(n+1));
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(rides[i][j] == EMPTY){
                Cell curr = GetCurrCell(num, i, j);

                if(best_cell < curr)
                    best_cell = curr;
            }
    // Step 2. �ش� ��ġ�� ž���Ѵ�.
    int x, y;
    tie(ignore, ignore, x, y) = best_cell;
    rides[-x][-y] = num;
}

// (x,y) ��ġ�� �ִ� �л��� ������ ����Ѵ�.
int GetScore(int x, int y){
    int cnt = 0;
    for(int i=0; i<DIR_NUM; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(InRange(nx ,ny) && IsFriend(rides[x][y], rides[nx][ny]))
            cnt++;
    }
    return (int)pow(10, cnt-1);
}

// �� ������ ����Ѵ�.
int GetTotalScore(){
    int score = 0;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            score += GetScore(i,j);
    return score;
}

int main(){
    cin >> n;

    for(int i=1; i<=n*n; i++){
        cin >> target_num[i];

        for(int j=1; j<=4; j++){
            int friend_num;
            cin >> friend_num;

            // ���� ��ȣ�� ģ�� ��ȣ�� ǥ�����ֱ�
            friends[target_num[i]][friend_num] = true;
        }
    }

    // ������� �л����� ���̱ⱸ�� ž�½�Ų��.
    for(int i=1; i<=n*n; i++)
        Move(target_num[i]);
    
    // �� ������ ����Ѵ�.
    int ans = GetTotalScore();
    cout << ans;

}