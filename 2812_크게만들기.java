import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

class ACM2812 {
    /* 2812 크게 만들기 20.03.14 15:03
       - N자리 숫자에서 숫자 k개를 지워서 얻는 가장 큰 수
       - N, k = 10^5 * 5 ==> nlongn or n

       Solution 1
       1. 1924 ==> 1,9,2,4 형태로 쪼갠 뒤에 min Heap에 저장, heap size는 n-k
       2. pq에서 하나씩 꺼내서 출력 ==> nlog(n-k)
       ===> 문자열의 순서는 변경 할 수 없다!

       Solution 2
       결국 제일 작은 숫자를 지워야 해!
       MaxHeap에 저장, size는 k, 저장 할 때 인덱스도!
       Heap에서 빼면서 isDeleted에 체크!
       number 돌면서 isDeleted false만 출력!
       ===> 작은 숫자만 빼는 것 틀림... 같은 자릿수의 앞자리가 큰 녀석이 와야 해

       Solution 3
       1. input number를 앞에서부터 하나씩 순회하면서 Stack에 저장
         1-1. Stack이 비어있다면 삽입
         1-2. Stack의 Top보다 크면 Stack의 Top과 교환, Top을 제거해준것이므로 k--,
         1-3. 1-2를 현재값보다 큰 top이 나올 때 또는 제거 할 수 있는 수(k)가 0이 될 때까지 반복
         1-4. 현재 값 삽입
       2-1. k가 0이라면 string에 담아서 역순으로 출력
       2-2. k가 0보다 크다면 제거해야 할 수가 남아 있으므로 k만큼 stack에서 pop 뒤에 역순으로 출력
     */
    static int n,k;
    static StringBuffer number;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer str = new StringTokenizer(br.readLine());
        n = Integer.parseInt(str.nextToken());
        k = Integer.parseInt(str.nextToken());
        number = new StringBuffer(br.readLine());

        Stack<Integer> st = new Stack<>();
        StringBuffer ans = new StringBuffer();

        for (int i = 0; i < n; i++) {
            int cur = number.charAt(i) - '0';
            if(st.empty()) {
                st.push(cur);
                continue;
            }

            while (!st.empty() && st.peek() < cur && k > 0) {
                st.pop();
                k--;
            }
            st.push(cur);
        }

        while(k > 0){
            st.pop();
            k--;
        }

        while(!st.empty())
            ans.append(st.pop());

        for (int i = ans.length()-1; i >= 0; i--) {
            System.out.print(ans.charAt(i));
        }
    }
}

