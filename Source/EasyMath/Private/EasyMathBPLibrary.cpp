// Copyright Epic Games, Inc. All Rights Reserved.

#include "EasyMathBPLibrary.h"
#include "EasyMath.h"
#include "EasyMath/include/EasyMath.h"

UEasyMathBPLibrary::UEasyMathBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UEasyMathBPLibrary::EasyMathSampleFunction(float Param)
{
	return -1;
}

FVector UEasyMathBPLibrary::EasyMathTranslateFunction(AActor* actor , FVector VecIn, FVector Source)
{
	if (!actor)
	{
	    return FVector::ZeroVector; // 安全检查
	}
        
	auto matrix = EM::MTXTranslation(VecIn[0],VecIn[1],VecIn[2]);
	
	EM::Vector<double,4> o = EM::Vector<double,4>{Source[0], Source[1], Source[2], 1};

	EM::Matrix<double,4, 1> m = matrix * o;
	FVector NewLocation(m[0], m[1], m[2]);
	actor->SetActorLocation(NewLocation);

	return NewLocation;
}

FRotator UEasyMathBPLibrary::EasyMathRotateFunction(AActor* actor, FVector VecIn, FVector Source)
{
	if (!actor)
	{
		return FRotator::ZeroRotator; // 安全检查
	}

	FVector NewV = VecIn + Source;
	
	FRotator NewRotator(NewV[0], NewV[1], NewV[2]);
	
	actor->SetActorRotation(NewRotator);

	return NewRotator;
}

FVector UEasyMathBPLibrary::EasyMathScaleFunction(AActor* actor, FVector VecIn, FVector Source)
{
	if (!actor)
	{
		return FVector::ZeroVector; // 安全检查
	}

	auto matrix = EM::MTXScale(VecIn[0], VecIn[1], VecIn[2]);
	EM::Vector<double,4> o = EM::Vector<double,4>{Source[0], Source[1], Source[2], 1};

	EM::Matrix<double,4, 1> m = matrix * o;
	FVector NewScale(m[0], m[1], m[2]);
	actor->SetActorScale3D(NewScale);

	return NewScale;
}

