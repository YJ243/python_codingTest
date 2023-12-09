/*
 * 2023.12.08
 * 각 사람마다 실제 갈 수 있는 자리의 위치를 HashSet으로 관리
 * => 중복해서 세지 않으면서도 빠르게 위치를 추가
 * => 최종적으로 갈 수 있는 서로 다른 위치의 수를 HashSet의 크기를 가지고 구해줌
 * 3K번에 걸쳐 실제 시뮬레이션을 진행하며 자리를 교환하는 두 사람에 대해서만 HashSet에 값 갱신
 * 총 시간복잡도 O(N+K)
*/



#include <iostream>
#include <unordered_set>
using namespace std;

#define MAX_N 100000
#define MAX_K 100000

// 변수 선언
int n, k;
int a[MAX_K], b[MAX_K];
int arr[MAX_N+1];
int ans[MAX_N+1];
unordered_set<int> s[MAX_N+1];

int main(){
    // 입력:
    cin >> n >> k;
    for(int i=0; i<k; i++)
        cin >> a[i] >> b[i];
    
    // 시작 array를 arr에 표시하기
    for(int i=1; i<=n; i++){
        arr[i] = i;
        // 각 i 숫자가 위치할 수 있는 자리를 HashSet에 넣어 저장
        s[i].insert(i);
        ans[i] = 1;
    }

    // 3k번 자리를 바꿈
    for(int cnt = 0; cnt<3; cnt++){
        for(int i=0; i<k; i++){
            // a[i]와 b[i]의 자리를 바꿔주기
            // 이때 자리가 변화한 값은 arr[a[i]]와 arr[b[i]] 밖에 없음
            // 이 값들만 새로운 자리를 HashSet에 넣어 저장
            
            // ex)  1번 자리에 a[i] 앉은 1번arr[a[i]]은 2번 b[i]자리로
            // ex)  2번 자리에 b[i] 앉은 2번arr[b[i]]은 1번 a[i]자리로
            swap(arr[a[i]], arr[b[i]]);

            // 만약 해쉬맵의 2번 애가 처음 1번 자리에 앉았다면
            if(s[arr[a[i]]].find(a[i]) == s[arr[a[i]]].end()){
                s[arr[a[i]].insert(a[i]);   // 그 1번 자리 추가
                ans[arr[a[i]]]++;           // 옮긴 자리 개수 추가
            }

            if(s[arr[b[i]]].find(b[i]) == s[arr[b[i]]].end()){
                s[arr[b[i]]].insert(b[i]);
                ans[arr[b[i]]]++;
            }
        }
    }

    // 3k번 자리를 바꾸면서 각 숫자들이 위치할 수 있는 값들의 개수를 ans 배열에서 확인
    for(int i=1; i<=n; i++)
        cout << ans[i] << '\n';
    return 0;
}
