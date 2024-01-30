//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWalk/GameInstance/DevLopWalkGameInstance.h"
#include "DevLopWalk/PlayerStates/ADevLopWalkGameStateBase.h"
#include "GameplayFaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWALK_API AGameplayFaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AGameplayFaseGameMode();

public:	
	virtual void BeginPlay() override;

	UPROPERTY()
	ADevLopWalkGameStateBase* GameStateJogador;

	FTimerHandle ContadorTempo;
	
	UFUNCTION()
	void AtualizaTempo();
	
	UFUNCTION(BlueprintCallable)
	void RetornaMenuInicial();

private:
	UPROPERTY()
	UDevLopWalkGameInstance* GameInstance;
};
