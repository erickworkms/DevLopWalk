//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopWalk/Huds/BaseHudGameplay.h"
#include "DevLopWalk/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWALK_API AGamePlayController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CriaPersonagem(TEnumAsByte<TipoPersonagem> PersonagemNPC);
		
	UPROPERTY(BlueprintReadWrite)
	AJogador_Base* Personagem;

	UPROPERTY(BlueprintReadWrite)
	ABaseHudGameplay* Hud;

protected:
	virtual void BeginPlay() override;
};
