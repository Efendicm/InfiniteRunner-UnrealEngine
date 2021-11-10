

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class INFINITERUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()

public:
	//Used to see if player has power up or not
	UPROPERTY(EditAnywhere)
		bool Dest = false;
	//Function to destroy the current Obstacle
	UFUNCTION()
		void DestroyObstacle();

	//Create the scene for the Obstacle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;
	//Create the Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* StaticMesh;


	// Sets default values for this actor's properties
	AObstacle();
	//Used to Set collison on the Obstacles
	UFUNCTION()
		void OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

