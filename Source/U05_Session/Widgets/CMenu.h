#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMenuInterface.h"
#include "CMenu.generated.h"

UCLASS()
class U05_SESSION_API UCMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
		void HostServer();

public:
	void SetOwingGameInstance(IIMenuInterface* InOwingInterface);

	void Attach();
	void Detach();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

private:
	IIMenuInterface* OwingGameInstance;
};