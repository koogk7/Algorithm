import sys
from queue import PriorityQueue

# python 2차원 배열 입력받기
m, n = map(int, sys.stdin.readline().split())
# maze = [list(map(int, list(input().strip()))) for i in range(n)]
maze = []
visit = [[0] * m for i in range(n)]

for i in range(n):
    test = list(map(int, list(input().strip())))
    maze.append(test)


dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]


def isBoundary(row, col):
    return 0 <= row < n and 0 <= col < m


que = PriorityQueue()
que.put((0, 0, 0))
visit[0][0] = 1

while not que.empty():
    break_wall_cnt, row, col = que.get()

    if row == n-1 and col == m-1:
        print(break_wall_cnt)
        break

    for dir in range(0,4):
        nr = row + dr[dir]
        nc = col + dc[dir]

        if not isBoundary(nr, nc):
            continue
        if visit[nr][nc] == 1:
            continue
        visit[nr][nc] = 1
        if maze[nr][nc] == 1:
            que.put((break_wall_cnt+1, nr, nc))
        else:
            que.put((break_wall_cnt, nr, nc))
