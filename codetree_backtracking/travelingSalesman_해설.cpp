/*
 * 2024.03.26
 * 해설 풀이
 * backtracking을 사용하여 1로 시작하는 가능한 모든 순열을 탐색
 * 모든 순열에 대해 비용 합을 계산하여 그 중 최솟값을 찾는다.
 * 유의할 점은 1) 끝에 다시 1번 지점으로 돌아오는 처리를 꼭 해야함 
 * 2) 비용을 더하는 도중 비용이 0인 경우가 있다면 불가능한 경우이니 답으로 갱신하면 안됨
 * 가능한 순열이 N!인데, 순열을 만든 이후 각각 n개의 지점을 보며 비용의 합을 구해줘야 하므로 
 * 총 시간복잡도: O(N!*N)
*/

#include <iostream>
#include <vector>
#include <climits>

#define MAX_N 10

using namespace std;

// 변수 선언
int n;
int cost[MAX_N][MAX_N];