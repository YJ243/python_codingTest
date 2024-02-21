/*
 * 2024.02.21
 * ���̱ⱸ ž��
 * �� Ǯ��
 * �Ǽ�1: n*n�ε� n���� �����ϵ��� �ؼ� runtime ������ ������
 * �Ǽ�2: ó���� ���ڸ� �ְ�, ���Ŀ� ����ִ� ������ �ֵ��� ���ؼ� �ʹݿ� ��� Ʋ�Ⱦ���
*/

#include <iostream>
#include <vector>

#define MAX_N 20

using namespace std;

int n;
int grid[MAX_N][MAX_N];
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
vector<int> turn;
vector<int> like[MAX_N*MAX_N+1];
int max_friend, max_vacant;

int score[5] = {0, 1, 10, 100, 1000};
int total_score;

void Input(){
    cin >> n;
    for(int i=0; i<n*n; i++){
        int n0, n1, n2, n3, n4;
        cin >> n0 >> n1 >> n2 >> n3 >> n4;
        
        turn.push_back(n0);
        like[n0].push_back(n1);
        like[n0].push_back(n2);
        like[n0].push_back(n3);
        like[n0].push_back(n4);
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> FindLoc(int curr){       // curr�� ����� �� ���� �켱������ ���� ��ġ�� ��ȯ�ϴ� �Լ�
    int curr_friend = 0, curr_vacant = 0;
    int nX, nY;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // ���� ĭ���� ������ �� ������ ���鼭 �����ϴ� ģ���� ����ִ� ĭ�� �� ã��
            if(grid[i][j]) continue;            // ���ڰ� �����ִٸ� �н�
            curr_friend = 0, curr_vacant = 0;
            for(int d=0; d<4; d++){
                int nx = i + dirs[d][0], ny = j + dirs[d][1];
                if(InRange(nx, ny)){
                    // ����ִ� ĭ�� �� ����
                    if(grid[nx][ny] == 0)   curr_vacant++;
                    for(int k=0; k<4; k++){
                        // �����ϴ� ģ���� �ִٸ� ����
                        if(grid[nx][ny] == like[curr][k])
                            curr_friend++;
                    }
                }
            }

            if(curr_friend > max_friend || (curr_friend == max_friend && (max_vacant < curr_vacant))){
                max_friend = curr_friend;
                max_vacant = curr_vacant;
                nX = i, nY = j;
            }
        }
    }
    return make_pair(nX, nY);
}

void Simulate(){    // �Է����� �־��� ������� ���� �켱������ ���� ĭ���� ž�½�Ű�� �Լ�
    for(int i=0; i<(int)turn.size(); i++){
        int curr = turn[i];
        //cout << "���� �����ִ� ����: " <<curr << ' ';
        max_friend = -1, max_vacant = -1;
        // 1 ���� ��ġ ã��
        pair<int, int> Next = FindLoc(curr);
        //cout << Next.first << ' ' << Next.second << '\n';
        // 2. �� ��ġ�� ��ȣ �ֱ�
        grid[Next.first][Next.second] = curr;
    }

}   

void UpdateScore(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int curr = grid[i][j];
            int cnt = 0;
            for(int d=0; d<4; d++){
                int nx = i + dirs[d][0], ny = j + dirs[d][1];
                if(InRange(nx, ny)){
                    for(int k=0; k<4; k++){
                        // �����ϴ� ģ���� �ִٸ� ����
                        if(grid[nx][ny] == like[curr][k])
                            cnt++;
                    }
                }
            }
            total_score += score[cnt];
        }
    }
}

int main() {
    // �Է�:
    Input();
    
    // �ùķ��̼� ����
    Simulate();
    // ���� ������Ʈ �ϱ�
    UpdateScore();
    // ���:
    cout << total_score;
    return 0;
}