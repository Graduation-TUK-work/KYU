// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/TutorialAnimInstance.h"
#include "../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTutorialAnimInstance() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
	MYPROJECT_START_API UClass* Z_Construct_UClass_UTutorialAnimInstance();
	MYPROJECT_START_API UClass* Z_Construct_UClass_UTutorialAnimInstance_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// End Cross Module References
	void UTutorialAnimInstance::StaticRegisterNativesUTutorialAnimInstance()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTutorialAnimInstance);
	UClass* Z_Construct_UClass_UTutorialAnimInstance_NoRegister()
	{
		return UTutorialAnimInstance::StaticClass();
	}
	struct Z_Construct_UClass_UTutorialAnimInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Horizontal_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Horizontal;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Vertical_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Vertical;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTutorialAnimInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAnimInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAnimInstance_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTutorialAnimInstance_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "TutorialAnimInstance.h" },
		{ "ModuleRelativePath", "TutorialAnimInstance.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Horizontal_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Pawn" },
		{ "ModuleRelativePath", "TutorialAnimInstance.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Horizontal = { "Horizontal", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTutorialAnimInstance, Horizontal), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Horizontal_MetaData), Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Horizontal_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Vertical_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Pawn" },
		{ "ModuleRelativePath", "TutorialAnimInstance.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Vertical = { "Vertical", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTutorialAnimInstance, Vertical), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Vertical_MetaData), Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Vertical_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTutorialAnimInstance_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Horizontal,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAnimInstance_Statics::NewProp_Vertical,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTutorialAnimInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTutorialAnimInstance>::IsAbstract,
	};
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
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAnimInstance_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UTutorialAnimInstance()
	{
		if (!Z_Registration_Info_UClass_UTutorialAnimInstance.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTutorialAnimInstance.OuterSingleton, Z_Construct_UClass_UTutorialAnimInstance_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UTutorialAnimInstance.OuterSingleton;
	}
	template<> MYPROJECT_START_API UClass* StaticClass<UTutorialAnimInstance>()
	{
		return UTutorialAnimInstance::StaticClass();
	}
	UTutorialAnimInstance::UTutorialAnimInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTutorialAnimInstance);
	UTutorialAnimInstance::~UTutorialAnimInstance() {}
	struct Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UTutorialAnimInstance, UTutorialAnimInstance::StaticClass, TEXT("UTutorialAnimInstance"), &Z_Registration_Info_UClass_UTutorialAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTutorialAnimInstance), 4291670818U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_1687442759(TEXT("/Script/MyProject_Start"),
		Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_TutorialAnimInstance_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
