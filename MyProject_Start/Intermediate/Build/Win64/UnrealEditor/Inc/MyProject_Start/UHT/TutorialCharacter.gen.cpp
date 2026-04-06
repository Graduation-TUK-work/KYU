// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/Player/TutorialCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTutorialCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
MOTIONWARPING_API UClass* Z_Construct_UClass_UMotionWarpingComponent_NoRegister();
MYPROJECT_START_API UClass* Z_Construct_UClass_ATutorialCharacter();
MYPROJECT_START_API UClass* Z_Construct_UClass_ATutorialCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATutorialCharacter Function SetCanVault **********************************
struct Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics
{
	struct TutorialCharacter_eventSetCanVault_Parms
	{
		bool CanIt;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd(\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xa3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd(\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetCanVault constinit property declarations ***************************
	static void NewProp_CanIt_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_CanIt;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetCanVault constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetCanVault Property Definitions **************************************
void Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::NewProp_CanIt_SetBit(void* Obj)
{
	((TutorialCharacter_eventSetCanVault_Parms*)Obj)->CanIt = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::NewProp_CanIt = { "CanIt", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TutorialCharacter_eventSetCanVault_Parms), &Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::NewProp_CanIt_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::NewProp_CanIt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::PropPointers) < 2048);
// ********** End Function SetCanVault Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATutorialCharacter, nullptr, "SetCanVault", 	Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::TutorialCharacter_eventSetCanVault_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATutorialCharacter_SetCanVault_Statics::Function_MetaDataParams)},  };
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
DEFINE_FUNCTION(ATutorialCharacter::execSetCanVault)
{
	P_GET_UBOOL(Z_Param_CanIt);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetCanVault(Z_Param_CanIt);
	P_NATIVE_END;
}
// ********** End Class ATutorialCharacter Function SetCanVault ************************************

// ********** Begin Class ATutorialCharacter *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ATutorialCharacter;
UClass* ATutorialCharacter::GetPrivateStaticClass()
{
	using TClass = ATutorialCharacter;
	if (!Z_Registration_Info_UClass_ATutorialCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TutorialCharacter"),
			Z_Registration_Info_UClass_ATutorialCharacter.InnerSingleton,
			StaticRegisterNativesATutorialCharacter,
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
	return Z_Registration_Info_UClass_ATutorialCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_ATutorialCharacter_NoRegister()
{
	return ATutorialCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATutorialCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Player/TutorialCharacter.h" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveForwardValue_MetaData[] = {
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveRightValue_MetaData[] = {
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AimYaw_MetaData[] = {
		{ "Category", "TutorialCharacter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd \xef\xbf\xbd\xd3\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd \xef\xbf\xbd\xd3\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AimPitch_MetaData[] = {
		{ "Category", "TutorialCharacter" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpringArm_MetaData[] = {
		{ "Category", "TutorialCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "Category", "TutorialCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VaultMontage_MetaData[] = {
		{ "Category", "Vault" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MotionWarping_MetaData[] = {
		{ "Category", "TutorialCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Player/TutorialCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ATutorialCharacter constinit property declarations ***********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveForwardValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveRightValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AimYaw;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AimPitch;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpringArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_VaultMontage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MotionWarping;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ATutorialCharacter constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("SetCanVault"), .Pointer = &ATutorialCharacter::execSetCanVault },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ATutorialCharacter_SetCanVault, "SetCanVault" }, // 3236886475
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATutorialCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ATutorialCharacter_Statics

// ********** Begin Class ATutorialCharacter Property Definitions **********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveForwardValue = { "MoveForwardValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, MoveForwardValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveForwardValue_MetaData), NewProp_MoveForwardValue_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveRightValue = { "MoveRightValue", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, MoveRightValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveRightValue_MetaData), NewProp_MoveRightValue_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimYaw = { "AimYaw", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, AimYaw), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AimYaw_MetaData), NewProp_AimYaw_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimPitch = { "AimPitch", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, AimPitch), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AimPitch_MetaData), NewProp_AimPitch_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_SpringArm = { "SpringArm", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, SpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringArm_MetaData), NewProp_SpringArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_VaultMontage = { "VaultMontage", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, VaultMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VaultMontage_MetaData), NewProp_VaultMontage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MotionWarping = { "MotionWarping", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialCharacter, MotionWarping), Z_Construct_UClass_UMotionWarpingComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MotionWarping_MetaData), NewProp_MotionWarping_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATutorialCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveForwardValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MoveRightValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimYaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_AimPitch,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_SpringArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_VaultMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialCharacter_Statics::NewProp_MotionWarping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::PropPointers) < 2048);
// ********** End Class ATutorialCharacter Property Definitions ************************************
UObject* (*const Z_Construct_UClass_ATutorialCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialCharacter_Statics::DependentSingletons) < 16);
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
void ATutorialCharacter::StaticRegisterNativesATutorialCharacter()
{
	UClass* Class = ATutorialCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ATutorialCharacter_Statics::Funcs));
}
UClass* Z_Construct_UClass_ATutorialCharacter()
{
	if (!Z_Registration_Info_UClass_ATutorialCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATutorialCharacter.OuterSingleton, Z_Construct_UClass_ATutorialCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATutorialCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ATutorialCharacter);
ATutorialCharacter::~ATutorialCharacter() {}
// ********** End Class ATutorialCharacter *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h__Script_MyProject_Start_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATutorialCharacter, ATutorialCharacter::StaticClass, TEXT("ATutorialCharacter"), &Z_Registration_Info_UClass_ATutorialCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATutorialCharacter), 3367666858U) },
	};
}; // Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h__Script_MyProject_Start_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h__Script_MyProject_Start_3521606530{
	TEXT("/Script/MyProject_Start"),
	Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h__Script_MyProject_Start_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_Player_TutorialCharacter_h__Script_MyProject_Start_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
