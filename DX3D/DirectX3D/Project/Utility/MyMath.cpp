#include "Framework.h"
#include "MyMath.h"

float MyMath::Clamp(const float& value, float minValue, float maxValue)
{
	return max(minValue, min(maxValue, value));
}

float MyMath::Saturate(const float& value)
{
	return Clamp(value, 0.0f, 1.0f);
}

float MyMath::Max(const float& value1, const float& value2, const float& value3)
{
	return max(max(value1, value2), value3);
}

float MyMath::Min(const float& value1, const float& value2, const float& value3)
{
	return min(min(value1, value2), value3);
}

float MyMath::Distance(Vector3 v1, Vector3 v2)
{
	return (v2 - v1).Length();
}

float MyMath::Random(const float& min, const float& max)
{
	float normal = ((float)rand() / RAND_MAX);

	return min + (max - min) * normal;
}

int MyMath::Random(const int& min, const int& max)
{
	return min + rand() % (max - min); // max Exclusive
	//return min + rand() % (max - min + 1); // max Inclusive
}

Vector3 MyMath::ClosestPointOnLine(Vector3 start, Vector3 end, Vector3 point)
{
	Vector3 line = end - start;

	float t = Vector3::Dot(line, point - start) / Vector3::Dot(line, line);
	t = Saturate(t);

	return start + line * t;
}
