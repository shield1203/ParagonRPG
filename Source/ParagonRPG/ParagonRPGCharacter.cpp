#include "ParagonRPGCharacter.h"
#include "ParagonRPGGameInstance.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharacterAnimInstance.h"
#include "SkillComponentBase.h"
#include "CharacterSkillComponent.h"
#include "ComboComponent.h"
#include "DungeonGameMode.h"

AParagonRPGCharacter::AParagonRPGCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
	
	Tags.Add(FName("Player"));
	
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 1.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 370.0f; // The camera follows at this distance behind the character
	CameraBoom->SetWorldLocation(FVector(0.0f, 0.0f, 70.0f));
	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	m_skillComponent = CreateDefaultSubobject<UCharacterSkillComponent>(TEXT("ChracterSkillComponet"));
	m_skillComponent->SetupAttachment(RootComponent);

	m_comboComponent = CreateDefaultSubobject<UComboComponent>(TEXT("ComboComponent"));
}

void AParagonRPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_skillComponent->Initialize();

	m_level = 1;
	LoadCharacterData();
	m_curHP = m_characterData.MaxHP;
	m_curMP = m_characterData.MaxMP;
	m_curExp = 0;
}

void AParagonRPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_characterAnimInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	m_characterAnimInstance->OnAttackHitCheck.BindUFunction(this, FName("AttackHitCheck"));
	m_characterAnimInstance->OnSkill.BindUFunction(m_skillComponent, FName("Execute"));
}

float AParagonRPGCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float fResultDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("This actor : Player"));
	if (m_characterAnimInstance->IsDeath()) return fResultDamage;

	m_curHP -= Damage;

	if (m_curHP > 0.f)
	{
		m_characterAnimInstance->StartHit();
	}
	else
	{
		m_characterAnimInstance->StartDeath();

		ADungeonGameMode* pGameMode = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode());
		if (pGameMode != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("GameOver"));
			pGameMode->GameOver();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("is nullptr : GameMode"));
		}
	}

	return fResultDamage;
}

void AParagonRPGCharacter::LoadCharacterData()
{
	UWorld* pWorld = GetWorld();

	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed GameInstance : Character"));
		return;
	}

	FCharacterData* pCharacterData = pGameInstance->GetDataTable(EGameDataTable::CharacterData)->FindRow<FCharacterData>(FName(*(FString::FormatAsNumber(m_level))), FString(""));

	m_characterData.Power = pCharacterData->Power;
	m_characterData.MaxHP = pCharacterData->MaxHP;
	m_characterData.MaxMP = pCharacterData->MaxMP;
	m_characterData.MaxExp = pCharacterData->MaxExp;
}

void AParagonRPGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AParagonRPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AParagonRPGCharacter::MoveRight);

	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AParagonRPGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AParagonRPGCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AParagonRPGCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AParagonRPGCharacter::TouchStopped);
}

void AParagonRPGCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AParagonRPGCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AParagonRPGCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AParagonRPGCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AParagonRPGCharacter::MoveForward(float Value)
{
	if (!m_characterAnimInstance->CanAction()) return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AParagonRPGCharacter::MoveRight(float Value)
{
	if (!m_characterAnimInstance->CanAction()) return;

	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

UComboComponent* AParagonRPGCharacter::GetComboComponent() const
{
	return m_comboComponent;
}

uint8 AParagonRPGCharacter::GetLevel() const
{
	return m_level;
}

float AParagonRPGCharacter::GetHP() const
{
	return (m_curHP / m_characterData.MaxHP);
}
 
float AParagonRPGCharacter::GetMP() const
{
	return (m_curMP / m_characterData.MaxMP);
}

float AParagonRPGCharacter::GetCurExp() const
{
	return m_curExp;
}

float AParagonRPGCharacter::GetMaxExp() const
{
	return m_characterData.MaxExp;
}

uint8 AParagonRPGCharacter::GetComboCount() const
{
	return m_comboComponent->GetComboCount();
}

void AParagonRPGCharacter::Attack()
{
	m_characterAnimInstance->StartAttack();
}

void AParagonRPGCharacter::AttackHitCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("HitCheck!! "));
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bResult = GetWorld()->SweepMultiByChannel(HitResults, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.0f, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(200.0f));

	if (!bResult) return;
	
	for (FHitResult HitResult : HitResults)
	{
		if (HitResult.GetActor()->ActorHasTag("Enemy"))
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(m_characterData.Power, DamageEvent, GetController(), this);
			m_comboComponent->CountingCombo();
			UE_LOG(LogTemp, Warning, TEXT("Count : %s"), *HitResult.Actor->GetFName().ToString());
		}
	}
}

void AParagonRPGCharacter::Skill(ESkillActorType skillType)
{
	if (!m_skillComponent->CanExecute(skillType, m_curMP)) return;

	m_characterAnimInstance->StartSkill(skillType);
}