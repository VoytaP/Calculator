// Fill out your copyright notice in the Description page of Project Settings.


#include "CalcCore.h"

// Sets default values
ACalcCore::ACalcCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CalcString = TEXT("");
	CalcResult = TEXT("");
}

// Called when the game starts or when spawned
void ACalcCore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACalcCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACalcCore::InputString(FString S)
{
	if (S.IsEmpty())
	{
		return false;
	}

	if (S[0] == TCHAR('+') || S[0] == TCHAR('-') || S[0] == TCHAR('*') || S[0] == TCHAR('/') || S[0] == TCHAR('0'))
	{
		if (CalcString.IsEmpty())
		{
			return false;
		}
		TCHAR LastCh = CalcString[CalcString.Len() - 1];
		if (LastCh == TCHAR('+') || LastCh == TCHAR('-') || LastCh == TCHAR('*') || LastCh == TCHAR('/'))
		{
			return false;
		}
	}

	if (S[0] == TCHAR('B'))
	{
		CalcString.RemoveAt(CalcString.Len() - 1);
		return true;
	}

	if (S[0] == TCHAR('C'))
	{
		CalcString.Reset();
		return true;
	}

	if (S[0] == TCHAR('='))
	{
		return Evaluate();
	}

	CalcString.Append(S);
	return true;
}

bool ACalcCore::Evaluate()
{
	TArray<int32> NumArray;
	FString Operators;
	FString CurNumStr;
	for (auto& Ch : CalcString)
	{
		if (Ch == TCHAR('+') || Ch == TCHAR('-') || Ch == TCHAR('*') || Ch == TCHAR('/'))
		{
			NumArray.Add(FCString::Atoi(*CurNumStr));
			CurNumStr.Reset();
			Operators.AppendChar(Ch);
		}
		else
		{
			CurNumStr += Ch;
		}
	}
	NumArray.Add(FCString::Atoi(*CurNumStr));

	// times, divide
	TArray<int32> NumArrayAfterM;
	FString OperatorsAfterM;
	auto ItNum = NumArray.CreateConstIterator();
	int32 CurrNum = NumArray[0];
	for (int32 Index = 0; Index != Operators.Len(); ++Index)
	{
		if (Operators[Index] == TCHAR('*'))
		{
			CurrNum *= NumArray[Index+1];
		}
		if (Operators[Index] == TCHAR('/'))
		{
			CurrNum /= NumArray[Index + 1];
		}
		else
		{
			NumArrayAfterM.Add(CurrNum);
			CurrNum = NumArray[Index+1];
			OperatorsAfterM.AppendChar(Operators[Index]);
		}
	}
	NumArrayAfterM.Add(CurrNum);

	// plus, minus
	int32 FinalNum = NumArrayAfterM[0];
	for (int32 Index = 0; Index != OperatorsAfterM.Len(); ++Index)
	{
		if (OperatorsAfterM[Index] == TCHAR('+'))
		{
			FinalNum += NumArrayAfterM[Index + 1];
		}
		if (OperatorsAfterM[Index] == TCHAR('-'))
		{
			FinalNum -= NumArrayAfterM[Index + 1];
		}
	}

	CalcResult = FString::FromInt(FinalNum);
	return true;
}

