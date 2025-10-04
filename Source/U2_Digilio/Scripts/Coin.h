// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS(Blueprintable)
class U2_DIGILIO_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float RotationSpeed = 180.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	bool WasCollected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* AuraMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* AuraMaterial;

	ACoin();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;
};
