//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHudGameplay.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWALK_API ABaseHudGameplay : public AHUD
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void AtivarTelaVencedor();
	
	UPROPERTY(BlueprintReadWrite)
	ABaseHudGameplay* HudGameplay;
};
