//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWalkGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWALK_API UDevLopWalkGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	APlayerController* ControleJogador;
	virtual void Init() override;
	virtual void StartGameInstance() override;
	virtual void Shutdown() override;
};
