// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "GameFramework/Actor.h"
#include "SuperSpeed.generated.h"

UCLASS()
class INFINITERUNNER_API ASuperSpeed : public AActor
{
	GENERATED_BODY()
	
public:	
	//Create Function For PowerUp
	UFUNCTION()
		void PowerUp();
	//Called if PowerUp is on or Off
	UPROPERTY(EditAnywhere)
		bool SuperSpeed = false;

	//Create The BluePrint Scene
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;
	//Adds NiagaraComponent
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UNiagaraComponent* PowerUpPart;
	//Create the Sphere Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USphereComponent* SphereCollider;
	//let the Item Rotate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class URotatingMovementComponent* RotatingMovement;
	//Used to Create OverLap sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assests")
		class USoundBase* OverlapSound;

	// Sets default values for this actor's properties
	ASuperSpeed();
public:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Makes the overlap Function
	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	//Calls to activate power up Function
	UPROPERTY(EditAnyWhere)
		class AObstacle* PowerUpDestroy;

};
