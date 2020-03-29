import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class HR_RecursiveDigitSum {
    /*
    p의 범위가 매우 크다. 따라서 n에 대한 superDigit을 먼저 구하고 *k를 해주자
    */
// Complete the superDigit function below.
    static boolean isSuperDigit(String number){
        return number.length() == 1;
    }

    static long caculateSum(String number){
        long sum = 0L;
        for(char digit : number.toCharArray()){
            sum += digit - '0';
        }
        return sum;
    }

    static int findSuperDigit(String number){
        if(isSuperDigit(number))
            return Integer.parseInt(number);

        long nextNumber = caculateSum(number);
        return findSuperDigit(Long.toString(nextNumber));
    }

    static int superDigit(String n, int k) {
        long initSum = caculateSum(n) * k;
        return findSuperDigit(Long.toString(initSum));
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] nk = scanner.nextLine().split(" ");

        String n = nk[0];

        int k = Integer.parseInt(nk[1]);

        int result = superDigit(n, k);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedWriter.close();

        scanner.close();
    }
}
