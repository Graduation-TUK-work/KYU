// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/KillerGameModeBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKillerGameModeBase() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
MYPROJECT_START_API UClass* Z_Construct_UClass_AKillerGameModeBase();
MYPROJECT_START_API UClass* Z_Construct_UClass_AKillerGameModeBase_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AKillerGameModeBase ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AKillerGameModeBase;
UClass* AKillerGameModeBase::GetPrivateStaticClass()
{
	using TClass = AKillerGameModeBase;
	if (!Z_Registration_Info_UClass_AKillerGameModeBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("KillerGameModeBase"),
			Z_Registration_Info_UClass_AKillerGameModeBase.InnerSingleton,
			StaticRegisterNativesAKillerGameModeBase,
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
	return Z_Registration_Info_UClass_AKillerGameModeBase.InnerSingleton;
}
UClass* Z_Construct_UClass_AKillerGameModeBase_NoRegister()
{
	return AKillerGameModeBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AKillerGameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "KillerGameModeBase.h" },
		{ "ModuleRelativePath", "KillerGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA

// ********** Begin Class AKillerGameModeBase constinit property declarations **********************
// ********** End Class AKillerGameModeBase constinit property declarations ************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AKillerGameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AKillerGameModeBase_Statics
UObject* (*const Z_Construct_UClass_AKillerGameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AKillerGameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AKillerGameModeBase_Statics::ClassParams = {
	&AKillerGameModeBase::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AKillerGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AKillerGameModeBase_Statics::Class_MetaDataParams)
};
void AKillerGameModeBase::StaticRegisterNativesAKillerGameModeBase()
{
}
UClass* Z_Construct_UClass_AKillerGameModeBase()
{
	if (!Z_Registration_Info_UClass_AKillerGameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AKillerGameModeBase.OuterSingleton, Z_Construct_UClass_AKillerGameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AKillerGameModeBase.OuterSingleton;
}
AKillerGameModeBase::AKillerGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AKillerGameModeBase);
AKillerGameModeBase::~AKillerGameModeBase() {}
// ********** End Class AKillerGameModeBase ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h__Script_MyProject_Start_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AKillerGameModeBase, AKillerGameModeBase::StaticClass, TEXT("AKillerGameModeBase"), &Z_Registration_Info_UClass_AKillerGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AKillerGameModeBase), 2287638215U) },
	};
}; // Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h__Script_MyProject_Start_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h__Script_MyProject_Start_751044806{
	TEXT("/Script/MyProject_Start"),
	Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h__Script_MyProject_Start_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerGameModeBase_h__Script_MyProject_Start_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
