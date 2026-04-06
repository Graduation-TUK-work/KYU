// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Player/TutorialCharacter.h"

#ifdef MYPROJECT_START_TutorialCharacter_generated_h
#error "TutorialCharacter.generated.h already included, missing '#pragma once' in TutorialCharacter.h"
#endif
#define MYPROJECT_START_TutorialCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATutorialCharacter *******************************************************
#define FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetCanVault);


struct Z_Construct_UClass_ATutorialCharacter_Statics;
MYPROJECT_START_API UClass* Z_Construct_UClass_ATutorialCharacter_NoRegister();

#define FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATutorialCharacter(); \
	friend struct ::Z_Construct_UClass_ATutorialCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MYPROJECT_START_API UClass* ::Z_Construct_UClass_ATutorialCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ATutorialCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject_Start"), Z_Construct_UClass_ATutorialCharacter_NoRegister) \
	DECLARE_SERIALIZER(ATutorialCharacter)


#define FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_13_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATutorialCharacter(ATutorialCharacter&&) = delete; \
	ATutorialCharacter(const ATutorialCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATutorialCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATutorialCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATutorialCharacter) \
	NO_API virtual ~ATutorialCharacter();


#define FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_10_PROLOG
#define FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_13_INCLASS_NO_PURE_DECLS \
	FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATutorialCharacter;

// ********** End Class ATutorialCharacter *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
