

#include "Runner.h"
#include "SuperSpeed.h"
#include "EndlessRunnerGameModeBase.h"
#include "LavaLevelGameMode.h"
#include "SpaceGameMode.h"
#include "WaterGameMode.h"
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
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	LavaGameMode = Cast<ALavaLevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	SpaceGameMode = Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	WaterGameMode = Cast<AWaterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (RunGameMode)
		{
			//Calls RunGameMode Class
			check(RunGameMode);
		}
		if (LavaGameMode)
		{
			//Calls LavaGameMode Class
			check(LavaGameMode);
		}
		if (SpaceGameMode)
		{
			//Calls SpaceGameMode Class
			check(SpaceGameMode);
		}
		if (WaterGameMode)
		{
			//Calls SpaceGameMode Class
			check(WaterGameMode);
		}

	Super::BeginPlay();
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
	if (RunGameMode)
	{
		RunGameMode->GameOver();
		RunGameMode->GamePaused();
	}
	if (LavaGameMode)
	{
		LavaGameMode->GameOver();
		LavaGameMode->GamePaused();
	}
	if (SpaceGameMode)
	{
		SpaceGameMode->GameOver();
		SpaceGameMode->GamePaused();
	}
	if (WaterGameMode)
	{
		WaterGameMode->GameOver();
		WaterGameMode->GamePaused();
	}
}
//Used for player Coin Collision 
void ARunner::AddCoin()
{
	if (RunGameMode)
	{
		RunGameMode->AddCoin();
	}
	if (LavaGameMode)
	{
		LavaGameMode->AddCoin();
	}
	if (SpaceGameMode)
	{
		SpaceGameMode->AddCoin();
	}
	if (WaterGameMode)
	{
		WaterGameMode->AddCoin();
	}

}
//Calls powerUp to activate
void ARunner::PowerUp()
{
	PowerUpOn = true;
	if (RunGameMode)
	{
		RunGameMode->PowerUpOn = true;
		RunGameMode->PowerUp();
	}
	if (LavaGameMode)
	{
		LavaGameMode->PowerUpOn = true;
		LavaGameMode->PowerUp();
	}
	if (SpaceGameMode)
	{
		SpaceGameMode->PowerUpOn = true;
		SpaceGameMode->PowerUp();
	}
	if (WaterGameMode)
	{
		WaterGameMode->PowerUpOn = true;
		WaterGameMode->PowerUp();
	}
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
	if (RunGameMode)
	{
		RunGameMode->PowerUpOn = false;
		RunGameMode->PowerUp();
	}
	if (LavaGameMode)
	{
		LavaGameMode->PowerUpOn = false;
		LavaGameMode->PowerUp();
	}
	if (SpaceGameMode)
	{
		SpaceGameMode->PowerUpOn = false;
		SpaceGameMode->PowerUp();
	}
	if (WaterGameMode)
	{
		WaterGameMode->PowerUpOn = false;
		WaterGameMode->PowerUp();
	}
}
void ARunner::SuperFly()
{
	SuperFlying = true;
	if (RunGameMode)
	{
		RunGameMode->SuperFlying = true;
		RunGameMode->PowerUp();
	}
	if (LavaGameMode)
	{
		LavaGameMode->SuperFlying = true;
		LavaGameMode->PowerUp();
	}
	if (SpaceGameMode)
	{
		SpaceGameMode->SuperFlying = true;
		SpaceGameMode->PowerUp();
	}
	if (WaterGameMode)
	{
		WaterGameMode->SuperFlying = true;
		WaterGameMode->PowerUp();
	}
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(SuperFlyRestartTimerHandle, this, &ARunner::SuperFlyOver, 10.f);
	}
}
void ARunner::SuperFlyOver()
{
	SuperFlying = false;
	if (SuperFlyRestartTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(SuperFlyRestartTimerHandle);
	}
	if (RunGameMode)
	{
		RunGameMode->SuperFlying = false;
		RunGameMode->PowerUp();
	}
	if (LavaGameMode)
	{
		LavaGameMode->SuperFlying = false;
		LavaGameMode->PowerUp();
	}
	if (SpaceGameMode)
	{
		SpaceGameMode->SuperFlying = false;
		SpaceGameMode->PowerUp();
	}
	if (WaterGameMode)
	{
		WaterGameMode->SuperFlying = false;
		WaterGameMode->PowerUp();
	}
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

