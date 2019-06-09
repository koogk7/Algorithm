from itertools import combinations


'''
    파이썬 자료구조 사용방법이 익숙하지 않아 시간이 오래걸림, 이번 문제를 통해 set과 tulpe에 조금
    익숙해짐
'''

def isKey(keys, relation, row_size):
    key_val = set()

    for row in relation:
        element = tuple([row[key] for key in keys])
        key_val.add(element)

    if len(key_val) == row_size:
        return True

    return False


def solution(relation):
    row_size = len(relation)
    col_size = len(relation[0])
    candi_key = list()
    answer = 0

    for key_size in range(1, col_size+1):
        key_comb = list(combinations(range(col_size), key_size))

        for keys in key_comb:
            if isKey(keys, relation, row_size):
                candi_key.append(set(keys))
    print(candi_key)

    # 최소성 검증
    for target in candi_key:
        flag = True
        for item in candi_key:
            if target == item:
                continue
            if target == target | item: # 교집합이 target이면
                flag = False
                break
        if flag:
            answer += 1

    return answer



