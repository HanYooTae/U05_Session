#include "CMenu.h"
#include "Components/Button.h"
#include "Global.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"
#include "CSessionRow.h"
#include "Components/TextBlock.h"

UCMenu::UCMenu(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetClass(&SessionRowClass, "/Game/Widgets/WB_SessionRow");
}

bool UCMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);


	CheckNullResult(HostButton, false);
	HostButton->OnClicked.AddDynamic(this, &UCMenu::HostServer);

	CheckNullResult(JoinButton, false);
	JoinButton->OnClicked.AddDynamic(this, &UCMenu::OpenJoinMenu);

	CheckNullResult(CancelJoinMenuButton, false);
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UCMenu::OpenMainMenu);

	CheckNullResult(ConfirmJoinMenuButton, false);
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UCMenu::JoinServer);

	CheckNullResult(QuitButton, false);
	QuitButton->OnClicked.AddDynamic(this, &UCMenu::QuitGame);

	return true;
}

void UCMenu::SetSessionList(TArray<FString> InSessionIDs)
{
	UWorld* world = GetWorld();
	CheckNull(world);

	SessionList->ClearChildren();


	uint32 i = 0;
	for (const auto& id : InSessionIDs)
	{
		UCSessionRow* sessionRow = CreateWidget<UCSessionRow>(world, SessionRowClass);
		CheckNull(sessionRow);

		sessionRow->SessionName->SetText(FText::FromString(id));
		sessionRow->SetSelfIndex(this, i++);

		SessionList->AddChild(sessionRow);
	}
}

void UCMenu::SetSelectedRowIndex(uint32 InIndex)
{
	SelectedRowIndex = InIndex;
	SelectedRowIndex.IsSet();
}

void UCMenu::HostServer()
{
	CheckNull(OwingGameInstance);
	OwingGameInstance->Host();
}

void UCMenu::JoinServer()
{
	CheckNull(OwingGameInstance);

	//SelectedRowIndex = 100;

	//CheckNull(IPAddressField);
	//const FString& address = IPAddressField->GetText().ToString();

	if (SelectedRowIndex.IsSet())
	{
		CLog::Log("SelectedRowIndex : " + FString::FromInt(SelectedRowIndex.GetValue()));
	}
	else
	{
		CLog::Log("SelectedRowIndex is not set");
	}

	OwingGameInstance->Join("");

	
}

void UCMenu::OpenJoinMenu()
{
	CheckNull(MenuSwitcher);
	CheckNull(JoinMenu);
	MenuSwitcher->SetActiveWidget(JoinMenu);

	if(!!OwingGameInstance)
		OwingGameInstance->FindSession();
}

void UCMenu::OpenMainMenu()
{
	CheckNull(MenuSwitcher);
	CheckNull(MainMenu);
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UCMenu::QuitGame()
{
	UWorld* world = GetWorld();
	CheckNull(world);

	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);
	
	controller->ConsoleCommand("Quit");
}
