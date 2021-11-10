

#include "Runner.h"
#include "SuperSpeed.h"
#include "EndlessRunnerGameModeBase.h"
#include "Components/SphereComponent.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include "Components/SphereComponent.h"
#include "GameHUDWidget.h"
#include "Obstacle.h"
#include "MyGameInstance.h"

// Sets default values
ARunner::ARunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARunner::BeginPlay()
{
	Super::BeginPlay();
	//Calls RunGameMode Class
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);
}



// Called every frame
void ARunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ARunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Creates the PlayerInput
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//Calls to see if player is out of game Bounds
void ARunner::FellOutOfWorld(const UDamageType& dmgType)
{
	FallDeath();
}
//calls if player Dies
void ARunner::Death()
{

	if (!rIsDead)
	{
		const FVector Location = GetActorLocation();

		UWorld* World = GetWorld();
		if (World)
		{
			rIsDead = true;
			DisableInput(nullptr);
			//Create Death particle
			if (DeathParticleSystem)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World, DeathParticleSystem, Location);
			}
			//Create the death sound
			if (DeathSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
			}
			GetMesh()->SetVisibility(false);
			World->GetTimerManager().SetTimer(RestartTimerHandle, this, &ARunner::OnDeath, 2.f);
		}
	}
}
//calls at the End of death
void ARunner::OnDeath()
{
	rIsDead = false;
	if (RestartTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RestartTimerHandle);
	}
	RunGameMode->GameOver();
	RunGameMode->GamePaused();
}
//Used for player Coin Collision 
void ARunner::AddCoin()
{
	RunGameMode->AddCoin();

}
//Calls powerUp to activate
void ARunner::PowerUp()
{
	PowerUpOn = true;
	RunGameMode->PowerUpOn = true;
	RunGameMode->PowerUp();
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(PowerUpRestartTimerHandle, this, &ARunner::PowerUpOver, 10.f);
	}
}
//Calls when the powerup Ends
void ARunner::PowerUpOver()
{
	PowerUpOn = false;
	if (PowerUpRestartTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(PowerUpRestartTimerHandle);
	}
	RunGameMode->PowerUpOn = false;
	RunGameMode->PowerUp();
}
//Calls if player falls out of the World
void ARunner::FallDeath()
{
	if (!rIsDead)
	{
		const FVector Location = GetActorLocation();

		UWorld* World = GetWorld();
		if (World)
		{
			rIsDead = true;
			DisableInput(nullptr);
			if (DeathFallParticleSystem)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World, DeathFallParticleSystem, Location);
			}
			if (DeathFallSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, DeathFallSound, Location);
			}
			GetMesh()->SetVisibility(false);

			World->GetTimerManager().SetTimer(RestartTimerHandle, this, &ARunner::OnDeath, 1.f);
		}
	}
}

