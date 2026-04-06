// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KillerGameModeBase.h"

#ifdef MYPROJECT_START_KillerGameModeBase_generated_h
#error "KillerGameModeBase.generated.h already included, missing '#pragma once' in KillerGameModeBase.h"
#endif
#define MYPROJECT_START_KillerGameModeBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AKillerGameModeBase ******************************************************
struct Z_Construct_UClass_AKillerGameModeBase_Statics;
MYPROJECT_START_API UClass* Z_Construct_UClass_AKillerGameModeBase_NoRegister();

#define FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAKillerGameModeBase(); \
	friend struct ::Z_Construct_UClass_AKillerGameModeBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MYPROJECT_START_API UClass* ::Z_Construct_UClass_AKillerGameModeBase_NoRegister(); \
public: \
	DECLARE_CLASS2(AKillerGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject_Start"), Z_Construct_UClass_AKillerGameModeBase_NoRegister) \
	DECLARE_SERIALIZER(AKillerGameModeBase)


#define FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AKillerGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AKillerGameModeBase(AKillerGameModeBase&&) = delete; \
	AKillerGameModeBase(const AKillerGameModeBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AKillerGameModeBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AKillerGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AKillerGameModeBase) \
	NO_API virtual ~AKillerGameModeBase();


#define FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h_12_PROLOG
#define FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
	FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AKillerGameModeBase;

// ********** End Class AKillerGameModeBase ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
