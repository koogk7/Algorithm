import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;


class ACM2023 {
    /*
        2023 신기한 소수, 14:54
        신기한 소수 --> 왼쪽부터 1자리, 2자리... 모두 소수
        N = 8 ( 자릿수 ), 신기한 소수를 오름차순으로 정렬해서 출력
        가장 큰 수 10^8
        7331 -->

        Solution 1
        1. 소수를 미리 다 구한다.
        2. 숫자마다 신기한 소수인지 체크 ==> 10^8 * 8
            2-1. 숫자 자릿수로 분해 ( 8 )
        ==> 10^8 --> Java는 int 배열 최대 크기를 10^7으로 제한, c++로 해도 메모리초과 뜸

        Solution 2
        DFS로 탐색, 시작 숫자는 반드시 2,3,5,7로 해야함
        탐색하면서 다음 숫자가 prime인지 체크!

     */
    static int N;
    static int[] canStarts = {2,3,5,7};

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        for (int i = 0; i < canStarts.length; i++) {
            dfs(canStarts[i], 1);
        }

    }

    public static void dfs(int number, int depth) {
        if(depth == N){
            System.out.println(number);
        }

        for (int i = 1; i < 10; i++) {
            if(i%2 == 0) continue;; // 짝수
            int nextNumber = number*10 + i;
            if(!isPrime(nextNumber)) continue;
            dfs(nextNumber, depth+1);
        }
    }

    public static boolean isPrime(int number){
        if(number == 0 || number == 1) return false;

        for (int i = 2; i*i <= number; i++) {
            if(number % i == 0)
                return false;
        }

        return true;
    }

    /*
        에라토스테네스의 체
     */
    public static boolean[] getPrimes(int end) {
        boolean[] ret = new boolean[end+1];
        ret[0] = false;
        ret[1] = false;
        for (int i = 2; i < end+1; i++) {
            ret[i] = true;
        }

        for (int i = 2; i < end+1; i++) {
            if(!ret[i]) continue;
            for (int j = i*i; j < end+1 ; j +=i) {
                ret[j] = false;
            };
        }
        return ret;
    }


}
