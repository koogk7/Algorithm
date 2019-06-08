from operator import itemgetter

N = 4
stages = [4,4,4,4,4]

def getRate(_stage, _stages):
    no_clear = 0
    for index, item in enumerate(_stages):
        if item > _stage:
            return no_clear/(len(_stages) - index + no_clear)
        if item == _stage:
            no_clear += 1
    if no_clear == 0:
        return 0
    else:
        return 1


def solution(N, stages):
    stages.sort()
    answer = []
    answerDict = dict()
    for stage in range(1,N+1):
        failRate = getRate(stage,stages)
        answerDict[stage] = failRate
        answer.append({stage: failRate})

    answerDict = sorted(answerDict.items(),key=itemgetter(1), reverse=True)
    print(answerDict)
    answer = list(( x for x,y in answerDict))
    print(answer)
    return answer


solution(N,stages)