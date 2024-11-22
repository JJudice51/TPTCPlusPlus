// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class UStaticMeshComponent;
class UCurveFloat;
class UBoxComponent;

UCLASS()
class TPTCPLUSPLUS_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = _MovingPlatform, meta = (AllowPrivateAccess = "true", MakeEditWidget))
	FVector EndPosition = FVector(1000.0f, 0.0f, 0.0f);
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = _MovingPlatform, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* MovementCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = _MovingPlatform, meta = (AllowPrivateAccess = "true"))
	bool bIsMovingForward = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = _MovingPlatform, meta = (AllowPrivateAccess = "true"))
	float Progress;



public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnTriggerOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Forward();
	void Reverse();
};
