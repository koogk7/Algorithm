import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

class ACM1965 {
    /* 1965 상자넣기  20.03.14
       - 앞에 상자가 뒤에 상자보다 작으면 뒤에 상자에 넣을 수 있음
       - 한번에 넣을 수 있는 최대의 상자 개수를 출력
       - 상자의 개수 n = 1000

       1 6 2 5 7 3 5 6
       1,2,3,5,6 ==> 5
       증가하는 수열을 찾는 문제네
       cache[i] ==> 길이가 i인 수열의 끝 숫자
       1,6 // cache[1] = 1, cache[2] = 6
       1,2 // cache[1] = 1, cache[2] = 2
       1,2,5 // cache[1] = 1, cache[2] = 2, cache[3] = 5
       1,2,5,7 // cache[1] = 1, cache[2] = 2, cache[3] = 5, cache[4] = 7
       1,2,3,5
       1,2,3,5,6
       lowerBound => logN

       Logic
       1-1. 현재 최장 수열의 끝보다 크면 다음 cache 인덱스에 삽입
       1-2. 작으면
        2. lowerbound보다 작으면 갱신, 크면 패스
     */
    static int n;
    static int cache[];

    static int lowerBound(int arr[],int start, int end, int key){
        int mid;
        while(start < end){
            mid = (start + end) / 2;
            if(arr[mid] < key) start = mid + 1;
            else end = mid;
        }
        return end;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer str = new StringTokenizer(br.readLine());
        n = Integer.parseInt(str.nextToken());

        cache = new int[n+1];
        int curCnt = 1;
        int input;

        cache[0] = -1;
        for (int i = 1; i < n+1; i++) {
            cache[i] = Integer.MAX_VALUE;
        }
        str = new StringTokenizer(br.readLine());

        for (int i = 1; i < n+1; i++) {
            input = Integer.parseInt(str.nextToken());
            if(cache[curCnt] < input){
                curCnt++;
                cache[curCnt] = input;
            } else {
                int lowerBoundIdx = lowerBound(cache, 0, n, input);
                cache[lowerBoundIdx] = Math.min(cache[lowerBoundIdx], input);
            }
        }

        System.out.println(curCnt);
    }
}

