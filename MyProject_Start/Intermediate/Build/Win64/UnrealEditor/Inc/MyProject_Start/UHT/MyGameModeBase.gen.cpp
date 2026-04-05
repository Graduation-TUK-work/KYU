// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/MyGameModeBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMyGameModeBase() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
MYPROJECT_START_API UClass* Z_Construct_UClass_AMyGameModeBase();
MYPROJECT_START_API UClass* Z_Construct_UClass_AMyGameModeBase_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMyGameModeBase **********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMyGameModeBase;
UClass* AMyGameModeBase::GetPrivateStaticClass()
{
	using TClass = AMyGameModeBase;
	if (!Z_Registration_Info_UClass_AMyGameModeBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MyGameModeBase"),
			Z_Registration_Info_UClass_AMyGameModeBase.InnerSingleton,
			StaticRegisterNativesAMyGameModeBase,
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
	return Z_Registration_Info_UClass_AMyGameModeBase.InnerSingleton;
}
UClass* Z_Construct_UClass_AMyGameModeBase_NoRegister()
{
	return AMyGameModeBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMyGameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "MyGameModeBase.h" },
		{ "ModuleRelativePath", "MyGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMyGameModeBase constinit property declarations **************************
// ********** End Class AMyGameModeBase constinit property declarations ****************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyGameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMyGameModeBase_Statics
UObject* (*const Z_Construct_UClass_AMyGameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyGameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyGameModeBase_Statics::ClassParams = {
	&AMyGameModeBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyGameModeBase_Statics::Class_MetaDataParams)
};
void AMyGameModeBase::StaticRegisterNativesAMyGameModeBase()
{
}
UClass* Z_Construct_UClass_AMyGameModeBase()
{
	if (!Z_Registration_Info_UClass_AMyGameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyGameModeBase.OuterSingleton, Z_Construct_UClass_AMyGameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyGameModeBase.OuterSingleton;
}
AMyGameModeBase::AMyGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMyGameModeBase);
AMyGameModeBase::~AMyGameModeBase() {}
// ********** End Class AMyGameModeBase ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_MyGameModeBase_h__Script_MyProject_Start_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyGameModeBase, AMyGameModeBase::StaticClass, TEXT("AMyGameModeBase"), &Z_Registration_Info_UClass_AMyGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyGameModeBase), 3987127137U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_MyGameModeBase_h__Script_MyProject_Start_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_MyGameModeBase_h__Script_MyProject_Start_2806879221{
	TEXT("/Script/MyProject_Start"),
	Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_MyGameModeBase_h__Script_MyProject_Start_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_MyGameModeBase_h__Script_MyProject_Start_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
