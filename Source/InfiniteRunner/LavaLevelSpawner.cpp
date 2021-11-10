// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaLevelSpawner.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "EndlessRunnerGameModeBase.h"
#include "Runner.h"
#include "CoinItem.h"
#include "SuperSpeed.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>

// Sets default values
ALavaLevelSpawner::ALavaLevelSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create the base Scene for the Island to be spawned
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;
	//Create the base mesh to show the Islands 
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	AttachLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachLeft"));
	AttachLeft->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	AttachMiddle = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachMiddle"));
	AttachMiddle->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	AttachRight = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachRight"));
	AttachRight->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	TopRight = CreateDefaultSubobject<UArrowComponent>(TEXT("TopRight"));
	TopRight->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	TopMiddle = CreateDefaultSubobject<UArrowComponent>(TEXT("TopMiddle"));
	TopMiddle->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	TopLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("TopLeft"));
	TopLeft->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	MiddleRight = CreateDefaultSubobject<UArrowComponent>(TEXT("MiddleRight"));
	MiddleRight->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	Middle = CreateDefaultSubobject<UArrowComponent>(TEXT("Middle"));
	Middle->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	MiddleLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("MiddleLeft"));
	MiddleLeft->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	BottomMiddle = CreateDefaultSubobject<UArrowComponent>(TEXT("BottomMiddle"));
	BottomMiddle->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	BottomRight = CreateDefaultSubobject<UArrowComponent>(TEXT("BottomRight"));
	BottomRight->SetupAttachment(SceneComponent);
	//Create Attachments to spwan Items on
	BottomLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("BottomLeft"));
	BottomLeft->SetupAttachment(SceneComponent);
	//Create the collison box to delete the Island after the player passed it 
	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorTriggerBox"));
	FloorTriggerBox->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetBoxExtent(FVector(32.f, 500.f, 200.f));
	FloorTriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));



}

// Called when the game starts or when spawned
void ALavaLevelSpawner::BeginPlay()
{
	Super::BeginPlay();
	//Calls to see if RunGameMode being Called 
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);
	//Calls to active Trigger box on Island For overlap
	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALavaLevelSpawner::OnTriggerBoxOverlap);
}

// Called every frame
void ALavaLevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALavaLevelSpawner::SpawnItems()
{
	//Checks to see if the Obstacles and items are Valid to spawn them and not crash the game
	if (IsValid(SmallObstacleClass) && IsValid(BigObstacleClass) && IsValid(CoinItemClass) && IsValid(SpeedClass))
	{
		SpawnLaneItems(MiddleLeft);
		SpawnLaneItems(Middle);
		SpawnLaneItems(MiddleRight);
		SpawnLaneItems(BottomLeft);
		SpawnLaneItems(BottomMiddle);
		SpawnLaneItems(BottomRight);
		SpawnLaneItems(TopLeft);
		SpawnLaneItems(TopMiddle);
		SpawnLaneItems(TopRight);
	}
}
//The math used to spawn every item in diffrent areas they all have a percentage all the way to 1.f
void ALavaLevelSpawner::SpawnLaneItems(UArrowComponent* Lane)
{
	const float RandVal = FMath::FRandRange(0.f, 1.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform& SpawnLocation = Lane->GetComponentTransform();

	if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent1, SpawnPercent2, true, true))
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(SmallObstacleClass, SpawnLocation, SpawnParameters);
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent2, SpawnPercent3, true, true))
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(BigObstacleClass, SpawnLocation, SpawnParameters);
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent3, 0.8f, true, true))
	{
		ACoinItem* Coin = GetWorld()->SpawnActor<ACoinItem>(CoinItemClass, SpawnLocation, SpawnParameters);
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, 0.9f, 1.f, true, true))
	{
		ASuperSpeed* Speed = GetWorld()->SpawnActor<ASuperSpeed>(SpeedClass, SpawnLocation, SpawnParameters);
	}


}
//Used to add more floors when the Trigger box is overlap at the end of the Current Island
void ALavaLevelSpawner::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunner* RunCharacter = Cast<ARunner>(OtherActor);


	if (RunCharacter)
	{
		RunGameMode->AddFloorTileMiddle(true);
		RunGameMode->AddFloorTileLeft(true);
		RunGameMode->AddFloorTileRight(true);

		GetWorldTimerManager().SetTimer(DestroyHandle, this, &ALavaLevelSpawner::DestroyFloorTile, 2.f, false);
	}
}


//Used to Destroy Previous Islands
void ALavaLevelSpawner::DestroyFloorTile()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	this->Destroy();
}
