// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IngenuityControl.generated.h"

UCLASS()
class RECRUITMENT_API AIngenuityControl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngenuityControl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BluePrintGetter = GetAtSamePosition, BlueprintSetter = SetAtSamePosition)
	bool AtSamePosition = true;
	bool CounterStarted = false;
	bool Reading = false;
	float counter = 0.0f;

	TArray<FTransform> TransformPipe;


	UStaticMeshComponent* Meshcomp;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CalculateMovement();
	void CheckSamePosition();

	UFUNCTION(BlueprintCallable, Category="DroneCommunication")
	void SendNewPosition(FTransform Transform);


	UFUNCTION(BlueprintSetter)
	void SetAtSamePosition(bool inAtSamePosition);

	UFUNCTION(BlueprintGetter)
		bool GetAtSamePosition();


};
