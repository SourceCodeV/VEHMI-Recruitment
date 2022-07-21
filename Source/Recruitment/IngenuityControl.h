// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PhysicsEngine/PhysicsThruster.h"
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
	UPROPERTY(BluePrintGetter = GetGrounded, BlueprintSetter = SetGrounded)
	bool Grounded = true;
	bool CounterStarted = false;
	bool Reading = false;
	float counter = 0.0f;

	TArray<FTransform> TransformPipe;

	UStaticMeshComponent* MeshComp;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CalculateMovement();
	void CheckGrounded();
	void ExeCuteVerticalControl(float zTransGoal);
	void ExecuteHorizontalControl(float xTransGoal, float yTransGoal);

	void ProportionalControl();

	UFUNCTION(BlueprintCallable, Category="DroneCommunication")
	void SendNewPosition(FTransform Transform);

	UFUNCTION(BlueprintImplementableEvent, Category = "DroneControl")
	void SetDroneThrust(float Thrust);

	UFUNCTION(BlueprintSetter)
	void SetGrounded(bool inAtSamePosition);

	UFUNCTION(BlueprintGetter)
	bool GetGrounded();


};
