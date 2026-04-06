// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TutorialAnimInstance.h"

#ifdef MYPROJECT_START_TutorialAnimInstance_generated_h
#error "TutorialAnimInstance.generated.h already included, missing '#pragma once' in TutorialAnimInstance.h"
#endif
#define MYPROJECT_START_TutorialAnimInstance_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UTutorialAnimInstance ****************************************************
struct Z_Construct_UClass_UTutorialAnimInstance_Statics;
MYPROJECT_START_API UClass* Z_Construct_UClass_UTutorialAnimInstance_NoRegister();

#define FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUTutorialAnimInstance(); \
	friend struct ::Z_Construct_UClass_UTutorialAnimInstance_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MYPROJECT_START_API UClass* ::Z_Construct_UClass_UTutorialAnimInstance_NoRegister(); \
public: \
	DECLARE_CLASS2(UTutorialAnimInstance, UAnimInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/MyProject_Start"), Z_Construct_UClass_UTutorialAnimInstance_NoRegister) \
	DECLARE_SERIALIZER(UTutorialAnimInstance)


#define FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UTutorialAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UTutorialAnimInstance(UTutorialAnimInstance&&) = delete; \
	UTutorialAnimInstance(const UTutorialAnimInstance&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UTutorialAnimInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UTutorialAnimInstance); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UTutorialAnimInstance) \
	NO_API virtual ~UTutorialAnimInstance();


#define FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_12_PROLOG
#define FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_15_INCLASS_NO_PURE_DECLS \
	FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UTutorialAnimInstance;

// ********** End Class UTutorialAnimInstance ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
