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

#define PI 3.141592f

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
	
	inline int getSampleCount() { return sampleCount; }
	inline void setSampleCount(int count) { sampleCount = count; }

	inline void setAntiAliasingEnabled(bool enabled) { antiAliasingEnabled = enabled; }
	inline bool getAntiAliasingEnabled() { return antiAliasingEnabled; }

	inline void setSkyLight(float pitch, float yaw, float4 light, float4 sky) 
	{ 
		lightColor = light;
		skyColor = sky;
		lightDirection = make_float4(cos(pitch) * cos(yaw), sin(pitch), cos(pitch) * sin(yaw), 0.0f);
	}

	

protected:
	int bounceCount = BOUNCE_COUNT;
	float maxDistance = MAX_DISTANCE;
	unsigned int frameCount = 0;
	unsigned int progressiveFrameCount = 0;

	float aoIntensity = AO_INTENSITY;

	bool progressiveRendering = false;

	bool antiAliasingEnabled = true;

	unsigned int sampleCount = 1;

	float4 lightDirection;
	float4 lightColor;
	float4 skyColor;
};