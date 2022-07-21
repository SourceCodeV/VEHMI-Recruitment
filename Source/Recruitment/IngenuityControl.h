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
	UPROPERTY(BluePrintGetter = GetGrounded, BluePrintSetter = SetGrounded)
	bool Grounded = true;
	UPROPERTY(BluePrintGetter = GetLanding, BluePrintSetter = SetLanding)
	bool Landing = false;
	float Zrotation = 0.0f;
	bool CounterStarted = false;
	bool Reading = false;
	float counter = 0.0f;

	TArray<FTransform> TransformPipe;

	UStaticMeshComponent* MeshComp;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CalculateMovement();
	void CheckLanding();
	void ExecuteVerticalControl(float zTransGoal);
	void ExecuteHorizontalControl(float xTransGoal, float yTransGoal, float zRotation);

	void ProportionalControl();

	UFUNCTION(BlueprintCallable, Category="DroneCommunication")
	void SendNewPosition(FTransform Transform);

	UFUNCTION(BlueprintCallable, Category = "DroneControl")
	void TakeOff();

	UFUNCTION(BlueprintCallable, Category = "DroneControl")
	void Rotate(float amount);

	UFUNCTION(BlueprintImplementableEvent, Category = "DroneControl")
	void SetDroneThrust(float Thrust);

	UFUNCTION(BlueprintGetter)
	bool GetGrounded();

	UFUNCTION(BlueprintSetter)
	void SetGrounded(bool isGrounded);

	UFUNCTION(BlueprintGetter)
	bool GetLanding();

	UFUNCTION(BlueprintSetter)
	void SetLanding(bool isLanding);

};
