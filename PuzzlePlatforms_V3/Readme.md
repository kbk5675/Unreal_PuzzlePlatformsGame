# 알아가야 할 중요 포인트

### 1. UserWidget Interface 사용
UserInterface를 사용하여 순수 가상함수를 만들어 사용한다 인터페이스를 생성하면 반드시 아래 클래스에만 작성한다.<br>
C++에서는 순수가상함수를 반드시 어딘가 구현해줘야 빌드가 된다..<br>
```
// MenuInterface.h

public:
	// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORMS_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Host() = 0;
	virtual void Join(const FString& Address) = 0;
	virtual void LoadMainMenu() = 0;
};

```
<br>

GameInstance가 UserInterface를 상속 받게 한다. <br><br>
``` class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface ``` 
<br>

### 2. UserWidget의 추상화
게임을 제작하면서 만든 UserWidgetClass가 2개인데 내용이 많이 겹치게 되서 UserWidget Base를 따로 만들어 상속받게 만들었다. 
<br>
UserWiget Class 2개 : InGameMenu, MainMenu 
<br>
MenuWidget.class를 하나 만들고 겹치는 내용들을 옮겨 주었다. <br>

```
//MenuWidget.h

UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* Interface);
	void Setup();

protected:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	IMenuInterface* MenuInterface;
};

``` 

<br>
아래와 같이 상속받은 함수를 사용 Setup(), SetMenuInterface() <br>


```
// PuzzlePlatformsGameInstance.cpp

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure( MainMenuClass!= nullptr)) return;
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (!ensure(MainMenu != nullptr)) return;

	MainMenu->Setup();

	MainMenu->SetMenuInterface(this);
}

// 위와 같이 사용
void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr)) return;

	InGameMenu->Setup();

	InGameMenu->SetMenuInterface(this);
}

```
<br>


### 3. UserWidget의 기능 WidgetSwitcher
WidgetSwitcher는 같은 인덱스 내에 있는 Widget들을 이벤트를 이용해 번갈아 보여줄 수 있다. <br>
여기서 어떤 위젯을 바꿔줄 지 인수를 정해줘야하는데 인수값이 UWidget이라 헤더에서 UWidget으로 선언해주었다.<br>
```
// MainMenu.h

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;
```
```
// MainMenu.cpp

MenuSwitcher->SetActiveWidget(JoinMenu);

```



### 4. 서버로부터 클라이언트를 분리하는 문법

```
// PuzzlePlatformsGameInstance.cpp

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/Maps/MainMenu?listen", ETravelType::TRAVEL_Absolute);
}

```

