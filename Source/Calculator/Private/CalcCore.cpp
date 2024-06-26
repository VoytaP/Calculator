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

	if (IsOperator(S[0]))
	{
		if (CalcString.IsEmpty())
		{
			return false;
		}
		if (IsOperator(CalcString[CalcString.Len() - 1]))
		{
			return false;
		}
	}

	if (S[0] == TCHAR('B'))
	{
		if (CalcString.IsEmpty())
		{
			return false;
		}
		CalcString.RemoveAt(CalcString.Len() - 1);
		return true;
	}

	if (S[0] == TCHAR('C'))
	{
		CalcString.Reset();
		CalcResult.Reset();
		return true;
	}

	if (S[0] == TCHAR('='))
	{
		if (CalcString.IsEmpty())
		{
			return false;
		}
		return Evaluate();
	}

	CalcString.Append(S);
	return true;
}

bool ACalcCore::Evaluate()
{
	if (IsOperator(CalcString[CalcString.Len() - 1]))
	{
		CalcString.RemoveAt(CalcString.Len() - 1);
	}

	TArray<int32> NumArray;
	FString Operators;
	FString CurNumStr;
	for (auto& Ch : CalcString)
	{
		if (IsOperator(Ch))
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
			CurrNum *= NumArray[Index + 1];
		}
		else if (Operators[Index] == TCHAR('/'))
		{
			if (NumArray[Index + 1] == 0)
			{
				CalcResult = TEXT("division by 0");
				return true;
			}
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

bool ACalcCore::IsOperator(TCHAR Ch)
{
	return (Ch == TCHAR('+') || Ch == TCHAR('-') || Ch == TCHAR('*') || Ch == TCHAR('/'));
}

