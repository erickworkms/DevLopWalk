//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DevLopWalk/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

void AJogador_Base::DefineEstadoAtual()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		Estado = Caindo;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		Estado = NoChaoAndando;
	}
	else
	{
		Estado = NoChaoAndando;
	}
}
