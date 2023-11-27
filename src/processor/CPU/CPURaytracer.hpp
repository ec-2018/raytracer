#pragma once

#include "../raytracer.hpp"

class CPURaytracer : public Raytracer
{
public:
	std::vector<float> trace(Scene& s, const std::vector<glm::vec3>& rayDirections, const glm::vec3& origin);
private:
	Color singleTrace(Ray& ray, const std::vector<DisplayObject*>& objects);

	bool intersectsBoundingBox(const Ray& ray, const glm::vec3& minBound, const glm::vec3& maxBound);

	void getIntersectionPoint(Ray& ray, DisplayObject* object);

	float distToTriangle(const Ray& ray, glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& barycentricCoords);

	float randomValue(unsigned int& seed);

	float randomValueNormalDistribution(unsigned int& seed);
};