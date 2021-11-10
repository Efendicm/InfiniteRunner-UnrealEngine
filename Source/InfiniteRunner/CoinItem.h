// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinItem.generated.h"

class UUserWidget;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinTotal, int32, CoinTotal);


UCLASS()
class INFINITERUNNER_API ACoinItem : public AActor
{
	GENERATED_BODY()
	
public:	
	//Create a SceneComponent in Blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* SceneComponent;
	//Create a static mesh component in blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* CoinMesh;
	//Shows the sphere in blueprint and being able to call it
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USphereComponent* SphereCollider;
		//Create the rotation Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class URotatingMovementComponent* RotatingMovement;
	//Create the sound for the object
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assests")
		class USoundBase* OverlapSound;


	// Sets default values for this actor's properties
	ACoinItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Called when overlap begins with this actor
	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
