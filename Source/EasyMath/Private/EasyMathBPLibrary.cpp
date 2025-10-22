// Copyright Epic Games, Inc. All Rights Reserved.

#include "EasyMath.h"
#include "EasyMathBPLibrary.h"
#include "EasyMath/EasyMath/include/EasyMath.h"

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

FVector UEasyMathBPLibrary::EasyMathRotateFunction(AActor* actor, FVector VecIn, FVector Source)
{
	if (!actor)
	{
		return FVector::ZeroVector; // 安全检查
	}

	auto mx = EM::MTXRotationX(VecIn[0]);
	auto my = EM::MTXRotationY(VecIn[1]);
	auto mz = EM::MTXRotationZ(VecIn[2]);

	auto mt = EM::MTXTranslation(Source[0],Source[1],Source[2]);

	auto m = mt * mx * my * mz * mt.inverse<>();

	FVector oo = actor->GetActorLocation();
	
	EM::Vector<double,4> o = EM::Vector<double,4>{oo[0], oo[1], oo[2], 1};
	
	EM::Matrix<double,4, 1> location = m * o;
	
	FVector NewLocation(location[0], location[1], location[2]);
	
	actor->SetActorLocation(NewLocation);
	
	return NewLocation;
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

