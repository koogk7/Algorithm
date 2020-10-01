"""
1. 2 곱하기 또는 3 나누기 연산만 가능

6
4 8 6 3 12 9
2*2, 2*2*2, 2*3, 3, 2*2*3, 3*3
3*3, 3, 2*3, 2*2*3, 2*2, 2*2*2
9, 3, 6, 12, 4, 8

4
42 28 84 126

2*3*7, 2*2*7, 2*2*3*7, 2*3*3*7
2*3, 2*2, 2*2*3, 2*3*3

2*3*3, 2*3, 2*2*3, 2*2
126 42 84 28

3, 2, 2*3, 3*3

--> 3의 갯수가 많고, 2의 갯수가 적은 순으로 정렬하면 되겠다
1. 원래 배열을 둔다.
2. 원래 배열과 인덱스를 공유하는 2의 갯수와 3의 갯수를 갖는 pair를 가지는 지료형 배열을 둔다
3. 정렬한다.
"""
import sys


class TwoThreeCnt:
    def __init__(self, index, number):
        self.index = index
        self.two = TwoThreeCnt._get_cnt(number, 2)
        self.three = TwoThreeCnt._get_cnt(number, 3)

    @staticmethod
    def _get_cnt(number, two_or_three):
        cnt = 0
        while True:
            if number == 0:
                return cnt
            if number % two_or_three != 0:
                return cnt
            cnt += 1
            number //= two_or_three


def solve(shuffled):
    parsed = [TwoThreeCnt(idx, number) for idx, number in enumerate(shuffled)]
    sort_seq = sorted(parsed, key=lambda item: (-item.three, item.two))
    return [shuffled[item.index] for item in sort_seq]


if __name__ == '__main__':
    n = int(sys.stdin.readline().rstrip())
    inputs = sys.stdin.readline().rstrip().split()
    answer = solve([int(input) for input in inputs])
    [print(ans, end=' ') for ans in answer]
