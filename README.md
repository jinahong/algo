## Study
|Due Date        | problem title| Memo|
|:-------------:|:-------------|:-------------|
||[14890.경사로](makepath.cpp)|index꼼꼼히 체크|
|2019/02/18| [1247. [S/W 문제해결 응용] 3일차 - 최적 경로](1247.cpp)||
||[1206. [S/W 문제해결 기본] 1일차 - View](view.cpp)||
||[1227. [S/W 문제해결 기본] 7일차 - 미로2](maze.cpp)||
|2019/02/21| [농작물 수확하기](farm.cpp)| 나는 배열 인덱스가 싫어요|
|2019/02/28|[[S/W 문제해결 기본] 9일차 - 사칙연산 유효성 검사](validation.cpp)|input받는거 개빡침, getline함수 사용|
||[삼삼 트리플 게임](triple.cpp)|나는 dfs를 썻지만, 안써도 가능했던문제..|
|2019/03/04|[퍼펙트 셔플](shuffle.cpp)|easy|
|2019/03/07|[삼성시의 버스 노선](busline.cpp)|easy|
||[격자판의 숫자 이어 붙이기](lattice.cpp)|set사용, 전역변수 초기화|
||[13458.시험 감독](supervisor.cpp)|기출인데 왤케쉬움? 테케 스스로 생각하기|
|2019/03/14|[2016년 요일 맞추기](datcnt.cpp)|easy, 맨날 c에서 함수 리턴해줘야하는거 까먹음|
||[15953.상금 헌터](huter.cpp)|0-based, 1-based신경써주기|
|2019/03/21|[[S/W 문제해결 기본] 7일차 - 암호생성기](crpyto.cpp)||


## simulation 및 시키는대로코딩
| Category      | problem title| Memo|
|:-------------:|:-------------|:-------------|
||[15683.감시](cctv.cpp)|XXX: 전역변수 남용하지 않기 위해서 2차원배열 parameter로 넘김, simulation|
||[16235.나무 제태크](tree.cpp)|문제 시킨대로 코딩, struct만들기, 행열 거꾸로 받아서 개고생..|
||[14499. 주사위 굴리기](dice.cpp)|easy, 60m, simulation|
||[14891. 톱니바퀴](gear.cpp)|문제 제대로 읽어야 할 simulation|
||[5373. 큐빙](cubing.cpp)|공간 복잡한 simulation|
||[3190. 뱀](snake.cpp)|문제 시킨대로 코딩, struct만들기, 행열 거꾸로 받아서 고생.. |
## 완탐 + chk
| 체감난이도      | problem title| Memo|
|:-------------:|:-------------|:-------------|


||[16234. 인구 이동](migration.cpp)|**pure 완탐**|

## combination
| 체감난이도      | problem title| Memo|
|:-------------:|:-------------|:-------------|
||[12886.돌 그룹](stongroup.cpp)|dfs, 해당 노드 방문여부가 N-dimension|
||[12969.ABC](abc.cpp)|dfs, 해당 노드 방문여부가 N-dimension|

||[15661. 링크와 스타트](combination/linksoccor.cpp)||
||[14500. 테트로미노](tetromino.cpp)||
||[5644. [모의 SW 역량테스트] 무선 충전](combination/wireless.cpp)|permutation|
||[14502. 연구소](combination/lab.cpp)|dfs, bfs, map크기작아서 괜찮|
||[2383. [모의 SW 역량테스트] 점심 식사시간](combination/helllunch.cpp)|combination, detail만드는게 어려웠음|
||[2112. [모의 SW 역량테스트] 보호 필름](combination/film.cpp)|combination을 여러 방법으로 구현해봄|
||[15686.치킨 배달](combination/chicken.cpp)|combination, 최소거리 완탐|
|high|[[S/W 문제해결 응용] 2일차 - 최대 상금](combination/reward.cpp)|combination + 중복가능한 permutation, 연산량 많으므로 pruning이 관건|
||[규영이와 인영이의 카드게임](combination/cardgame2.cpp)|permutation, 완탐|
||[7227. 사랑의 카운슬러](combination/counselor.cpp)|combination, 최소거리 완탐, 문제만 봐서는 permutation 같지만 정답계산하는 방법을 보면 순서필요없음|
||[15684.사다리 조작](combination/ladder.cpp)|combination|
|high|[[모의 SW 역량테스트] 벽돌 깨기](combination/explode.cpp)|permutation + bfs, 완탐|
||[2407.조합](combination/combination.cpp)|BigInt구조체, long long으로 안됨|
||[14501. 퇴사](quit.cpp)|Knapsack Problem|
||[15486. 퇴사2](quit2.cpp)|Knapsack Problem + memoization|
|high|[7579.앱](app.cpp)| knapsack문제, 상향식 dp, 잔잔하게 많은 실수함XXX|

## BFS or Complete Search
|체감난이도        | problem title| Memo|
|:-------------:|:-------------|:-------------| 
||[5014.스타트링크](startlink.cpp)|굳이 bfs쓰지 않아도되던...|
||[[S/W 문제해결 응용] 4일차 - 보급로](recover2.cpp)|dikstra, priority queue,|
||[[S/W 문제해결 응용] 4일차 - 보급로](recover.cpp)|dp로 안정화될때까지 반복문|
||[5213.과외맨](lessonman.cpp)|배열이 특이하게 꼼꼼함이 필요|
|high|[16236.아기 상어](babyshark.cpp)|2019/03/12, 역대급삽질, 머리좀써라.. dfs로 했다가 시간초과, bfs+visited|
|high|[16236.아기 상어](babyshark2.cpp)|2019/03/28, 2번째푸는대도 2시간 ㅠㅠ, bfs, 이전코드보다 빠름|
|high|[16236.아기 상어](babyshark3.cpp)|priority queue쓰면 코드가 더 깔끔!|
|low|[7576.토마토](tomato.cpp)|Basic BFS, x,y가 헷갈려 ㅠ|
## etc
|Category        | problem title| Memo|
|:-------------:|:-------------|:-------------| 
|partial sum|[15954.인형들](15954.cpp)|long double, partial sum|
|partial sum|[은기의 송아지 세기](calf.cpp)|partial sum, 전역변수 초기화|


