import heapq

def solution(prices):
    max_heap = []
    last_day = len(prices) - 1
    answer = [last_day - idx for idx, _ in enumerate(prices)]

    # (N -1) + NlogN = NlogN
    for day, price in enumerate(prices): # N
        while max_heap and price < -1 * max_heap[0][0]: # NlogN
            p, i = heapq.heappop(max_heap)
            answer[-1*i] = day + i

        heapq.heappush(max_heap, (-price, -day))

    return answer