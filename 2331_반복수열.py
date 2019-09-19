import sys
import math
import operator

'''
    2331 - 반복수열
    - 첫항을 딕셔너리에 추가하지 않아서 해맸다
    - 딕셔너리 정렬 : dict(sorted(visit_number.items(), key=operator.itemgetter(1)))
'''

def caclulate(number, exp):
    return int(math.pow(int(number), int(exp)))


def getDigits(number):
    rst = []
    for i in str(number):
        rst.append(int(i))
    return rst


a, p = sys.stdin.readline().split()
visit_number = {}
number = int(a)
visit_number[number] = 0
order = 1

while True:
    next_number = 0
    digits = getDigits(number)

    for i in digits:
        next_number += caclulate(i, p)

    number = next_number

    if number in visit_number:
        break

    visit_number[number] = order
    order += 1

sorted_visit_number = dict(sorted(visit_number.items(), key=operator.itemgetter(1)))
# items() 함수는 key-value 쌍이 tuple로 구성된 리스트가 리턴됩니다.
# 인자값에 있는 key=operator.itemgetter(0)는 정렬하고자 하는 키 값을 0번째 인덱스 기준으로 하겠다는 것입니다.

print(sorted_visit_number[number])
