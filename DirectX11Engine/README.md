# Engine
```
* Engine -> Debug -> 구성 속성 -> 일반 -> 대상 이름
$(ProjectName)_d

* Engine -> 모든 구성 -> 구성 속성 -> 일반 -> 출력디렉터리
$(SolutionDir)External\Library\$(ProjectName)\
```

# Client
```
* Client -> 모든 구성 -> 구성 속성 -> VC++ 디렉터리 -> 포함 디렉터리
$(SolutionDir)External\Include\
Client -> 모든 구성 -> 구성 속성 -> VC++ 디렉터리 -> 포함 디렉터리 -> 부모 또는 프로젝트 기본값에서 상속(I) 체크

* Client -> 모든 구성 -> 구성 속성 -> VC++ 디렉터리 -> 라이브러리 디렉터리
$(SolutionDir)External\Library\
```