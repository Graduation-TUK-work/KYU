// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KillerCharacter.h"

#ifdef MYPROJECT_START_KillerCharacter_generated_h
#error "KillerCharacter.generated.h already included, missing '#pragma once' in KillerCharacter.h"
#endif
#define MYPROJECT_START_KillerCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AKillerCharacter *********************************************************
#define FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execMoveRight); \
	DECLARE_FUNCTION(execMoveForward);


struct Z_Construct_UClass_AKillerCharacter_Statics;
MYPROJECT_START_API UClass* Z_Construct_UClass_AKillerCharacter_NoRegister();

#define FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAKillerCharacter(); \
	friend struct ::Z_Construct_UClass_AKillerCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MYPROJECT_START_API UClass* ::Z_Construct_UClass_AKillerCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AKillerCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject_Start"), Z_Construct_UClass_AKillerCharacter_NoRegister) \
	DECLARE_SERIALIZER(AKillerCharacter)


#define FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h_13_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AKillerCharacter(AKillerCharacter&&) = delete; \
	AKillerCharacter(const AKillerCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AKillerCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AKillerCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AKillerCharacter) \
	NO_API virtual ~AKillerCharacter();


#define FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h_10_PROLOG
#define FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h_13_INCLASS_NO_PURE_DECLS \
	FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AKillerCharacter;

// ********** End Class AKillerCharacter ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
