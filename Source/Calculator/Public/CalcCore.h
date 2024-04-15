// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CalcCore.generated.h"

UCLASS()
class CALCULATOR_API ACalcCore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACalcCore();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CalcString;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CalcResult;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool InputString(FString S);

	UFUNCTION(BlueprintCallable)
	bool Evaluate();
};
