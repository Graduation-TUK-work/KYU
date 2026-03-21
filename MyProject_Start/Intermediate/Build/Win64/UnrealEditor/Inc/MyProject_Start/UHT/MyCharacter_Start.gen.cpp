// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/Player/MyCharacter_Start.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyCharacter_Start() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	MYPROJECT_START_API UClass* Z_Construct_UClass_AMyCharacter_Start();
	MYPROJECT_START_API UClass* Z_Construct_UClass_AMyCharacter_Start_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// End Cross Module References
	void AMyCharacter_Start::StaticRegisterNativesAMyCharacter_Start()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyCharacter_Start);
	UClass* Z_Construct_UClass_AMyCharacter_Start_NoRegister()
	{
		return AMyCharacter_Start::StaticClass();
	}
	struct Z_Construct_UClass_AMyCharacter_Start_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyCharacter_Start_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Start_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCharacter_Start_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Player/MyCharacter_Start.h" },
		{ "ModuleRelativePath", "Player/MyCharacter_Start.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyCharacter_Start_Statics::NewProp_Camera_MetaData[] = {
		{ "Category", "MyCharacter_Start" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Player/MyCharacter_Start.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyCharacter_Start_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x0020080000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyCharacter_Start, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Start_Statics::NewProp_Camera_MetaData), Z_Construct_UClass_AMyCharacter_Start_Statics::NewProp_Camera_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyCharacter_Start_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyCharacter_Start_Statics::NewProp_Camera,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMyCharacter_Start_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyCharacter_Start>::IsAbstract,
	};
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
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyCharacter_Start_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AMyCharacter_Start()
	{
		if (!Z_Registration_Info_UClass_AMyCharacter_Start.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyCharacter_Start.OuterSingleton, Z_Construct_UClass_AMyCharacter_Start_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMyCharacter_Start.OuterSingleton;
	}
	template<> MYPROJECT_START_API UClass* StaticClass<AMyCharacter_Start>()
	{
		return AMyCharacter_Start::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyCharacter_Start);
	AMyCharacter_Start::~AMyCharacter_Start() {}
	struct Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMyCharacter_Start, AMyCharacter_Start::StaticClass, TEXT("AMyCharacter_Start"), &Z_Registration_Info_UClass_AMyCharacter_Start, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyCharacter_Start), 2795209149U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h_1907633562(TEXT("/Script/MyProject_Start"),
		Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_MyCharacter_Start_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
