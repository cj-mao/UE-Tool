// Copyright Epic Games, Inc. All Rights Reserved.

#include "FileOperationToolBPLibrary.h"
#include "FileOperationToolSettings.h"
#include "HAL/FileManagerGeneric.h"

UFileOperationToolBPLibrary::UFileOperationToolBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UFileOperationToolBPLibrary::FileContentWrap(const FString& FileContent, FString& NewContent)
{
	NewContent = FString::Printf(TEXT("%s\n"), *FileContent);
}

void UFileOperationToolBPLibrary::ReadFromFile(const FString& FilePath, const FString& FileName, FString& Result)
{
	const FString Path = FPaths::ProjectDir() + FilePath + "/" + FileName;
	ReadFromFileByPath(Path, Result);
}

void UFileOperationToolBPLibrary::ReadFromFileByPath(const FString& Path, FString& Result)
{
	FFileHelper::LoadFileToString(Result, *Path);
}

bool UFileOperationToolBPLibrary::WriteToFile(const FString& FilePath, const FString& FileName, const FString& FileContent)
{
	const FString Path = FPaths::ProjectDir() + FilePath + "/" + FileName;
	return WriteToFileByPath(Path, FileContent);
}

bool UFileOperationToolBPLibrary::WriteToFileByPath(const FString& Path, const FString& FileContent)
{
	// const FString NewContent = FString::Printf(TEXT("%s\n"), *FileContent);
	return FFileHelper::SaveStringToFile(FileContent,
	                                     *Path,
	                                     FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM,
	                                     &IFileManager::Get(),
	                                     FILEWRITE_None);
}

bool UFileOperationToolBPLibrary::AddToFile(const FString& FilePath, const FString& FileName, const FString& AddFileContent)
{
	const FString Path = FPaths::ProjectDir() + FilePath + "/" + FileName;
	return AddToFileByPath(Path, AddFileContent);
}

bool UFileOperationToolBPLibrary::AddToFileByPath(const FString& Path, const FString& AddFileContent)
{
	const FString NewContent = FString::Printf(TEXT("%s\n"), *AddFileContent);
	return FFileHelper::SaveStringToFile(NewContent,
	                                     *Path,
	                                     FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM,
	                                     &IFileManager::Get(),
	                                     FILEWRITE_Append);
}

void UFileOperationToolBPLibrary::FindFiles(const FString FilePath, const FString Filter, bool Files, bool Directory, TArray<FString>& Result)
{
	const FString Path = FPaths::ProjectDir() + FilePath;
	Result.Empty();
	FFileManagerGeneric::Get().FindFilesRecursive(Result, *Path, *Filter, Files, Directory);
}

void UFileOperationToolBPLibrary::FindFilesByPath(const FString& FilePath, const FString& Filter, bool Files, bool Directory, TArray<FString>& Result)
{
	Result.Empty();
	FFileManagerGeneric::Get().FindFilesRecursive(Result, *FilePath, *Filter, Files, Directory);
}

bool UFileOperationToolBPLibrary::DeleteFile(FString FilePath, FString FileName)
{
	const FString Path = FPaths::ProjectDir() + FilePath + "/" + FileName;
	return DeleteFileByPath(Path);
}

bool UFileOperationToolBPLibrary::DeleteFileByPath(FString Path)
{
	return IFileManager::Get().Delete(*Path);
}

bool UFileOperationToolBPLibrary::FileExists(const FString& FilePath, const FString& FileName)
{
	const FString Path = FPaths::ProjectDir() + FilePath + "/" + FileName;
	return FileExistsByPath(Path);
}

bool UFileOperationToolBPLibrary::FileExistsByPath(const FString& Path)
{
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*Path);
}

void UFileOperationToolBPLibrary::CopyFileToTargetPath(const FString& FilePath, const FString& FileName, const FString& TargetFilePath, const FString& TargetFileName)
{
	const FString CopyPath = FPaths::ProjectDir() + FilePath + "/" + FileName;
	const FString TargetPath = FPaths::ProjectDir() + TargetFilePath + "/" + TargetFileName;
	CopyFileToTargetPathByPath(CopyPath, TargetPath);
}

void UFileOperationToolBPLibrary::CopyFileToTargetPathByPath(const FString& CopyPath, const FString& TargetPath)
{
	IFileManager::Get().Copy(*TargetPath, *CopyPath);
}

void UFileOperationToolBPLibrary::MoveFileToTargetPath(const FString& FilePath, const FString& FileName, const FString& TargetFilePath, const FString& TargetFileName)
{
	const FString MovePath = FPaths::ProjectDir() + FilePath + "/" + FileName;
	const FString TargetPath = FPaths::ProjectDir() + TargetFilePath + "/" + TargetFileName;
	MoveFileToTargetPathByPath(MovePath, TargetPath);
}

void UFileOperationToolBPLibrary::MoveFileToTargetPathByPath(const FString& MovePath, const FString& TargetPath)
{
	IFileManager::Get().Move(*TargetPath, *MovePath);
}

void UFileOperationToolBPLibrary::CopyDirectory(const FString& DirectoryPath, const FString& TargetDirectoryPath)
{
	const FString Path = FPaths::ProjectDir() + DirectoryPath;
	const FString TargetPath = FPaths::ProjectDir() + TargetDirectoryPath;
	CopyDirectoryByPath(Path, TargetPath);
}

void UFileOperationToolBPLibrary::CopyDirectoryByPath(const FString& CopyPath, const FString& TargetPath)
{
	FPlatformFileManager::Get().GetPlatformFile().CopyDirectoryTree(*TargetPath, *CopyPath, true);
}

FString UFileOperationToolBPLibrary::Encrypt(FString InputString, FString Key)
{
	if (InputString.IsEmpty()) return "";
	if (Key.IsEmpty()) return "";
	FString SignStartStr = "=-StartCheck-=";
	FString SignEndStr = "=-EndCheck-=";
	InputString = SignStartStr + InputString;
	InputString.Append(SignEndStr);
	TArray<uint8> Content;
	std::string _s(TCHAR_TO_UTF8(*InputString));
	Content.Append((unsigned char*)_s.data(), _s.size());
	InputString = FBase64::Encode(Content);

	FString SplitSymbol = "somethingSpecialSignal";
	InputString.Append(SplitSymbol);

	Key = FMD5::HashAnsiString(*Key);
	TCHAR* KeyTChar = Key.GetCharArray().GetData();
	ANSICHAR* KeyAnsi = (ANSICHAR*)TCHAR_TO_ANSI(KeyTChar);

	uint8* Blob;
	uint32 Size;

	Size = InputString.Len();
	Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));

	Blob = new uint8[Size];

	if (StringToBytes(InputString, Blob, Size))
	{
		FAES::EncryptData(Blob, Size, KeyAnsi);
		InputString = FString::FromHexBlob(Blob, Size);
		delete Blob;
		return InputString;
	}
	delete Blob;
	return "";
}

FString UFileOperationToolBPLibrary::Decrypt(FString InputString, FString Key)
{
	if (InputString.IsEmpty()) return "";
	if (Key.IsEmpty()) return "";

	FString SplitSymbol = "somethingSpecialSignal";

	Key = FMD5::HashAnsiString(*Key);
	TCHAR* KeyTChar = Key.GetCharArray().GetData();
	ANSICHAR* KeyAnsi = (ANSICHAR*)TCHAR_TO_ANSI(KeyTChar);

	uint8* Blob;
	uint32 Size;
	Size = InputString.Len();
	Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));
	Blob = new uint8[Size];

	if (FString::ToHexBlob(InputString, Blob, Size))
	{
		FAES::DecryptData(Blob, Size, KeyAnsi);
		InputString = BytesToString(Blob, Size);

		FString LeftData;
		FString RightData;
		InputString.Split(SplitSymbol, &LeftData, &RightData, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		InputString = LeftData;

		TArray<uint8> Content;
		FBase64::Decode(InputString, Content);
		InputString = FString(UTF8_TO_TCHAR(Content.GetData()));

		FString SignStartStr = "=-StartCheck-=";
		FString SignEndStr = "=-EndCheck-=";

		InputString.Split(SignStartStr, &LeftData, &RightData, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		InputString = RightData;
		InputString.Split(SignEndStr, &LeftData, &RightData, ESearchCase::CaseSensitive, ESearchDir::FromStart);

		delete Blob;
		return LeftData;
	}
	delete Blob;
	return "";
}



