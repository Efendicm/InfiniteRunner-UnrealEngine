// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Obstacle.h"
#include <InfiniteRunner/SuperSpeed.h>
#include "LavaLevelSpawner.generated.h"

class ACoinItem;
class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;
class UArrowComponent;



UCLASS()
class INFINITERUNNER_API ALavaLevelSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	//Create the Small Obstacles calling to the BluePrint
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<AObstacle> SmallObstacleClass;
	//Create the Big Obstacles calling to the BluePrint
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<AObstacle> BigObstacleClass;
	//Used to call the Power Up item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<ASuperSpeed> SpeedClass;
	//Used to call the Coins in game
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<ACoinItem> CoinItemClass;
	//used to create the Islands
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* SceneComponent;
	//create the mesh for the floors
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* FloorMesh;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* AttachMiddle;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* AttachRight;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* AttachLeft;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* TopMiddle;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* TopLeft;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* TopRight;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* MiddleRight;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* Middle;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* MiddleLeft;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* BottomRight;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* BottomMiddle;
	//Used to create the Spots for the items to spwan at using arrow Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UArrowComponent* BottomLeft;
	//used to create the Collison box at the end of the Island
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* FloorTriggerBox;
	//Used to create Spawn Percentages for Items
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent1 = 0.2f;
	//Used to create Spawn Percentages for Items
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent2 = 0.3f;
	//Used to create Spawn Percentages for Items
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent3 = 0.5f;

	//called to spawn the items
	UFUNCTION(BlueprintCallable)
		void SpawnItems();

	// Sets default values for this actor's properties
	ALavaLevelSpawner();
	FORCEINLINE const FTransform& GetAttachTransformLeft() const
	{
		return AttachLeft->GetComponentTransform();
	}
	FORCEINLINE const FTransform& GetAttachTransformMiddle() const
	{
		return AttachMiddle->GetComponentTransform();
	}
	FORCEINLINE const FTransform& GetAttachTransformRight() const
	{
		return AttachRight->GetComponentTransform();
	}

protected:
	//calls to see Gamemode
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* RunGameMode;
	//used to count down time before the Island destroyed
	UPROPERTY()
		FTimerHandle DestroyHandle;
	//Create the overlap for the Collison box
	UFUNCTION()
		void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//Used to Spawn items
	UFUNCTION()
		void SpawnLaneItems(UArrowComponent* Lane);
	//used to destroy Floors
	UFUNCTION()
		void DestroyFloorTile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
