import heapq

processable_que = []
waiting_que = []

def solution(jobs):
    """
    22:57 ~ 24:24 -> 1:30분 걸림...
    구현 생각: 30분
    이슈: 시작할 때 웨이팅 큐에 넣고 시작하면 되는데, 이 처리를 복잡하게 생각함

    한 번에 하나의 요청만을 수행
    걸린 시간 = 종료시간 - 요청시간

    가장 작은 평균 시간을 구하라

    어떻게 해야 가장 작지? --> 대기를 적게 해야지... 수행 시간은 항상 고정!
    """
    sec = 0
    answer = 0
    [push_waiting(job) for job in jobs]

    while(processable_que or waiting_que):
        process_job = pop_processable() if processable_que else pop_waiting()

        sec = max(sec, process_job[0])
        sec += process_job[1]
        answer += sec - process_job[0]

        while(waiting_que and waiting_que[0][0] <= sec):
            push_processable(pop_waiting())

    return answer // len(jobs)


def push_processable(job):
    heapq.heappush(processable_que, (job[1], job[0]))


def pop_processable():
    ret = heapq.heappop(processable_que)
    return (ret[1], ret[0])


def push_waiting(job):
    heapq.heappush(waiting_que, job)


def pop_waiting():
    return heapq.heappop(waiting_que)


print(solution([[0, 3], [1, 9], [2, 6]]))
print(solution([[0, 3], [0, 1]]))
print(solution([[100, 1], [1, 1]]))
print(solution([[0, 9], [8, 1]]))
