//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "DevLopWalk/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::MoverFrente(float valor)
{
	ValorFrenteAtras = valor;
	if (valor != 0 && PodeMovimentar == true)
	{
		if (Acao != Queda && Acao != Morto)
		{
			FVector Frente = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
			
			AddMovementInput(Frente, valor);
		}
	}
}

void AJogador_Base::MoverLado(float valor)
{
	ValorDireitaEsquerda = valor;
	if (valor != 0 && PodeMovimentar == true)
	{
		if (Acao != Queda && Acao != Morto)
		{
			FVector Lado = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

			AddMovementInput(Lado, valor);
		}
	}
}


