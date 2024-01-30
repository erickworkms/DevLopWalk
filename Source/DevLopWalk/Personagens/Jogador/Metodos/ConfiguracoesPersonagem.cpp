//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DevLopWalk/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void AJogador_Base::DefinePadroes()
{
	MeshesPlayer.Init("4", 4);
	AnimacaoPlayer.Init("4", 4);

	MeshesPlayer[0] = TEXT("SkeletalMesh'/Game/Personagens/Estagiario/Estagiario.Estagiario'");
	MeshesPlayer[1] = TEXT("SkeletalMesh'/Game/Personagens/Pleno/Sporty_Granny.Sporty_Granny'");
	MeshesPlayer[2] = TEXT("SkeletalMesh'/Game/Personagens/Senior/Swat.Swat'");
	MeshesPlayer[3] = TEXT("SkeletalMesh'/Game/Personagens/Chefe/The_Boss.The_Boss'");
	
	AnimacaoPlayer[0] = TEXT(
		"AnimBlueprint'/Game/Personagens/Estagiario/Estagiario_AnimBlueprint.Estagiario_AnimBlueprint_C'");
	AnimacaoPlayer[1] = TEXT("AnimBlueprint'/Game/Personagens/Pleno/Pleno_AnimBlueprint.Pleno_AnimBlueprint_C'");
	AnimacaoPlayer[2] = TEXT("AnimBlueprint'/Game/Personagens/Senior/Senior_AnimBlueprint.Senior_AnimBlueprint_C'");
	AnimacaoPlayer[3] = TEXT("AnimBlueprint'/Game/Personagens/Chefe/Chefe_AnimBlueprint.Chefe_AnimBlueprint_C'");


	Estagiario_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[0]));
	Pleno_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[1]));
	Senior_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[2]));
	Chefe_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimacaoPlayer[3]));

	GetCharacterMovement()->AirControl = 1;
	GetCharacterMovement()->AirControlBoostMultiplier = 10;
	GetCharacterMovement()->AirControlBoostVelocityThreshold = 100;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AJogador_Base::VerificaMeshPersonagem(float Index)
{
	if (IsValid(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index]))))
	{
		GetMesh()->SetSkeletalMesh(
			Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index])));
	}
}

void AJogador_Base::CriaPersonagemConfig()
{
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);

	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Personagens/Estagiario/Estagiario.Estagiario'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -78.5));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));
	}

	//AnimBlueprint
	static ConstructorHelpers::FObjectFinder<UClass> AnimacaoEncontrada(
		TEXT("AnimBlueprint'/Game/Personagens/Estagiario/Estagiario_AnimBlueprint.Estagiario_AnimBlueprint_C'"));
	GetMesh()->SetAnimInstanceClass(AnimacaoEncontrada.Object);

	ColisaoPeDir = CreateDefaultSubobject<USphereComponent>(TEXT("ColisaoPeDir"));
	ColisaoPeEsq = CreateDefaultSubobject<USphereComponent>(TEXT("ColisaoPeEsq"));
}

void AJogador_Base::AttachPersonagemColisao()
{
	ColisaoPeDir->AttachToComponent(GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale, "PeDireitoSoquete");
	ColisaoPeDir->SetRelativeLocationAndRotation(FVector(5, 0, 0),
										 FRotator(0, 0, 0), false, false);
	ColisaoPeDir->SetVisibility(true);
	ColisaoPeDir->bHiddenInGame = false;
	//ColisaoPeDir->SetWorldScale3D(FVector(0.05, 0.15, 0.25));
	ColisaoPeDir->SetWorldScale3D(FVector(0.2, 0.2, 0.2));
	ColisaoPeDir->SetCollisionResponseToAllChannels(ECR_Overlap);
	ColisaoPeDir->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	ColisaoPeDir->MoveIgnoreActors.Add(GetOwner());
	ColisaoPeDir->OnComponentBeginOverlap.AddDynamic(this, &AJogador_Base::PeDirColisaoEntrada);
	ColisaoPeDir->OnComponentEndOverlap.AddDynamic(this, &AJogador_Base::PeDirColisaoSaida);

	ColisaoPeEsq->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale, "PeEsquerdoSoquete");
	ColisaoPeEsq->SetRelativeLocationAndRotation(FVector(5, 0, 0),
										 FRotator(0, 0, 0), false, false);
	ColisaoPeEsq->SetVisibility(true);
	ColisaoPeEsq->bHiddenInGame = false;
	ColisaoPeEsq->SetWorldScale3D(FVector(0.2, 0.2, 0.2));
	ColisaoPeEsq->SetCollisionResponseToAllChannels(ECR_Overlap);
	ColisaoPeEsq->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	ColisaoPeEsq->MoveIgnoreActors.Add(GetOwner());
	ColisaoPeEsq->OnComponentBeginOverlap.AddDynamic(this, &AJogador_Base::PeEsqColisaoEntrada);
	ColisaoPeEsq->OnComponentEndOverlap.AddDynamic(this, &AJogador_Base::PeEsqColisaoSaida);
}

void AJogador_Base::PeDirColisaoEntrada(UPrimitiveComponent* OverlappedComp, AActor* ObjetoDetectado,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector LocalSocket = GetMesh()->GetSocketLocation("PeDireitoSoquete");
	
	FCollisionQueryParams ParametrosColisao;

	FVector Direcao = -GetActorUpVector();
	
	FHitResult LocalColisao;
	GetWorld()->LineTraceSingleByChannel(
		LocalColisao,
		LocalSocket,
		LocalSocket + Direcao * 100,
		ECC_Visibility,
		ParametrosColisao);

	EstaColidindoPeDir = true;
}

void AJogador_Base::PeDirColisaoSaida(UPrimitiveComponent* OverlappedComp, AActor* ObjetoDetectado,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EstaColidindoPeDir = false;
}

void AJogador_Base::PeEsqColisaoEntrada(UPrimitiveComponent* OverlappedComp, AActor* ObjetoDetectado,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector LocalSocket = GetMesh()->GetSocketLocation("PeEsquerdoSoquete");
	
	FCollisionQueryParams ParametrosColisao;

	FVector Direcao = -GetActorUpVector();
	
	FHitResult LocalColisao;
	GetWorld()->LineTraceSingleByChannel(
		LocalColisao,
		LocalSocket + (Direcao *-1) * 40,
		LocalSocket + Direcao * 40,
		ECC_Visibility,
		ParametrosColisao);
	EstaColidindoPeEsq = true;
}

void AJogador_Base::PeEsqColisaoSaida(UPrimitiveComponent* OverlappedComp, AActor* ObjetoDetectado,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EstaColidindoPeEsq = false;
}
