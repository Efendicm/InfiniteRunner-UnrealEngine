// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperFly.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include <InfiniteRunner\Runner.h>
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "EndlessRunnerGameModeBase.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>

// Sets default values
ASuperFly::ASuperFly()
{
	//Create the Scene for PowerUp
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	//used as SphereCollider for collison for PowerUp
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(SceneComponent);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapPawn"));
	//create the powerUp Mesh
	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMesh"));
	PowerUpMesh->SetupAttachment(SphereCollider);
	PowerUpMesh->SetCollisionProfileName(TEXT("OverlapPawn"));
	//Created to Roate PowerUp
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 180, 0);

}

// Called when the game starts or when spawned
void ASuperFly::BeginPlay()
{
	Super::BeginPlay();
	//Calls to Activate the Collision
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASuperFly::OnSphereOverlap);
}

void ASuperFly::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunner* RunCharacter = Cast<ARunner>(OtherActor);
	SuperFly = true;
	if (RunCharacter && SuperFly)
	{
		if (OverlapSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
		}
		Destroy();
	}
}
