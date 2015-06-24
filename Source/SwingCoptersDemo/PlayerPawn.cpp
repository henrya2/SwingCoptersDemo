// Fill out your copyright notice in the Description page of Project Settings.

#include "SwingCoptersDemo.h"
#include "PlayerPawn.h"
#include "PaperFlipbookComponent.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetConstraintMode(EDOFMode::XZPlane);
	Box->SetSimulatePhysics(true);
	Box->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = Box;
	Box->OnComponentHit.AddDynamic(this, &APlayerPawn::HandleBoxHit);

	Bear = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Bear"));
	Bear->AttachParent = RootComponent;
	Wheels = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Wheels"));
	Wheels->AttachParent = RootComponent;

	HitSound = CreateDefaultSubobject<UAudioComponent>(TEXT("HitSound"));
	HitSound->AttachParent = RootComponent;
	HitSound->bAutoActivate = false;

	TapUpForce = 30000;
	LeftRightForce = 1500;

	bIsRightDirection = true;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GetVelocity().X >= 0)
	{
		if (!bIsRightDirection)
		{
			Bear->SetRelativeRotation(FRotator(0, 0, 0));
			bIsRightDirection = true;
		}
	}
	else
	{
		if (bIsRightDirection)
		{
			Bear->SetRelativeRotation(FRotator(0, 180.0f, 0));
			bIsRightDirection = false;
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::BeginTouch);
}

void APlayerPawn::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		FVector2D PlayerScreenLocation;
		PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), PlayerScreenLocation);

		float DeltaX = Location.X - PlayerScreenLocation.X;
		float XForce = DeltaX > 0 ? LeftRightForce : -LeftRightForce;

		Box->AddForce(FVector(XForce, 0, TapUpForce));
	}
}

void APlayerPawn::HandleBoxHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->ComponentHasTag(TEXT("Hammer")))
	{
		HitSound->Play();
	}
}

