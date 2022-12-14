
# 알아가야 할 중요 포인트

### 1. UserWidget Interface 사용
UserInterface를 사용하여 순수 가상함수를 만들어 사용한다 인터페이스를 생성하면 반드시 아래 클래스에만 작성한다.
<br>
C++에서는 순수가상함수를 반드시 어딘가 구현해줘야 빌드가 된다.
<br>
<br>
```
public:
	virtual void Host() = 0;
	virtual void Join(const FString& Address) = 0;
	virtual void LoadMainMenu() = 0;
```
<br>

GameInstance가 UserInterface를 상속 받게 한다. <br> <br>
``` class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface ``` 
<br>

### 2. UserWidget의 추상화

### 3. UserWidget의 기능 WidgetSwitcher

### 4. 서버로부터 클라이언트를 분리하는 문법
