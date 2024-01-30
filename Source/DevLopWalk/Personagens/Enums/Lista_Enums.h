#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum TipoEstado
{
	NoChaoAndando UMETA(DisplayName = "NoChao"),
	Caindo UMETA(DisplayName = "Caindo")
};

UENUM(BlueprintType)
enum TipoAcao
{
	Atacar UMETA(DisplayName = "Atacar"),
	Pular UMETA(DisplayName = "Pular"),
	TomarDano UMETA(DisplayName = "TomarDano"),
	Queda UMETA(DisplayName = "Queda"),
	Morto UMETA(DisplayName = "Morto"),
	Nada UMETA(DisplayName = "Nada")
};

UENUM(BlueprintType)
enum TipoPersonagem
{
	Chefe UMETA(DisplayName = "Chefe"),
	Senior UMETA(DisplayName = "Senior"),
	Pleno UMETA(DisplayName = "Pleno"),
	Estagiario UMETA(DisplayName = "Estagiario"),
	Nenhum UMETA(DisplayName = "Nenhum")
};