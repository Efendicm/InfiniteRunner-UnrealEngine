// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuperFly.generated.h"

UCLASS()
class INFINITERUNNER_API ASuperFly : public AActor
{
	GENERATED_BODY()
	

public:
	//Called if PowerUp is on or Off
	UPROPERTY(EditAnywhere)
		bool SuperFly = false;

	//Create The BluePrint Scene
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;
	//Creates the Mesh in BluePrints
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* PowerUpMesh;
	//Create the Sphere Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USphereComponent* SphereCollider;
	//let the Item Rotate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class URotatingMovementComponent* RotatingMovement;
	//Used to Create OverLap sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assests")
		class USoundBase* OverlapSound;

public:
	// Sets default values for this actor's properties
	ASuperFly();

public:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Makes the overlap Function
	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
