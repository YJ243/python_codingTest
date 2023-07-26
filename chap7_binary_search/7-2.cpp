#include <iostream>

using namespace std;

// 이진 탐색 소스코드구현(재귀)
int binarySearch(vector<int> &arr, int target, int start, int end){
    if(start > end) return -1;
    int mid = (start+end) / 2;
    // 찾은 경우 중간점 인덱스 반환
    if(arr[mid] == target) return mid;
    // 중간점의 값보다 찾고자 하는 값이 작은 경우 왼쪽 확인

    else if(arr[mid]>target) return binarySearch(arr, target, start, mid-1);
    // 중간점의 값보다 찾고자 하는 값이 큰 경우 오른족 확인
    else return binarySearch(arr, target, mid+1, end); 
}

int n, target;
vector<int> arr;

int main(){
    // n: 원소의 개수, target: 찾고자 하는 값
    cin >> n >> target;
     // 전체 원소 입력 받기
     for(int i=0; i<n; i++){
         int x;
         cin >> x;
         arr.push_back(X);
     }

    // 이진 탐색 수행 결과 출력
    int result =  binarySearch(arr, target, 0, n-1);

    if(result == -1)
        cout << "원소가 존재하지않음" << '\n';
    else
    {
        cout<< result+1 << '\n';
    }
}