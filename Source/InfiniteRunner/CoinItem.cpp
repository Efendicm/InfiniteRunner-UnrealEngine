// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include <InfiniteRunner\Runner.h>
#include "MyGameInstance.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values
ACoinItem::ACoinItem()
{
	//Create The Component in Bluerints For the coin
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	//Create a Collision for the coin to collide with the player
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(SceneComponent);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapPawn"));
	//Create the base mesh of the coin to give it the assets 
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	CoinMesh->SetupAttachment(SphereCollider);
	CoinMesh->SetCollisionProfileName(TEXT("OverlapPawn"));
	//Lets the coin roate to give it motion
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 180, 0);


}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
	//Overlap called when the game starts to scan for it
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ACoinItem::OnSphereOverlap);
	
}

void ACoinItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Call to the runcharacter to detect if they overlap to add and destroy the coin
	ARunner* RunCharacter = Cast<ARunner>(OtherActor);

	if (RunCharacter)
	{
		if (OverlapSound)
		{
			//Calling the sound for the coin to give a sound at the location of overlap
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
		}
		//Calls the add coin fuction in the Runner Class
		RunCharacter->AddCoin();
		//Destroys the coin
		Destroy();
	}
}

