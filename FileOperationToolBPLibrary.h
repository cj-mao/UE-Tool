// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileOperationToolBPLibrary.generated.h"

UCLASS()
class FILEOPERATIONTOOL_API UFileOperationToolBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	/**
	 * 添加换行符
	 * @param FileContent 
	 * @param NewContent 
	 */
	static void FileContentWrap(const FString& FileContent, FString& NewContent);
	/**
	 * @description:从文件中读取
	 * @param FilePath 文件在工程下目录路径
	 * @param FileName 文件名
	 * @param Result 文件内容
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static void ReadFromFile(const FString& FilePath, const FString& FileName, FString& Result);

	/**
	 * @description:从文件中读取
	 * @param Path 文件路径
	 * @param Result 文件内容
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static void ReadFromFileByPath(const FString& Path, FString& Result);

	/**
	 * @description:将内容写入文件
	 * @param FilePath 文件在工程下目录路径
	 * @param FileName 文件名
	 * @param FileContent 写入的文件内容
	 * @return  是否写入成功
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static bool WriteToFile(const FString& FilePath, const FString& FileName, const FString& FileContent);

	/**
	 * @description:将内容写入文件
	 * @param Path 文件路径
	 * @param FileContent 写入的文件内容
	 * @return 是否写入成功
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static bool WriteToFileByPath(const FString& Path, const FString& FileContent);

	/**
	 * @description:将内容添加进文件
	 * @param FilePath 文件在工程下目录路径
	 * @param FileName 文件名
	 * @param AddFileContent 需要增加的内容
	 * @return 是否增加成功
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static bool AddToFile(const FString& FilePath, const FString& FileName, const FString& AddFileContent);

	/**
	 * @description:
	 * @param Path 文件路径
	 * @param AddFileContent 需要增加的内容
	 * @return 是否增加成功
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static bool AddToFileByPath(const FString& Path, const FString& AddFileContent);

	/**
	 * @description:查找文件或文件夹
	 * @param FilePath 开始查找的文件在工程下目录路径
	 * @param Filter 文件名
	 * @param Files 文件
	 * @param Directory 文件夹
	 * @param Result 查找到的所有路径
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static void FindFiles(FString FilePath, FString Filter, bool Files, bool Directory, TArray<FString>& Result);

	/**
	 * @description:查找文件或文件夹
	 * @param FilePath 开始查找的文件目录路径
	 * @param Filter 文件名
	 * @param Files 文件
	 * @param Directory 文件夹
	 * @param Result 查找到的所有路径
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static void FindFilesByPath(const FString& FilePath, const FString& Filter, bool Files, bool Directory,
	                            TArray<FString>& Result);

	/**
	 * @description:删除文件
	 * @param FilePath 文件在工程下目录路径
	 * @param FileName 文件名
	 * @return 是否删除成功
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static bool DeleteFile(FString FilePath, FString FileName);

	/**
	 * @description:删除文件
	 * @param Path 文件路径
	 * @return 是否删除成功
	 */
	UFUNCTION(BlueprintCallable, Category = "FileOperationTool")
	static bool DeleteFileByPath(FString Path);

	/**
	 * @description:文件是否存在
	 * @param FilePath 文件在工程下目录路径
	 * @param FileName 文件名
	 * @return 文件是否存在
	 */
	UFUNCTION(BlueprintPure, Category = "FileOperationTool")
	static bool FileExists(const FString& FilePath, const FString& FileName);

	/**
	 * @description:文件是否存在
	 * @param Path 文件路径
	 * @return 文件是否存在
	 */
	UFUNCTION(BlueprintPure, Category = "FileOperationTool")
	static bool FileExistsByPath(const FString& Path);

	/**
	 * @description:拷贝文件
	 * @param FilePath 需要拷贝的文件在工程下目录路径
	 * @param FileName 需要拷贝的文件名
	 * @param TargetFilePath 目标工程下目录路径
	 * @param TargetFileName 目标文件名
	 */
	UFUNCTION(BlueprintCallable,Category="FileOperationTool")
	static void CopyFileToTargetPath(const FString&FilePath,const FString&FileName,const FString& TargetFilePath,const FString& TargetFileName);

	/**
	 * @description:拷贝文件
	 * @param CopyPath 需要拷贝的文件路径
	 * @param TargetPath 目标路径
	 */
	UFUNCTION(BlueprintCallable,Category="FileOperationTool")
	static void CopyFileToTargetPathByPath(const FString& CopyPath,const FString& TargetPath);

	/**
	 * @description:移动文件
	 * @param FilePath 需要移动的文件在工程下目录路径
	 * @param FileName 需要移动的文件名
	 * @param TargetFilePath 目标工程下目录路径
	 * @param TargetFileName 目标文件名
	 */
	UFUNCTION(BlueprintCallable,Category="FileOperationTool")
	static void MoveFileToTargetPath(const FString&FilePath,const FString&FileName,const FString& TargetFilePath,const FString& TargetFileName);

	/**
	 * @description:移动文件
	 * @param MovePath 需要移动的文件路径
	 * @param TargetPath 目标路径
	 */
	UFUNCTION(BlueprintCallable,Category="FileOperationTool")
	static void MoveFileToTargetPathByPath(const FString& MovePath,const FString& TargetPath);
	
	/**
	 * @description:拷贝文件夹
	 * @param DirectoryPath 拷贝的文件夹在工程下目录路径
	 * @param TargetDirectoryPath 目标文件夹在工程下目录路径
	 */
	UFUNCTION(BlueprintCallable,Category="FileOperationTool")
	static void CopyDirectory(const FString& DirectoryPath,const FString& TargetDirectoryPath);

	/**
	 * @description:拷贝文件夹
	 * @param CopyPath 拷贝文件夹路径
	 * @param TargetPath 目标文件夹路径
	 */
	UFUNCTION(BlueprintCallable,Category="FileOperationTool")
	static void CopyDirectoryByPath(const FString& CopyPath,const FString& TargetPath);
	
	/**
	 * @description:AES加密
	 * @param InputString 需要加密的字符串
	 * @param Key 加密钥匙
	 * @return 加密后的字符串
	 */
	UFUNCTION(BlueprintPure, Category = "FileOperationTool")
	static FString Encrypt(FString InputString, FString Key = "key");

	/**
	 * @description:AES解密
	 * @param InputString 需要解密的字符串
	 * @param Key 加密钥匙
	 * @return 解密后的字符串
	 */
	UFUNCTION(BlueprintPure, Category = "FileOperationTool")
	static FString Decrypt(FString InputString, FString Key = "key");

};
