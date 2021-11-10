

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runner.generated.h"


class UUserWidget;

UCLASS()
class INFINITERUNNER_API ARunner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunner();


protected:
	//Calls to endlessRunnerGameMode
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* RunGameMode;
	//Calls to gameInstance
	UPROPERTY(VisibleInstanceOnly)
		class UMyGameInstance* Game;
	//Called to Destroy Obstacle
	UPROPERTY(VisibleInstanceOnly)
		class AObstacle* Dest;
	//Called to Create PowerUp Icon
	UPROPERTY(VisibleInstanceOnly)
		class UGameHUDWidget* PowerTimer;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Create on Death Function
	UFUNCTION()
		void OnDeath();

	UPROPERTY()
		FTimerHandle RestartTimerHandle;

	UPROPERTY()
		FTimerHandle PowerUpRestartTimerHandle;



public:
	//Set Default Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Varibles")
		float RunSpeed = 3000;
	//Checks to see if dead
	UPROPERTY()
		bool rIsDead = false;
	//Checks to see if powerUp is on
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PowerUpOn = false;

	UPROPERTY()
		bool SuperFly = false;
	//Function used to Create Coins and PowerUps
	UFUNCTION()
		void AddCoin();

	UFUNCTION()
		void PowerUp();

	UFUNCTION()
		void PowerUpOver();


	//Create Death particle
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		class UParticleSystem* DeathParticleSystem;
	//Create Death Sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		class USoundBase* DeathSound;
	//creates death Particle for falling out of World
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		class UParticleSystem* DeathFallParticleSystem;
	//Create the death sound for falling
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		class USoundBase* DeathFallSound;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Create Function For Death
	virtual void FellOutOfWorld(const UDamageType& dmgType) override;

	UFUNCTION(BlueprintCallable)
		void Death();

	UFUNCTION(BlueprintCallable)
		void FallDeath();

};
