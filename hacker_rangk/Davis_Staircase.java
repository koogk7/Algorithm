import java.util.Scanner;

public class HR_DavisStaircase {
    static int stepPerms(int n) {
        long[] cache = new long[n+1];
        long moduler = 10000000007L;
        if(n == 1)
            return 1;
        cache[0] = 1L;
        cache[1] = 1L;
        cache[2] = 2L;

        for(int i = 3; i <= n; i++){
            cache[i] = cache[i-1] + cache[i-2] + cache[i-3];
            cache[i] %= moduler;
        }
        return (int)cache[n];
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int s = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int sItr = 0; sItr < s; sItr++) {
            int n = scanner.nextInt();
            scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

            int res = stepPerms(n);

            bufferedWriter.write(String.valueOf(res));
            bufferedWriter.newLine();
        }

        bufferedWriter.close();

        scanner.close();
    }
}
