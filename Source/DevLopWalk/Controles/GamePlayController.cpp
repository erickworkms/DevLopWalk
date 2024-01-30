//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "GamePlayController.h"
#include "EngineUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "GameFramework/PlayerStart.h"


void AGamePlayController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AGamePlayController::CriaPersonagem(TEnumAsByte<TipoPersonagem> PersonagemNPC)
{
	UWorld* World = GetWorld();
	check(World);
	APlayerStart* PontoEscolhido = nullptr;
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		PontoEscolhido = *It;
	}
	
	if (IsValid(PontoEscolhido))
	{
		Personagem = GetWorld()->SpawnActorDeferred<AJogador_Base>(
			AJogador_Base::StaticClass(),
			FTransform(PontoEscolhido->GetActorRotation(),
			           PontoEscolhido->GetActorLocation()));
		if (Personagem)
		{
			Personagem->PersonagemNPC = PersonagemNPC;
			Personagem->FinishSpawning(FTransform(PontoEscolhido->GetActorRotation(),
			                                      PontoEscolhido->GetActorLocation()));
		}
		bShowMouseCursor = false;
		SetPawn(Personagem);
		Possess(Personagem);
	}
}