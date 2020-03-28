import java.util.Scanner;

public class HR_NewYearChoas {
    static void minimumBribes(int[] q) {
        int ans = 0;
        String chaos = "Too chaotic";

        for(int i= q.length-1; i > 0; i--){
            boolean isSwap = q[i-1] > q[i]; // 앞이 더 크면 바꿈
            int swapCnt = 0;
            int swapStartIdx = i;
            if(!isSwap) continue;

            while(isSwap) {
                int buffer = q[swapStartIdx];
                q[swapStartIdx] = q[swapStartIdx-1];
                q[swapStartIdx-1] = buffer;

                swapStartIdx++;
                swapCnt++;
                if(swapCnt > 2) {
                    System.out.println(chaos);
                    return;
                }
                if(swapStartIdx == q.length) break;

                isSwap = q[swapStartIdx-1] > q[swapStartIdx];
            }

            ans += swapCnt;
        }

        System.out.println(ans);
    }



    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int t = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int tItr = 0; tItr < t; tItr++) {
            int n = scanner.nextInt();
            scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

            int[] q = new int[n];

            String[] qItems = scanner.nextLine().split(" ");
            scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

            for (int i = 0; i < n; i++) {
                int qItem = Integer.parseInt(qItems[i]);
                q[i] = qItem;
            }

            minimumBribes(q);
        }

        scanner.close();
    }
}
