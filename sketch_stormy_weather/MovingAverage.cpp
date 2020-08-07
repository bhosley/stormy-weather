#include "MovingAverage.h"
#include <stdlib.h>
#include <math.h>

MovingAverage::MovingAverage() {}
MovingAverage::MovingAverage(float f) { init(f); }
MovingAverage::~MovingAverage() {}
void MovingAverage::init(float f) { currentValue = f; x++; }
float MovingAverage::getValue()
{
	return currentValue;
}
float MovingAverage::addValue(float f)
{
	return ++currentValue;
}

/*----------------------Random-Moving-Average----------------------*/

float RandomMovingAverage::addValue(float f)
{
	float a = rand() % 16;		// random(0, 15);
	float b = rand() % 16;		// random(0, 15);
	currentValue = currentValue + ((a-b)/15);
	return currentValue;
}

/*----------------------Simple-Moving-Average----------------------*/

SimpleMovingAverage::SimpleMovingAverage() {}
SimpleMovingAverage::SimpleMovingAverage(float f) { init(f); }
float SimpleMovingAverage::addValue(float f)
{
	x++;
	currentValue = currentValue + ((f - previousValue) / x);
	previousValue = currentValue;
	return currentValue;
}

/*--------------------Cumulative-Moving-Average--------------------*/

CumulativeMovingAverage::CumulativeMovingAverage() {}
CumulativeMovingAverage::CumulativeMovingAverage(float f) { init(f); }
float CumulativeMovingAverage::addValue(float f)
{
	// Arithmetic mean of accumulating values
	x++;
	//currentValue = ( f + (x - 1) * currentValue) / (x);
	currentValue = currentValue + ((f - currentValue) / (x));
	return currentValue;
}

/*---------------------Weighted-Moving-Average---------------------*/

WeightedMovingAverage::WeightedMovingAverage() {}
WeightedMovingAverage::WeightedMovingAverage(float f) { init(f); }
float WeightedMovingAverage::addValue(float f)
{
	// Arithmetic mean in which earlier values have higher weight
	currentValue = ((currentValue * (x+1)) + (f * x)) / ((2*x) + 1);
	x++;
	return currentValue;
}

/*-------------------Exponential-Moving-Average--------------------*/

ExponentialMovingAverage::ExponentialMovingAverage() {}
ExponentialMovingAverage::ExponentialMovingAverage(float f) { init(f); }
float ExponentialMovingAverage::addValue(float f)
{
	currentNumerator = currentNumerator + (f * pow( a,x ));
	currentDenominator = currentDenominator + pow( a,x );
	currentValue = currentNumerator / currentDenominator;
	x++;
	return currentValue;
}