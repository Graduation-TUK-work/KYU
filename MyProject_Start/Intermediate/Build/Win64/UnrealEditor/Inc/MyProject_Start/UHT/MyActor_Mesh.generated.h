// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MyActor_Mesh.h"

#ifdef MYPROJECT_START_MyActor_Mesh_generated_h
#error "MyActor_Mesh.generated.h already included, missing '#pragma once' in MyActor_Mesh.h"
#endif
#define MYPROJECT_START_MyActor_Mesh_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AMyActor_Mesh ************************************************************
struct Z_Construct_UClass_AMyActor_Mesh_Statics;
MYPROJECT_START_API UClass* Z_Construct_UClass_AMyActor_Mesh_NoRegister();

#define FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyActor_Mesh(); \
	friend struct ::Z_Construct_UClass_AMyActor_Mesh_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MYPROJECT_START_API UClass* ::Z_Construct_UClass_AMyActor_Mesh_NoRegister(); \
public: \
	DECLARE_CLASS2(AMyActor_Mesh, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject_Start"), Z_Construct_UClass_AMyActor_Mesh_NoRegister) \
	DECLARE_SERIALIZER(AMyActor_Mesh)


#define FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_12_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AMyActor_Mesh(AMyActor_Mesh&&) = delete; \
	AMyActor_Mesh(const AMyActor_Mesh&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyActor_Mesh); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyActor_Mesh); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMyActor_Mesh) \
	NO_API virtual ~AMyActor_Mesh();


#define FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_9_PROLOG
#define FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_12_INCLASS_NO_PURE_DECLS \
	FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AMyActor_Mesh;

// ********** End Class AMyActor_Mesh **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
