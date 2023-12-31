#pragma once

#include<vector>
#include<memory>

#include <glm/glm.hpp>

#include "../Scene.hpp"
#include "../Camera.hpp"
#include "../Material.hpp"

#define BOUNCE_COUNT 3
#define MAX_DISTANCE 100.0f
#define AO_INTENSITY 0.01f

class Raytracer
{
public:
	inline void setBounceCount(int count) { bounceCount = count; }
	inline void setMaxDistance(float distance) { maxDistance = distance; }
	inline void setAOIntensity(float intensity) { aoIntensity = intensity; }
	inline void setProgressiveRendering(bool progressive) { progressiveRendering = progressive; }

	inline int getBounceCount() { return bounceCount; }
	inline float getMaxDistance() { return maxDistance; }
	inline float getAOIntensity() { return aoIntensity; }
	inline bool getProgressiveRendering() { return progressiveRendering; }
	

	enum class AntiAliasing
	{
		AA1x,
		AA4x,
		AA16x,
	};
	inline AntiAliasing getAntiAliasing() { return antiAliasing; }
	inline void setAntiAliasing(AntiAliasing aa) { antiAliasing = aa; }

protected:
	int bounceCount = BOUNCE_COUNT;
	float maxDistance = MAX_DISTANCE;

	float aoIntensity = AO_INTENSITY;

	bool progressiveRendering = false;

	AntiAliasing antiAliasing = AntiAliasing::AA1x;
};