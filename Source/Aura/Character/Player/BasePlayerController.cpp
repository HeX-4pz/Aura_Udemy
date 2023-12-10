// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Aura/Interactable.h"

ABasePlayerController::ABasePlayerController()
{
	bReplicates = true;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(Context);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(Context, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Move);
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto Actor = CursorTrace();

	if (Actor)
	{
		if (!PrevInteractableActor)
		{
			Actor->Highlight();
		}
		else if (Actor != PrevInteractableActor)
		{
				Actor->Highlight();
				PrevInteractableActor->Unhighlight();
		}
	}
	else if (PrevInteractableActor)
	{
		PrevInteractableActor->Unhighlight();
	}

	PrevInteractableActor = Actor;
}

void ABasePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputVector = InputActionValue.Get<FVector2D>();

	UE_LOG(LogTemp, Warning, TEXT("x = %f, y = %f"), InputVector.X, InputVector.Y);

	if (const auto CurrentPawn = GetPawn())
	{
		CurrentPawn->AddMovementInput(FVector::UnitY(), InputVector.X);
		CurrentPawn->AddMovementInput(FVector::UnitX(), InputVector.Y);
	}
}

IInteractable* ABasePlayerController::CursorTrace()
{

	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		IInteractable* HitActor = Cast<IInteractable>(HitResult.GetActor());
		return HitActor;
	}
	return nullptr;
}
