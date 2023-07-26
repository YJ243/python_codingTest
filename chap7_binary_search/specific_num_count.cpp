#include <iostream>
#include <vector>

using namespace std;
int n, x;
int answer = 0;
int BinarySearch(vector<int>& a, int start, int end, int target){
    if(start >end) return -1;

    int mid = (start+end)/2;
    if(a[mid]== target){
        answer++;
        for(int i=mid-1; i>0; i--){
            if(a[i] == target){
                answer++;
            }
            else
            {
                break;
            }
        }
        for(int i=mid+1; i<n; i++){
            if(a[i] == target)
                answer++;
            else
                {
                    break;
                }
        }
        int ret = answer;
        return ret;
    }
    else if(a[mid]>target) return BinarySearch(a, start, mid-1, target);
    else return BinarySearch(a, mid+1, end, target);
}

int main(){
    cin >> n >> x;
    vector<int> a(n,0);

    for(int i=0; i<n; i++){
        cin >> a[i];
    }

    int result = BinarySearch(a, 0, n-1, x);

    cout << result << '\n';

}