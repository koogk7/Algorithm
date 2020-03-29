import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class HR_ArrayManipulation {
    /*
    1 5 3 ==>  1,5,3
    4 8 7 ==>  1,4,10,
    4 9 4 ==>  1,5,3 4,5,10, 6,8,7,
    [3,0,0,0,0,-3],
    [3,0,0,7,-3,0,0,0,-7]

    */

    static long arrayManipulation(int n, int[][] queries) {
        long ans = 0;
        long[] prefixSums = new long[n+1];

        for(int i=0; i< queries.length; i++){
            int startIdx = queries[i][0] - 1;
            int endIdx = queries[i][1];
            int addSum = queries[i][2];

            prefixSums[startIdx] += addSum;
            prefixSums[endIdx] -= addSum;
        }

        long beforeAccSum = 0;
        for(int i = 0; i< n; i++){
            beforeAccSum += prefixSums[i];
            ans = Math.max(ans, beforeAccSum);
        }

        return ans;
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] nm = scanner.nextLine().split(" ");

        int n = Integer.parseInt(nm[0]);

        int m = Integer.parseInt(nm[1]);

        int[][] queries = new int[m][3];

        for (int i = 0; i < m; i++) {
            String[] queriesRowItems = scanner.nextLine().split(" ");
            scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

            for (int j = 0; j < 3; j++) {
                int queriesItem = Integer.parseInt(queriesRowItems[j]);
                queries[i][j] = queriesItem;
            }
        }

        long result = arrayManipulation(n, queries);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedWriter.close();

        scanner.close();
    }
}
