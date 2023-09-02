// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(30,7,7));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);


	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 0;
	Movement->MaxSpeed = 2000.0f;
	Movement->InitialSpeed = 2000.0f;



}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	

	SetLifeSpan(3.f);

	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessBeginOverlap);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CallCPPToBP();

	if (Effect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Effect, GetActorLocation(), GetActorRotation());
	}
	if (EffectSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), EffectSound, GetActorLocation(), GetActorRotation());
	}
	
	this->Destroy();
	
}



