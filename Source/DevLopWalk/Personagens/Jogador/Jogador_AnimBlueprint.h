//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DevLopWalk/Personagens/Enums/Lista_Enums.h"
#include "Jogador_AnimBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWALK_API UJogador_AnimBlueprint : public UAnimInstance
{
	GENERATED_BODY()

public:
	UJogador_AnimBlueprint();
	
	FVector LocalArma;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Vida;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Velocidade;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float PeDirIKValor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float PeEsqIKValor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float RootIKValor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	FVector RootIKLocal;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	FRotator RootIKRotacao;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	FRotator PeDirIKRotacao;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	FRotator PeEsqIKRotacao;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<TipoAcao> Acao = Nada;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	APawn* Personagem = NULL;
private:
	
	float DistanciaMax = 40.0f;

	FRotator LimiteSoloPeDirRotacao;
};
