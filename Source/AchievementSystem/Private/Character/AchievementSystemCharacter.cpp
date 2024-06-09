// Copyright Epic Games, Inc. All Rights Reserved.

//game
#include "Character/AchievementSystemCharacter.h"
#include "Weapons/AchievementSystemProjectile.h"
#include "UserInterface/AchievementSystemHUD.h"
#include "Components/AchievementComponent.h"

//engine
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"




//////////////////////////////////////////////////////////////////////////
// AAchievementSystemCharacter

AAchievementSystemCharacter::AAchievementSystemCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	PreviousPosition = FVector::ZeroVector;

	// Create default subobject for the AchievementComponent
	AchievementComponent = CreateDefaultSubobject<UAchievementComponent>(TEXT("AchievementComponent"));
}



void AAchievementSystemCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Check if AchievementComponent is valid
	if (!AchievementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AchievementComponent is not properly initialized in AAchievementSystemCharacter"));
		return;
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	PreviousPosition = GetActorLocation();

	//Linking C++ and editor HUDs
	HUD = Cast<AAchievementSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

//////////////////////////////////////////////////////////////////////////// Input

void AAchievementSystemCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AAchievementSystemCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAchievementSystemCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAchievementSystemCharacter::Look);
		
		//TogglingMenu
		EnhancedInputComponent->BindAction(ToggleMenuAction, ETriggerEvent::Triggered, this, &AAchievementSystemCharacter::ToggleMenu);


		//TogglingAchievementPanel
		EnhancedInputComponent->BindAction(ToggleAchievementPanelAction, ETriggerEvent::Triggered, this, &AAchievementSystemCharacter::ToggleAchievementPanel);
	}
}


void AAchievementSystemCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);

		FVector CurrentPosition = GetActorLocation();
		float DistanceTraveled = FVector::Dist(PreviousPosition, CurrentPosition);

		if (DistanceTraveled > 0.0f)
		{
			// Update total distance traveled
			AccumulatedDistance += DistanceTraveled;

			// Check if we've accumulated at least 1 meter
			if (AccumulatedDistance >= 100.0f)  // 100 Unreal units = 1 meter
			{
				float MetersTraveled = AccumulatedDistance / 100.0f;  // Convert to meters
				if (AchievementComponent)
				{
					// Call the delegate to track distance traveled
					AchievementComponent->OnDistanceTraveled.Broadcast(MetersTraveled);
				}

				// Reset accumulated distance
				AccumulatedDistance = 0.0f;
			}

			// Update previous position
			PreviousPosition = CurrentPosition;
		}
	}
}

void AAchievementSystemCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAchievementSystemCharacter::ToggleMenu()
{
	if (HUD)
	{
		if(HUD->IsAchievementBoxVisible())
		{
			HUD->HideAchievementBox();
		}

		HUD->ToggleMenu();
	}
}

void AAchievementSystemCharacter::ToggleAchievementPanel()
{
	if (HUD)
	{
		if (HUD->IsMenuVisible())
		{
			HUD->HideMenu();
		}

		HUD->ToggleAchievementBox();
	}
}

void AAchievementSystemCharacter::Jump()
{
	Super::Jump();

	if (GetCharacterMovement() && GetCharacterMovement()->IsMovingOnGround())
	{
		AchievementComponent->OnJumpMade.Broadcast();
	}
}

void AAchievementSystemCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AAchievementSystemCharacter::GetHasRifle()
{
	return bHasRifle;
}