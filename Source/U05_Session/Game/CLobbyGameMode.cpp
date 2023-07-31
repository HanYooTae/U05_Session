#include "CLobbyGameMode.h"
#include "Global.h"

void ACLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++NumberOfPlayers;
	CLog::Print("Player : " + FString::FromInt(NumberOfPlayers));

	if (NumberOfPlayers >= 3)
	{
		UWorld* world = GetWorld();
		CheckNull(world);
		world->ServerTravel("/Game/Maps/Play?Listen");
	}
}

void ACLobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	--NumberOfPlayers;
	CLog::Print("Player : " + FString::FromInt(NumberOfPlayers));
}