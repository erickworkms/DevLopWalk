//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DetectarDano.h"
#include "DevLopWalk/Personagens/Jogador/Jogador_Base.h"

void UDetectarDano::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao,
                                float DuracaoTotal)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		Jogador->Acao = TomarDano;
	}
}


void UDetectarDano::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animacao)
{
	AJogador_Base* Jogador = Cast<AJogador_Base>(MeshComp->GetOwner());
	if (IsValid(Jogador))
	{
		Jogador->Acao = Nada;
	}
}
