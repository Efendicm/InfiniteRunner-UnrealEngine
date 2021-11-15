                                                                                 
// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSpeed.h"
#include "Obstacle.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include <InfiniteRunner\Runner.h>
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "EndlessRunnerGameModeBase.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include "Niagara/Public/NiagaraComponent.h"

// Sets default values
ASuperSpeed::ASuperSpeed()
{
	//Create the Scene for PowerUp
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	//used as SphereCollider for collison for PowerUp
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(SceneComponent);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapPawn"));
	//ParticleSystem
	PowerUpPart = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PowerUpPart"));
	PowerUpPart->SetupAttachment(SceneComponent);
	PowerUpPart->SetupAttachment(SphereCollider);
	PowerUpPart->SetCollisionProfileName(TEXT("OverlapPawn"));
	//Created to Roate PowerUp
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 180, 0);
}

// Called when the game starts or when spawned
void ASuperSpeed::BeginPlay()
{
	Super::BeginPlay();
	//Calls to Activate the Collision
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASuperSpeed::OnSphereOverlap);

}
//Calls the PowerUp to be on or off
void ASuperSpeed::PowerUp()
{
	PowerUpDestroy->Dest = true;

}
//Call if Player Collides with PowerUp Mesh
void ASuperSpeed::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunner* RunCharacter = Cast<ARunner>(OtherActor);
	SuperSpeed = true;
	if (RunCharacter && SuperSpeed)
	{
		RunCharacter->PowerUp();
		if (OverlapSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
		}
		Destroy();
	}

}



