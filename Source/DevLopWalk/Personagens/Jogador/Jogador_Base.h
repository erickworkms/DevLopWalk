//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DevLopWalk/Personagens/Enums/Lista_Enums.h"
#include "Jogador_Base.generated.h"

UCLASS()
class DEVLOPWALK_API AJogador_Base : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCameraComponent* CameraPrincipal;
	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaCamera;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* ColisaoPeDir;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* ColisaoPeEsq;

public:
	AJogador_Base();

	UPROPERTY()
	AActor* Veiculo = nullptr;
	UPROPERTY()
	TArray<FString> MeshesPlayer;
	UPROPERTY()
	TArray<FString> AnimacaoPlayer;

	UPROPERTY(BlueprintReadOnly, Category="Variaveis")
	float Vida = 100;
	UPROPERTY()
	float Velocidade;
	UPROPERTY()
	float ValorFrenteAtras = 0;
	UPROPERTY()
	float ValorDireitaEsquerda = 0;

	UPROPERTY(meta=(BlueprintProtected = "true"))
	float VelocidadeCombo = 0.2f;
	UPROPERTY(BlueprintReadOnly, Category="Variaveis")
	float ValorAceleracao = 0.0f;
	UPROPERTY()
	float VelocidadeMax = 1000;
	UPROPERTY()
	float DistanciaRoot = 0;
	UPROPERTY()
	float DistanciaPeDir = 0;
	UPROPERTY()
	float DistanciaPeEsq = 0;
	UPROPERTY()
	float DistanciaEncontrada = 0;
	UPROPERTY()
	float DistanciaPes = 0;
	
	UPROPERTY()
	float InterpolacaoPe = 15;
	UPROPERTY()
	float InterpolacaoRoot = 30;
	UPROPERTY()
	float InterpolacaoDistancia = 15;
	
	
	UPROPERTY()
	bool EstaColidindoPeDir = false;
	UPROPERTY()
	bool EstaColidindoPeEsq = false;
	UPROPERTY()
	bool PodeMovimentar = true;
	
	UPROPERTY()
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY()
	TEnumAsByte<TipoAcao> Acao = Nada;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Personagem")
	TEnumAsByte<TipoPersonagem> PersonagemNPC = Estagiario;

	UPROPERTY()
	UClass* Estagiario_Anim;
	UPROPERTY()
	UClass* Pleno_Anim;
	UPROPERTY()
	UClass* Senior_Anim;
	UPROPERTY()
	UClass* Chefe_Anim;

	UPROPERTY()
	bool BloqueiaContador = true;
	UPROPERTY()
	bool PersonagemSeMovimenta;

	void VerificaEscolhaPersonagem();

	void VerificaMeshPersonagem(float Index);
	
	FVector RootIKLocal;
	
	FRotator RootIKRotacao;
	
	FRotator PeDirIKRotacao;
	
	FRotator PeEsqIKRotacao;

	FHitResult ResultadoPeEsq;

	FHitResult ResultadoPeDir;
	
	FHitResult ResultadoRoot;

	UFUNCTION()
	FHitResult VerificaSocketDist(AJogador_Base* PersonagemReferencia,FName SocketNome,float LimiteColisao);

	UFUNCTION()
	FHitResult VerificaRootDist(AJogador_Base* PersonagemReferencia,FName SocketNome,float LimiteColisao);

protected:
	virtual void BeginPlay() override;

	void MoverFrente(float valor);

	void MoverLado(float valor);

	void VirarCameraFrente(float valor);

	void VirarCameraLado(float valor);

	void DefinePadroesVel(float valor);

	//Botões apertados
	void VerificaPulo_Pressionado();
	void VerificaPulo_Solto();

	//Metodos
	void DefinePadroes();

	void DefineEstadoAtual();
	void CriaCameraConfig();
	void CriaPersonagemConfig();
	void AttachPersonagemColisao();
	void AtualizaPersonagemColisao(float DeltaTime);
	

	UFUNCTION()
	void PeDirColisaoEntrada(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						   const FHitResult& SweepResult);
	UFUNCTION()
	void PeDirColisaoSaida(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void PeEsqColisaoEntrada(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						   const FHitResult& SweepResult);

	UFUNCTION()
	void PeEsqColisaoSaida(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
