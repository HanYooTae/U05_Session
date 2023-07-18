#include "CGameInstance.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	CLog::Log("GameInstance::Constructor Called");

	CHelpers::GetClass(&MenuWidgetClass, "/Game/Widgets/WB_Menu");
	//CLog::Log(MenuWidgetClass->GetName());
}

void UCGameInstance::Init()
{
	Super::Init();

	CLog::Log("GameInstance::Init Called");

	//CreateWidget(this, )
}

void UCGameInstance::LoadMenu()
{
	CheckNull(MenuWidgetClass);

	UUserWidget* menu = CreateWidget(this, MenuWidgetClass);
	CheckNull(menu);

	menu->AddToViewport();

	APlayerController* controller = GetFirstLocalPlayerController();
	CheckNull(controller);

	// º° µµ¿ò¾ÈµÊ
	menu->bIsFocusable = true;

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(menu->TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	controller->SetInputMode(inputMode);
	controller->bShowMouseCursor = true;

}

void UCGameInstance::Host()
{
	CLog::Print("Host");
	//-> Everybody Move to Play Map
	UWorld* world = GetWorld();
	CheckNull(world);

	world->ServerTravel("/Game/Maps/Play?listen");
}

void UCGameInstance::Join(const FString& InAddress)
{
	//GetEngine()->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(L"Join to %s", InAddress));
	CLog::Print("Join to " + InAddress);

	//UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//GetWorld()->GetFirstPlayerController();
	APlayerController* controller = GetFirstLocalPlayerController();
	CheckNull(controller);
	controller->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}
