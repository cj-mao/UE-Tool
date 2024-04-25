// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FileOperationToolBPLibrary.h"
#include "JsonObjectConverter.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonDataLibrary.generated.h"

/**
 * json数据处理函数库
 */
UCLASS()
class DATANG_API UJsonDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	//从文件中读取Json数据并转换成结构体模版函数
	template <typename T>
	static void LoadJsonForStruct(T& Struct, const FString& SavePath)
	{
		FString Json;
		UFileOperationToolBPLibrary::ReadFromFileByPath(SavePath, Json);
		FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Struct, 0, 0);
	}

	//将结构体数据转换成json数据并写入文件中
	template <typename T>
	static void SaveJsonFormStruct(const T& Struct, const FString& SavePath)
	{
		FString Json;
		FJsonObjectConverter::UStructToJsonObjectString(Struct, Json);
		UFileOperationToolBPLibrary::WriteToFileByPath(SavePath, Json);
	}

	UFUNCTION(BlueprintCallable)
	static void SaveObjectToJson(UObject* SaveObject,const FString& SavePath);
	UFUNCTION(BlueprintCallable)
	static bool LoadFromJson(UObject* LoadObject, const FString& Path);

	static  bool UStructToJsonObject(const UStruct* StructDefinition, const void* Struct, TSharedRef<FJsonObject> OutJsonObject, int64 CheckFlags = 0, int64 SkipFlags = 0);

	static bool UStructToJsonAttributes(const UStruct* StructDefinition, const void* Struct, TMap< FString, TSharedPtr<FJsonValue> >& OutJsonAttributes, int64 CheckFlags = 0, int64 SkipFlags = 0);
	static  TSharedPtr<FJsonValue> UPropertyToJsonValue(FProperty* Property, const void* Value, int64 CheckFlags = 0, int64 SkipFlags = 0, FProperty* OuterProperty = nullptr);

	static bool JsonObjectToUStruct(const TSharedRef<FJsonObject>& JsonObject, const UStruct* StructDefinition, void* OutStruct, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr);
	static  bool JsonAttributesToUStruct(const TMap< FString, TSharedPtr<FJsonValue> >& JsonAttributes, const UStruct* StructDefinition, void* OutStruct, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr);

	static  TSharedPtr<FJsonValue> ConvertScalarFPropertyToJsonValue(FProperty* Property, const void* Value, int64 CheckFlags, int64 SkipFlags, FProperty* OuterProperty);
	static bool ConvertScalarJsonValueToFPropertyWithContainer(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags, const bool bStrictMode, FText* OutFailReason);
	static bool JsonValueToFPropertyWithContainer(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags, const bool bStrictMode, FText* OutFailReason);
	static bool JsonAttributesToUStructWithContainer(const TMap< FString, TSharedPtr<FJsonValue> >& JsonAttributes, const UStruct* StructDefinition, void* OutStruct, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags, const bool bStrictMode, FText* OutFailReason);
};
