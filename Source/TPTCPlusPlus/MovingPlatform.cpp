// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Curves/CurveFloat.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	sceneComponent->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(sceneComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(StaticMesh);
	
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OnTriggerOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMovingPlatform::OnTriggerOverlapEnd);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Verify curve
	if (MovementCurve == nullptr) return;
		
	// Increase/Decrease Progress
	if (bIsMovingForward)
		Progress += DeltaTime;
	else
		Progress -= DeltaTime;
	Progress = FMath::Clamp(Progress, 0, 1);
	
	// Sample curve
	float value = MovementCurve->GetFloatValue(Progress);

	// Apply movement
	FVector newLocation = FMath::Lerp(FVector(0,0,0), EndPosition, value);
	StaticMesh->SetRelativeLocation(newLocation);
	

}

void AMovingPlatform::OnTriggerOverlapBegin(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//confirms the trigger is being called as necessary
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("Forward")));
}

void AMovingPlatform::OnTriggerOverlapEnd(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//confirms we are no longer calling the trigger as intended
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("Reverse")));
}

void AMovingPlatform::Forward()
{
	bIsMovingForward = true;
}

void AMovingPlatform::Reverse()
{
	bIsMovingForward = false;
}

