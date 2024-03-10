/*
 * 2024.02.25
 * 해설 풀이
 * 시간 복잡도는 격자 크기가 n이고 원자의 개수가 최대 n^2개 일 때 각 자리에 대한 원자들의 이동
 * O(N^2)을 K번 시뮬레이션하므로 O(K*N^2)
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define MAX_N 50
#define DIR_NUM 8

using namespace std;

int n, m, k;
vector<tuple<int, int, int> > grid[MAX_N][MAX_N];
vector<tuple<int, int, int> > next_grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> NextPos(int x, int y, int v, int move_dir) {
	int dx[DIR_NUM] = {-1, -1, 0, 1, 1,  1,  0, -1};
	int dy[DIR_NUM] = { 0,  1, 1, 1, 0, -1, -1, -1};
    
    // 움직인 이후 값이 음수가 되는 경우, 이를 양수로 쉽게 만들기 위해서는
    // n의 배수이며 더했을 때 값을 항상 양수로 만들어 주는 수인 nv를 더해주면 됩니다.
    int nx = (x + dx[move_dir] * v + n * v) % n;
    int ny = (y + dy[move_dir] * v + n * v) % n;
    
    return make_pair(nx, ny);
}

void MoveAll() {
    for(int x = 0; x < n; x++)
        for(int y = 0; y < n; y++)
            for(int i = 0; i < (int) grid[x][y].size(); i++) {
                int w, v, move_dir;
                tie(w, v, move_dir) = grid[x][y][i];
                
                int next_x, next_y;
                tie(next_x, next_y) = NextPos(x, y, v, move_dir);
                next_grid[next_x][next_y].push_back(
                    make_tuple(w, v, move_dir)
                );
            }
}

void Split(int x, int y){
    int sum_of_mass = 0;
    int sum_of_velocity = 0;
    int num_of_dir_type[2] = {};

    for(int i = 0; i < (int) next_grid[x][y].size(); i++) {
        int w, v, move_dir;
        tie(w, v, move_dir) = next_grid[x][y][i];
        
        sum_of_mass += w;
        sum_of_velocity += v;
        num_of_dir_type[move_dir % 2]++;
    }

    int start_dir;
    // 전부 상하좌우 방향이거나, 전부 대각선 방향으로만 이루어져 있다면
    // 각각 상하좌우 방향을 갖습니다.
    if(!num_of_dir_type[0] || !num_of_dir_type[1]) 
        start_dir = 0;
    // 그렇지 않다면, 각각 대각선 방향을 갖습니다.
    else
        start_dir = 1;
    
    int atom_cnt = (int) next_grid[x][y].size();
    
    // 각 방향 갖는 원자를 추가해줍니다.
    for(int move_dir = start_dir; move_dir < DIR_NUM; move_dir += 2)
        // 질량이 0보다 큰 경우에만 추가합니다.
        if(sum_of_mass / 5 > 0)
            grid[x][y].push_back(
                make_tuple(sum_of_mass / 5,
                           sum_of_velocity / atom_cnt,
                           move_dir)
            );
}

void Compound(){
    // Step 1. grid 값을 초기화한다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            grid[i][j].clear();

    // Step 2. 합성을 진행한다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            int atom_cnt = (int) next_grid[i][j].size();
            if(atom_cnt == 1)
                grid[i][j].push_back(next_grid[i][j].back());
            // 2개 이상인 경우에는, 분열된다.
            else if(atom_cnt > 1)
                Split(i,j);
        }
}

void Simulate() {
    // Step1. next_grid를 초기화합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            next_grid[i][j].clear();
		
    // Step2. 원자들을 전부 움직입니다.
    MoveAll();
    
    // Step3. 합성이 일어나고, 그 결과를 grid에 저장합니다.
    Compound();
}

int main() {
	cin >> n >> m >> k;
	
	for(int i = 0; i < m; i++) {
		int x, y, m, s, d;
		cin >> x >> y >> m >> s >> d;
        
		grid[x - 1][y - 1].push_back(
            make_tuple(m, s, d)
        );
	}
	
    // k초에 걸쳐 시뮬레이션을 반복합니다.
	while(k--)
		Simulate();
	
	int ans = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
            for(int k = 0; k < (int) grid[i][j].size(); k++) {
                int weight;
                tie(weight, ignore, ignore) = grid[i][j][k];
			    ans += weight;
            }
	
	cout << ans;
	
	return 0;
}