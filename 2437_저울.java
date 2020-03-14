import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

class ACM2437 {
    /* 2437 저울  20.03.14
       추로 만들 수 있는 수?
       1,2,3을 예로 들어보자
       1만 있을 때 ==> 1
       1,2가 있을 떼 ==> 1,2,(1+2)
       1,2,3이 있을 떼 ==> 1,2,3,(1+3),(2+3),(3+3)
       즉 현재 추가 추가되기 전에 만들 수 있는 무게의 현재추를 더한 것 + 이전 추로 만들 수 있는 무게
       여기서 이전 추에서 만들 수 있는 가장 큰 수 + 1보다 현재 추가 크다면 간격이 생겨버림!

       1. 추들을 오름차순으로 정렬
       2. 추들을 순회하면서 합을 더해간다.
       3. 현재 추가 이전 합 + 1 보다 크면 간격이 생김으로 합 + 1 출력하고 끝
       4. 추들을 다 순회하고나면 현재 합+1 출력
     */
    static int n;
    static ArrayList<Integer> weights;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer str = new StringTokenizer(br.readLine());
        n = Integer.parseInt(str.nextToken());

        int head = 0;
        weights = new ArrayList<>(n);

        str = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {
            weights.add(Integer.parseInt(str.nextToken()));
        }
        Collections.sort(weights);

        for (int i = 0; i < n; i++) {
            if(head + 1 < weights.get(i)){
                System.out.println(head+1);
                return;
            }
            head += weights.get(i);
        }

        System.out.println(head+1);
    }
}

