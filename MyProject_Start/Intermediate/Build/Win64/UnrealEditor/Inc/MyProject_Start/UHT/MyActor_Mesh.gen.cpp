// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/MyActor_Mesh.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMyActor_Mesh() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
MYPROJECT_START_API UClass* Z_Construct_UClass_AMyActor_Mesh();
MYPROJECT_START_API UClass* Z_Construct_UClass_AMyActor_Mesh_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMyActor_Mesh ************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMyActor_Mesh;
UClass* AMyActor_Mesh::GetPrivateStaticClass()
{
	using TClass = AMyActor_Mesh;
	if (!Z_Registration_Info_UClass_AMyActor_Mesh.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MyActor_Mesh"),
			Z_Registration_Info_UClass_AMyActor_Mesh.InnerSingleton,
			StaticRegisterNativesAMyActor_Mesh,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AMyActor_Mesh.InnerSingleton;
}
UClass* Z_Construct_UClass_AMyActor_Mesh_NoRegister()
{
	return AMyActor_Mesh::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMyActor_Mesh_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "MyActor_Mesh.h" },
		{ "ModuleRelativePath", "MyActor_Mesh.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMyActor_Mesh constinit property declarations ****************************
// ********** End Class AMyActor_Mesh constinit property declarations ******************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyActor_Mesh>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMyActor_Mesh_Statics
UObject* (*const Z_Construct_UClass_AMyActor_Mesh_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyActor_Mesh_Statics::DependentSingletons) < 16);
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
void AMyActor_Mesh::StaticRegisterNativesAMyActor_Mesh()
{
}
UClass* Z_Construct_UClass_AMyActor_Mesh()
{
	if (!Z_Registration_Info_UClass_AMyActor_Mesh.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyActor_Mesh.OuterSingleton, Z_Construct_UClass_AMyActor_Mesh_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyActor_Mesh.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMyActor_Mesh);
AMyActor_Mesh::~AMyActor_Mesh() {}
// ********** End Class AMyActor_Mesh **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h__Script_MyProject_Start_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyActor_Mesh, AMyActor_Mesh::StaticClass, TEXT("AMyActor_Mesh"), &Z_Registration_Info_UClass_AMyActor_Mesh, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyActor_Mesh), 2889310484U) },
	};
}; // Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h__Script_MyProject_Start_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h__Script_MyProject_Start_2936426983{
	TEXT("/Script/MyProject_Start"),
	Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h__Script_MyProject_Start_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_MyActor_Mesh_h__Script_MyProject_Start_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
