// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/Player/MyCharacter_Start.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMyCharacter_Start() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
MYPROJECT_START_API UClass* Z_Construct_UClass_AMyCharacter_Start();
MYPROJECT_START_API UClass* Z_Construct_UClass_AMyCharacter_Start_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMyCharacter_Start *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMyCharacter_Start;
UClass* AMyCharacter_Start::GetPrivateStaticClass()
{
	using TClass = AMyCharacter_Start;
	if (!Z_Registration_Info_UClass_AMyCharacter_Start.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MyCharacter_Start"),
			Z_Registration_Info_UClass_AMyCharacter_Start.InnerSingleton,
			StaticRegisterNativesAMyCharacter_Start,
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
	return Z_Registration_Info_UClass_AMyCharacter_Start.InnerSingleton;
}
UClass* Z_Construct_UClass_AMyCharacter_Start_NoRegister()
{
	return AMyCharacter_Start::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMyCharacter_Start_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Player/MyCharacter_Start.h" },
		{ "ModuleRelativePath", "Player/MyCharacter_Start.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "Category", "MyCharacter_Start" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Player/MyCharacter_Start.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMyCharacter_Start constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMyCharacter_Start constinit property declarations *************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyCharacter_Start>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMyCharacter_Start_Statics

// ********** Begin Class AMyCharacter_Start Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Start_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x0020080000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter_Start, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyCharacter_Start_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Start_Statics::NewProp_Camera,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Start_Statics::PropPointers) < 2048);
// ********** End Class AMyCharacter_Start Property Definitions ************************************
UObject* (*const Z_Construct_UClass_AMyCharacter_Start_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Start_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyCharacter_Start_Statics::ClassParams = {
	&AMyCharacter_Start::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AMyCharacter_Start_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Start_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Start_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyCharacter_Start_Statics::Class_MetaDataParams)
};
void AMyCharacter_Start::StaticRegisterNativesAMyCharacter_Start()
{
}
UClass* Z_Construct_UClass_AMyCharacter_Start()
{
	if (!Z_Registration_Info_UClass_AMyCharacter_Start.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyCharacter_Start.OuterSingleton, Z_Construct_UClass_AMyCharacter_Start_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyCharacter_Start.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMyCharacter_Start);
AMyCharacter_Start::~AMyCharacter_Start() {}
// ********** End Class AMyCharacter_Start *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h__Script_MyProject_Start_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyCharacter_Start, AMyCharacter_Start::StaticClass, TEXT("AMyCharacter_Start"), &Z_Registration_Info_UClass_AMyCharacter_Start, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyCharacter_Start), 1774468745U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h__Script_MyProject_Start_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h__Script_MyProject_Start_1123928268{
	TEXT("/Script/MyProject_Start"),
	Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h__Script_MyProject_Start_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h__Script_MyProject_Start_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
