#pragma once
class MovingAverage
{
public:
	MovingAverage();
	MovingAverage(float f);
	~MovingAverage();
	float getValue();
	virtual float addValue(float f);
protected:
	int x = 0;
	void init(float f);
	float currentValue = 0;
private:
};

class RandomMovingAverage : public MovingAverage
{
public:
	float addValue(float f) override;
private:
};
class SimpleMovingAverage : public MovingAverage 
{
public:
	SimpleMovingAverage();
	SimpleMovingAverage(float f);
	float addValue(float f) override;
private:
	float previousValue = 0.0f;
};
class CumulativeMovingAverage : public MovingAverage
{
public:
	CumulativeMovingAverage();
	CumulativeMovingAverage(float f);
	float addValue(float f) override;
private:
};
class WeightedMovingAverage : public MovingAverage
{
public:
	WeightedMovingAverage();
	WeightedMovingAverage(float f);
	float addValue(float f) override;
private:
};
class ExponentialMovingAverage : public MovingAverage
{
public:
	ExponentialMovingAverage();
	ExponentialMovingAverage(float f);
	float addValue(float f) override;
	float a = 0.9f;
private:
	float currentDenominator = 0.0f;
	float currentNumerator = 0.0f;
};