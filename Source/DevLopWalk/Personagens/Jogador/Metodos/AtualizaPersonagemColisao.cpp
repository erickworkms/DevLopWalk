#include "DevLopWalk/Personagens/Jogador/Jogador_Base.h"
#include "Kismet/KismetMathLibrary.h"

void AJogador_Base::AtualizaPersonagemColisao(float DeltaTime)
{
	ResultadoPeEsq = VerificaSocketDist(this,"PeEsquerdoSoquete",40);
	ResultadoPeDir = VerificaSocketDist(this,"PeDireitoSoquete",40);

	FHitResult LimiteSoloPeEsq = VerificaSocketDist(this,"PeEsquerdoSoquete",DistanciaPes);
	FHitResult LimiteSoloPeDir = VerificaSocketDist(this,"PeDireitoSoquete",DistanciaPes);
	FHitResult LimiteSoloRoot = VerificaSocketDist(this,"Root",40);

	float rotacaoPeDir = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(LimiteSoloPeDir.ImpactNormal.GetSafeNormal(),FVector::UpVector)));
	float rotacaoPeEsq = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(LimiteSoloPeEsq.ImpactNormal.GetSafeNormal(),FVector::UpVector)));
	//float rotacaoRoot = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(LimiteSoloRoot.ImpactNormal.GetSafeNormal(),FVector::UpVector)));

	FQuat VetorRotacaoRootCima = FQuat::FindBetweenVectors(FVector::UpVector, LimiteSoloRoot.ImpactNormal);
	FQuat VetorRotacaoRootlado = FQuat::FindBetweenVectors(FVector::ForwardVector, LimiteSoloRoot.ImpactNormal);

	float rotacaoRootCima =FQuatRotationMatrix(VetorRotacaoRootCima).Rotator().Pitch;
	float rotacaoRootBaixo =FQuatRotationMatrix(VetorRotacaoRootlado).Rotator().Pitch;
		
	if (ResultadoPeEsq.bBlockingHit || ResultadoPeDir.bBlockingHit)
	{
		if (FMath::TruncToInt(ResultadoPeEsq.Distance) > FMath::TruncToInt(ResultadoPeDir.Distance))
		{
			DistanciaEncontrada = (ResultadoPeEsq.Distance - 76) * -1;
			DistanciaPes = ResultadoPeEsq.Distance - ResultadoPeDir.Distance;
		
			DistanciaRoot = UKismetMathLibrary::FInterpTo(DistanciaRoot,DistanciaEncontrada,DeltaTime,InterpolacaoRoot);
						
			if (rotacaoRootCima > -12 && rotacaoRootCima < 12)
			{
				DistanciaPeDir = (LimiteSoloPeDir.Distance - 110 - DistanciaPes) / -45 - rotacaoPeDir;
				DistanciaPeEsq = (LimiteSoloPeEsq.Distance - 110 + DistanciaPes) / -45 - rotacaoPeEsq;
				RootIKRotacao = FRotator(UKismetMathLibrary::FInterpTo(RootIKRotacao.Pitch,rotacaoRootCima,DeltaTime,5.0f),0,0);
			}
			else 
			{
				if (rotacaoPeEsq > 10)
				{
					rotacaoPeDir = 0;
				}
				DistanciaPeDir = (LimiteSoloPeDir.Distance - 110 - DistanciaPes) / -45 - rotacaoPeDir;
				DistanciaPeDir = DistanciaPeDir - (DistanciaPeDir * 0.5);
				DistanciaPeEsq = (LimiteSoloPeEsq.Distance - 110 + DistanciaPes) / -45 - rotacaoPeEsq;
				DistanciaPeEsq = DistanciaPeEsq + (DistanciaPeEsq * 0.5);
				RootIKRotacao = FRotator(UKismetMathLibrary::FInterpTo(RootIKRotacao.Pitch,0,DeltaTime,1.0f),0,0);
			}
		}
		else if (FMath::TruncToInt(ResultadoPeDir.Distance) > FMath::TruncToInt(ResultadoPeEsq.Distance))
		{
			DistanciaEncontrada = (ResultadoPeDir.Distance - 76) * -1;
			DistanciaPes = ResultadoPeDir.Distance - ResultadoPeEsq.Distance;
			DistanciaRoot = UKismetMathLibrary::FInterpTo(DistanciaRoot,DistanciaEncontrada,DeltaTime,30.0f);
	
			if (rotacaoRootCima > -12 && rotacaoRootCima < 12)
			{
				DistanciaPeDir =(LimiteSoloPeDir.Distance - 110 + DistanciaPes) / -45 - rotacaoPeDir;
				DistanciaPeEsq = (LimiteSoloPeEsq.Distance - 110 - DistanciaPes) / -45 - rotacaoPeEsq;
				RootIKRotacao = FRotator(UKismetMathLibrary::FInterpTo(RootIKRotacao.Pitch,rotacaoRootCima,DeltaTime,5.0f),0,0);
			}
			else 
			{
				if (rotacaoPeDir > 10)
				{
					rotacaoPeEsq = 0;
				}
				DistanciaPeDir =(LimiteSoloPeDir.Distance - 110 + DistanciaPes) / -45 - rotacaoPeDir;
				DistanciaPeDir = DistanciaPeDir + (DistanciaPeDir * 0.5);
				DistanciaPeEsq = (LimiteSoloPeEsq.Distance - 110 - DistanciaPes) / -45 - rotacaoPeEsq;
				DistanciaPeEsq = DistanciaPeEsq - (DistanciaPeEsq * 0.5);
				RootIKRotacao = FRotator(UKismetMathLibrary::FInterpTo(RootIKRotacao.Pitch,0,DeltaTime,5.0f),0,0);
			}
		}
		else
		{
			DistanciaEncontrada = 0;
			DistanciaPes = 0;
			DistanciaRoot = UKismetMathLibrary::FInterpTo(DistanciaRoot,DistanciaEncontrada,DeltaTime,30.0f);
			DistanciaPeDir = FMath::FInterpTo(DistanciaPeDir,0,DeltaTime, 15.f);
			DistanciaPeEsq = FMath::FInterpTo(DistanciaPeEsq,0,DeltaTime, 15.f);
			RootIKRotacao = FRotator(UKismetMathLibrary::FInterpTo(RootIKRotacao.Pitch,0,DeltaTime,5.0f),0,0);
		}
		if (rotacaoRootCima > -1 && rotacaoRootCima < 1)
		{
			RootIKLocal = UKismetMathLibrary::VInterpTo(RootIKLocal,FVector(0,0,UKismetMathLibrary::FClamp(DistanciaRoot,-20,0)),DeltaTime,15.0f);
		}
		else
		{
			RootIKLocal = UKismetMathLibrary::VInterpTo(RootIKLocal,FVector(0,0,UKismetMathLibrary::FClamp(0,-20,0)),DeltaTime,15.0f);
		}
		
		// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
	 //  "ResultadoPeEsq "+FString::SanitizeFloat(FMath::TruncToInt(ResultadoPeEsq.Distance))+"\n"+
	 //   "ResultadoPeDir "+FString::SanitizeFloat(FMath::TruncToInt(ResultadoPeDir.Distance))+"\n"+
	 //  "PeDirIKRotacao "+PeDirIKRotacao.ToString()+"\n"+
	 //   "RotacaoChaoDir "+FString::SanitizeFloat(FMath::TruncToInt(rotacaoPeDir))+"\n"+
	 //   "PeEsqIKRotacao "+PeEsqIKRotacao.ToString()+"\n"+
	 //   "RotacaoChaoEsq "+FString::SanitizeFloat(FMath::TruncToInt(rotacaoPeEsq))+"\n"+
	 //   "LimiteSoloPeDir "+FString::SanitizeFloat(FMath::TruncToInt(LimiteSoloPeDir.Distance))+"\n"+
	 //   "DistanciaPes "+FString::SanitizeFloat(FMath::TruncToInt(DistanciaPes))+"\n"+
	 //   "rotacaoRootCima "+FString::SanitizeFloat(FMath::TruncToInt(rotacaoRootCima))+"\n"+
	 //   "rotacaoRootBaixo"+FString::SanitizeFloat(FMath::TruncToInt(rotacaoRootBaixo))+"\n"+
	 //   "atan2x "+FString::SanitizeFloat(FMath::RadiansToDegrees(FMath::Acos(FMath::Atan2(LimiteSoloRoot.ImpactNormal.X,
		// 						LimiteSoloRoot.ImpactNormal.Z))))+"\n"+
		// "atan2y "+FString::SanitizeFloat(FMath::RadiansToDegrees(FMath::Acos(FMath::Atan2(LimiteSoloRoot.ImpactNormal.Y,
		// 					   LimiteSoloRoot.ImpactNormal.Z))))+"\n"+
	 //   "DistanciaRoot : "+FString::SanitizeFloat(DistanciaRoot)+"\n");
	}
}


FHitResult AJogador_Base::VerificaSocketDist(AJogador_Base* PersonagemReferencia, FName SocketNome,float LimiteColisao)
{
	FVector LocalSocket = PersonagemReferencia->GetMesh()->GetSocketLocation(SocketNome);

	FVector LocalRoot = PersonagemReferencia->GetMesh()->GetComponentToWorld().GetLocation() + FVector(0,0,78.5);

	FVector LocalResultado = FVector(LocalSocket.X,LocalSocket.Y,LocalRoot.Z);
	
	FVector DirecaoBaixo = -PersonagemReferencia->GetActorUpVector();
	FVector DirecaoCima = PersonagemReferencia->GetActorUpVector();
	FCollisionQueryParams ParametrosColisao;
	ParametrosColisao.AddIgnoredActor(PersonagemReferencia);

	FHitResult LocalColisao;
	GetWorld()->LineTraceSingleByChannel(
		LocalColisao,
		LocalResultado,
		LocalResultado - FVector(0,0,151),		
		ECC_Visibility,
		ParametrosColisao);
	
	//DrawDebugLine(GetWorld(), LocalResultado, LocalResultado - FVector(0,0,151), FColor::Green, false, 2.0f, 0, 1.0f);
		
	return LocalColisao;
}

FHitResult AJogador_Base::VerificaRootDist(AJogador_Base* PersonagemReferencia, FName SocketNome, float DiferencaPeDistancia)
{
	FVector LocalSocket = PersonagemReferencia->GetMesh()->GetSocketLocation(SocketNome);
	
	FVector LocalResultado = FVector(LocalSocket.X,LocalSocket.Y,0);

	FCollisionQueryParams ParametrosColisao;
	ParametrosColisao.AddIgnoredActor(PersonagemReferencia);

	FHitResult LocalColisao;
	bool ColisaoBloqueada = GetWorld()->LineTraceSingleByChannel(
		LocalColisao,
		LocalResultado + FVector(0,0,78.5),
		LocalResultado + FVector(0,0,-78.5),		
		ECC_Visibility,
		ParametrosColisao);
	
	if (ColisaoBloqueada)
	{
		return LocalColisao;
	}
	else if (!ColisaoBloqueada)
	{
		LocalColisao.Distance = 999;
		LocalColisao.bBlockingHit = false;
		LocalColisao.Normal = FVector(0,0,0);
		return LocalColisao;
	}
	return LocalColisao;
}
