#include "CMenu.h"
#include "Components/Button.h"
#include "Global.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

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

	return true;
}

void UCMenu::HostServer()
{
	CheckNull(OwingGameInstance);
	OwingGameInstance->Host();
}

void UCMenu::JoinServer()
{
	CheckNull(OwingGameInstance);

	CheckNull(IPAddressField);
	const FString& address = IPAddressField->GetText().ToString();

	OwingGameInstance->Join(address);
}

void UCMenu::OpenJoinMenu()
{
	CheckNull(MenuSwitcher);
	CheckNull(JoinMenu);
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UCMenu::OpenMainMenu()
{
	CheckNull(MenuSwitcher);
	CheckNull(MainMenu);
	MenuSwitcher->SetActiveWidget(MainMenu);
}
