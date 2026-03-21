// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/Player/TutorialCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTutorialCharacter() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	MYPROJECT_START_API UClass* Z_Construct_UClass_ATutorialCharacter();
	MYPROJECT_START_API UClass* Z_Construct_UClass_ATutorialCharacter_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// End Cross Module References
	DEFINE_FUNCTION(ATutorialCharacter::execSetCanVault)
	{
		P_GET_UBOOL(Z_Param_CanIt);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetCanVault(Z_Param_CanIt);
		P_NATIVE_END;
	}
	void ATutorialCharacter::StaticRegisterNativesATutorialCharacter()
	{
		UClass* Class = ATutorialCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetCanVault", &ATutorialCharacter::execSetCanVault },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics
	{
		struct TutorialCharacter_eventSetCanVault_Parms
		{
			bool CanIt;
		};
		static void NewProp_CanIt_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_CanIt;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::NewProp_CanIt_SetBit(void* Obj)
	{
		((TutorialCharacter_eventSetCanVault_Parms*)Obj)->CanIt = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::NewProp_CanIt = { "CanIt", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TutorialCharacter_eventSetCanVault_Parms), &Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::NewProp_CanIt_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::NewProp_CanIt,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd(\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd(\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATutorialCharacter, nullptr, "SetCanVault", nullptr, nullptr, Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::PropPointers), sizeof(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::TutorialCharacter_eventSetCanVault_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::TutorialCharacter_eventSetCanVault_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ATutorialCharacter_SetCanVault()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATutorialCharacter);
	UClass* Z_Construct_UClass_ATutorialCharacter_NoRegister()
	{
		return ATutorialCharacter::StaticClass();
	}
	struct Z_Construct_UClass_ATutorialCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveForwardValue_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveForwardValue;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveRightValue_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveRightValue;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AimYaw_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AimYaw;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AimPitch_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AimPitch;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SpringArm_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SpringArm;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VaultMontage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_VaultMontage;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATutorialCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ATutorialCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ATutorialCharacter_SetCanVault, "SetCanVault" }, // 2253432965
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATutorialCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Player/TutorialCharacter.h" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveForwardValue_MetaData[] = {
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveForwardValue = { "MoveForwardValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, MoveForwardValue), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveForwardValue_MetaData), Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveForwardValue_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveRightValue_MetaData[] = {
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveRightValue = { "MoveRightValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, MoveRightValue), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveRightValue_MetaData), Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveRightValue_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimYaw_MetaData[] = {
		{ "Category", "TutorialCharacter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd \xef\xbf\xbd\xd3\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd \xef\xbf\xbd\xd3\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimYaw = { "AimYaw", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, AimYaw), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimYaw_MetaData), Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimYaw_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimPitch_MetaData[] = {
		{ "Category", "TutorialCharacter" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimPitch = { "AimPitch", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, AimPitch), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimPitch_MetaData), Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimPitch_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_SpringArm_MetaData[] = {
		{ "Category", "TutorialCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_SpringArm = { "SpringArm", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, SpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_SpringArm_MetaData), Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_SpringArm_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_Camera_MetaData[] = {
		{ "Category", "TutorialCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_Camera_MetaData), Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_Camera_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_VaultMontage_MetaData[] = {
		{ "Category", "Animation" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_VaultMontage = { "VaultMontage", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, VaultMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_VaultMontage_MetaData), Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_VaultMontage_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATutorialCharacter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveForwardValue,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveRightValue,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimYaw,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimPitch,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_SpringArm,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_Camera,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_VaultMontage,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATutorialCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATutorialCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATutorialCharacter_Statics::ClassParams = {
		&ATutorialCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ATutorialCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ATutorialCharacter_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ATutorialCharacter()
	{
		if (!Z_Registration_Info_UClass_ATutorialCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATutorialCharacter.OuterSingleton, Z_Construct_UClass_ATutorialCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATutorialCharacter.OuterSingleton;
	}
	template<> MYPROJECT_START_API UClass* StaticClass<ATutorialCharacter>()
	{
		return ATutorialCharacter::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATutorialCharacter);
	ATutorialCharacter::~ATutorialCharacter() {}
	struct Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATutorialCharacter, ATutorialCharacter::StaticClass, TEXT("ATutorialCharacter"), &Z_Registration_Info_UClass_ATutorialCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATutorialCharacter), 3135692691U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_3555350231(TEXT("/Script/MyProject_Start"),
		Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
