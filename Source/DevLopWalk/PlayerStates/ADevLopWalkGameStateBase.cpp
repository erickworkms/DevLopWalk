//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "ADevLopWalkGameStateBase.h"

float ADevLopWalkGameStateBase::GetTempoJogo()
{
	return TempoJogo;
}

void ADevLopWalkGameStateBase::SetTempoJogo(float TempoJogoSet)
{
	TempoJogo = TempoJogoSet;
}

void ADevLopWalkGameStateBase::DescontaTempoJogo()
{
	TempoJogo--;
}
