# 탈출
### 1. 44m

</br>

# 불!
### 1. 31m
### 2. 한번 틀렸는데... 반례 찾음
<<반례>> </br>

```
4 4
####
#.J#
#F.#
#..#
```

나는 사람 먼저 옮겨주고 불 옮겨줬는데.. 불이 옮겨짐에도 불구하고 이미 사람이 다음 곳으로 이동할 곳이 Queue에 들어갔기 때문에 이점을 고려 못해줘서 틀렸다.


</br>

# 성곽
### 1. 1hour ? 
### 2. 방향을 어떻게 구해줄지 고민/ 벽을 어떻게 뚫어줄지 고민 했었음
### 풀이 방법
1. map[N][M][4]: 3차원 배열로 각 배열안에 2진수로 벽인지, 길인지 넣어줌
2. v[N][M]: BFS 돌면서 방문체크겸 같은 방인지 숫자로 넣어주고 check해줌
3. 이때, 방향은 0일때만 갈 수 있으므로 그때 queue에 넣어줌
4. 1번째 BFS 돌면서 방을 나눠주고 이때, 몇개의 방이 나오고 그중 가장 큰 방이 나오는지 구해줬음
5. 대망의 벽뿌수기 -> 이것또한 BFS로 구해줬음
6. 나랑 같은 숫자가 아니면 다른 방이니깐 벽을 부술 수 있음 그래서 Hashmap<Integer, ArrayList<Integer> 에 key는 방 번호고, value는 벽부수고 갈 수 있는 방임
7. 마지막에 hashmap 돌면서 붙어 있는 방끼리 더해줬고, 이때 두개 방 더해서 가장 큰 값이 답임

    
