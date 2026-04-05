// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/TutorialAnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTutorialAnimInstance() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
MYPROJECT_START_API UClass* Z_Construct_UClass_UTutorialAnimInstance();
MYPROJECT_START_API UClass* Z_Construct_UClass_UTutorialAnimInstance_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UTutorialAnimInstance ****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UTutorialAnimInstance;
UClass* UTutorialAnimInstance::GetPrivateStaticClass()
{
	using TClass = UTutorialAnimInstance;
	if (!Z_Registration_Info_UClass_UTutorialAnimInstance.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TutorialAnimInstance"),
			Z_Registration_Info_UClass_UTutorialAnimInstance.InnerSingleton,
			StaticRegisterNativesUTutorialAnimInstance,
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
	return Z_Registration_Info_UClass_UTutorialAnimInstance.InnerSingleton;
}
UClass* Z_Construct_UClass_UTutorialAnimInstance_NoRegister()
{
	return UTutorialAnimInstance::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UTutorialAnimInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "TutorialAnimInstance.h" },
		{ "ModuleRelativePath", "TutorialAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Horizontal_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Pawn" },
		{ "ModuleRelativePath", "TutorialAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Vertical_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Pawn" },
		{ "ModuleRelativePath", "TutorialAnimInstance.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UTutorialAnimInstance constinit property declarations ********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Horizontal;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Vertical;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UTutorialAnimInstance constinit property declarations **********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTutorialAnimInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UTutorialAnimInstance_Statics

// ********** Begin Class UTutorialAnimInstance Property Definitions *******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Horizontal = { "Horizontal", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTutorialAnimInstance, Horizontal), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Horizontal_MetaData), NewProp_Horizontal_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Vertical = { "Vertical", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTutorialAnimInstance, Vertical), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Vertical_MetaData), NewProp_Vertical_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTutorialAnimInstance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Horizontal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Vertical,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAnimInstance_Statics::PropPointers) < 2048);
// ********** End Class UTutorialAnimInstance Property Definitions *********************************
UObject* (*const Z_Construct_UClass_UTutorialAnimInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAnimInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTutorialAnimInstance_Statics::ClassParams = {
	&UTutorialAnimInstance::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UTutorialAnimInstance_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAnimInstance_Statics::PropPointers),
	0,
	0x009000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAnimInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UTutorialAnimInstance_Statics::Class_MetaDataParams)
};
void UTutorialAnimInstance::StaticRegisterNativesUTutorialAnimInstance()
{
}
UClass* Z_Construct_UClass_UTutorialAnimInstance()
{
	if (!Z_Registration_Info_UClass_UTutorialAnimInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTutorialAnimInstance.OuterSingleton, Z_Construct_UClass_UTutorialAnimInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTutorialAnimInstance.OuterSingleton;
}
UTutorialAnimInstance::UTutorialAnimInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UTutorialAnimInstance);
UTutorialAnimInstance::~UTutorialAnimInstance() {}
// ********** End Class UTutorialAnimInstance ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h__Script_MyProject_Start_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTutorialAnimInstance, UTutorialAnimInstance::StaticClass, TEXT("UTutorialAnimInstance"), &Z_Registration_Info_UClass_UTutorialAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTutorialAnimInstance), 2003118489U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h__Script_MyProject_Start_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h__Script_MyProject_Start_3866160981{
	TEXT("/Script/MyProject_Start"),
	Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h__Script_MyProject_Start_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Ham_Min_Kyu_Documents_GitHub_KYU_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h__Script_MyProject_Start_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
