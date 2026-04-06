// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject_Start/KillerCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeKillerCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
MYPROJECT_START_API UClass* Z_Construct_UClass_AKillerCharacter();
MYPROJECT_START_API UClass* Z_Construct_UClass_AKillerCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject_Start();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AKillerCharacter Function MoveForward ************************************
struct Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics
{
	struct KillerCharacter_eventMoveForward_Parms
	{
		float AxisValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "KillerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function MoveForward constinit property declarations ***************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AxisValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function MoveForward constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function MoveForward Property Definitions **************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::NewProp_AxisValue = { "AxisValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KillerCharacter_eventMoveForward_Parms, AxisValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::NewProp_AxisValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::PropPointers) < 2048);
// ********** End Function MoveForward Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AKillerCharacter, nullptr, "MoveForward", 	Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::KillerCharacter_eventMoveForward_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::Function_MetaDataParams), Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::KillerCharacter_eventMoveForward_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AKillerCharacter_MoveForward()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AKillerCharacter_MoveForward_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AKillerCharacter::execMoveForward)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_AxisValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MoveForward(Z_Param_AxisValue);
	P_NATIVE_END;
}
// ********** End Class AKillerCharacter Function MoveForward **************************************

// ********** Begin Class AKillerCharacter Function MoveRight **************************************
struct Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics
{
	struct KillerCharacter_eventMoveRight_Parms
	{
		float AxisValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "KillerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function MoveRight constinit property declarations *****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AxisValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function MoveRight constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function MoveRight Property Definitions ****************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::NewProp_AxisValue = { "AxisValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KillerCharacter_eventMoveRight_Parms, AxisValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::NewProp_AxisValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::PropPointers) < 2048);
// ********** End Function MoveRight Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AKillerCharacter, nullptr, "MoveRight", 	Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::KillerCharacter_eventMoveRight_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::Function_MetaDataParams), Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::KillerCharacter_eventMoveRight_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AKillerCharacter_MoveRight()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AKillerCharacter_MoveRight_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AKillerCharacter::execMoveRight)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_AxisValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MoveRight(Z_Param_AxisValue);
	P_NATIVE_END;
}
// ********** End Class AKillerCharacter Function MoveRight ****************************************

// ********** Begin Class AKillerCharacter *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AKillerCharacter;
UClass* AKillerCharacter::GetPrivateStaticClass()
{
	using TClass = AKillerCharacter;
	if (!Z_Registration_Info_UClass_AKillerCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("KillerCharacter"),
			Z_Registration_Info_UClass_AKillerCharacter.InnerSingleton,
			StaticRegisterNativesAKillerCharacter,
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
	return Z_Registration_Info_UClass_AKillerCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_AKillerCharacter_NoRegister()
{
	return AKillerCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AKillerCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "KillerCharacter.h" },
		{ "ModuleRelativePath", "KillerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FPSCamerComponent_MetaData[] = {
		{ "Category", "KillerCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "KillerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FPSMesh_MetaData[] = {
		{ "Category", "Mesh" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "KillerCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AKillerCharacter constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FPSCamerComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FPSMesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AKillerCharacter constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("MoveForward"), .Pointer = &AKillerCharacter::execMoveForward },
		{ .NameUTF8 = UTF8TEXT("MoveRight"), .Pointer = &AKillerCharacter::execMoveRight },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AKillerCharacter_MoveForward, "MoveForward" }, // 1835947914
		{ &Z_Construct_UFunction_AKillerCharacter_MoveRight, "MoveRight" }, // 2319253993
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AKillerCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AKillerCharacter_Statics

// ********** Begin Class AKillerCharacter Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AKillerCharacter_Statics::NewProp_FPSCamerComponent = { "FPSCamerComponent", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AKillerCharacter, FPSCamerComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FPSCamerComponent_MetaData), NewProp_FPSCamerComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AKillerCharacter_Statics::NewProp_FPSMesh = { "FPSMesh", nullptr, (EPropertyFlags)0x00100000000b0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AKillerCharacter, FPSMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FPSMesh_MetaData), NewProp_FPSMesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AKillerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AKillerCharacter_Statics::NewProp_FPSCamerComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AKillerCharacter_Statics::NewProp_FPSMesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AKillerCharacter_Statics::PropPointers) < 2048);
// ********** End Class AKillerCharacter Property Definitions **************************************
UObject* (*const Z_Construct_UClass_AKillerCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject_Start,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AKillerCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AKillerCharacter_Statics::ClassParams = {
	&AKillerCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AKillerCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AKillerCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AKillerCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AKillerCharacter_Statics::Class_MetaDataParams)
};
void AKillerCharacter::StaticRegisterNativesAKillerCharacter()
{
	UClass* Class = AKillerCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AKillerCharacter_Statics::Funcs));
}
UClass* Z_Construct_UClass_AKillerCharacter()
{
	if (!Z_Registration_Info_UClass_AKillerCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AKillerCharacter.OuterSingleton, Z_Construct_UClass_AKillerCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AKillerCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AKillerCharacter);
AKillerCharacter::~AKillerCharacter() {}
// ********** End Class AKillerCharacter ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h__Script_MyProject_Start_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AKillerCharacter, AKillerCharacter::StaticClass, TEXT("AKillerCharacter"), &Z_Registration_Info_UClass_AKillerCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AKillerCharacter), 2153437748U) },
	};
}; // Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h__Script_MyProject_Start_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h__Script_MyProject_Start_3128184089{
	TEXT("/Script/MyProject_Start"),
	Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h__Script_MyProject_Start_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MyProject_Start_Source_MyProject_Start_KillerCharacter_h__Script_MyProject_Start_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
