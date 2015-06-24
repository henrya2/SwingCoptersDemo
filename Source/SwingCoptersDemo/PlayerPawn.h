// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SWINGCOPTERSDEMO_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
protected:
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);

	UFUNCTION()
	void HandleBoxHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TapUpForce;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LeftRightForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsRightDirection;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Bear;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperFlipbookComponent* Wheels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAudioComponent* HitSound;
};
