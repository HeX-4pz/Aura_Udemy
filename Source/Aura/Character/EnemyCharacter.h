// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Aura/Interactable.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ABaseCharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Start Interactable
	virtual void Highlight() override;
	virtual void Unhighlight() override;
	// End Interactable

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bShouldHighlight = false;
};
