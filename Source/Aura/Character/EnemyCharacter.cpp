// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

void AEnemyCharacter::Highlight()
{
	bShouldHighlight = true;
}

void AEnemyCharacter::Unhighlight()
{
	bShouldHighlight = false;
}

