// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class IInteractable;
/**
 * 
 */
UCLASS()
class AURA_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputMappingContext> Context;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputAction> MoveAction;

	void Move(const struct FInputActionValue& InputActionValue);

	IInteractable* CursorTrace();
	IInteractable* PrevInteractableActor;
	
};
