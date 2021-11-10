


#include "Obstacle.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include <InfiniteRunner\Runner.h>
#include "SuperSpeed.h"



// Sets default values
AObstacle::AObstacle()
{
	//Create the Obsticle for the game
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;
	//Create the mesh for the obstacle
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);
	StaticMesh->OnComponentHit.AddDynamic(this, &AObstacle::OnObstacleHit);
}


void AObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Calls to see if player hit Obstacle to Either Die or Destroy the Obstacle
	ARunner* RunCharacter = Cast<ARunner>(OtherActor);
	if (RunCharacter && RunCharacter->PowerUpOn)
	{
		Destroy();
		Dest = true;
	}
	else if (RunCharacter)
	{	
		RunCharacter->Death();
	}
}
//Destroy The Obstacle
void AObstacle::DestroyObstacle()
{
	this->Destroy();
}

