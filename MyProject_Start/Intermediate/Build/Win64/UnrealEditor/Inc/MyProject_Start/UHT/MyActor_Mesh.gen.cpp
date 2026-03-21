// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/MyActor_Mesh.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyActor_Mesh() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	MYPROJECT_START_API UClass* Z_Construct_UClass_AMyActor_Mesh();
	MYPROJECT_START_API UClass* Z_Construct_UClass_AMyActor_Mesh_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// End Cross Module References
	void AMyActor_Mesh::StaticRegisterNativesAMyActor_Mesh()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyActor_Mesh);
	UClass* Z_Construct_UClass_AMyActor_Mesh_NoRegister()
	{
		return AMyActor_Mesh::StaticClass();
	}
	struct Z_Construct_UClass_AMyActor_Mesh_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyActor_Mesh_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyActor_Mesh_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyActor_Mesh_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "MyActor_Mesh.h" },
		{ "ModuleRelativePath", "MyActor_Mesh.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMyActor_Mesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyActor_Mesh>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyActor_Mesh_Statics::ClassParams = {
		&AMyActor_Mesh::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyActor_Mesh_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyActor_Mesh_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AMyActor_Mesh()
	{
		if (!Z_Registration_Info_UClass_AMyActor_Mesh.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyActor_Mesh.OuterSingleton, Z_Construct_UClass_AMyActor_Mesh_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMyActor_Mesh.OuterSingleton;
	}
	template<> MYPROJECT_START_API UClass* StaticClass<AMyActor_Mesh>()
	{
		return AMyActor_Mesh::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyActor_Mesh);
	AMyActor_Mesh::~AMyActor_Mesh() {}
	struct Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMyActor_Mesh, AMyActor_Mesh::StaticClass, TEXT("AMyActor_Mesh"), &Z_Registration_Info_UClass_AMyActor_Mesh, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyActor_Mesh), 3571656321U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_3011525256(TEXT("/Script/MyProject_Start"),
		Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
