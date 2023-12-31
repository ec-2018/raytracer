#pragma once

#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

#include "device_launch_parameters.h"

#include "../Raytracer.hpp"

#ifdef __INTELLISENSE__
template<class T>
void surf2Dwrite(T data, cudaSurfaceObject_t surfObj, int x, int y,
	cudaSurfaceBoundaryMode boundaryMode = cudaBoundaryModeTrap);
#endif

#define BLOCK_SIZE 8
#define MAXIMUM_AA 4

struct mat4
{
	float4 c0;
	float4 c1;
	float4 c2;
	float4 c3;
};

struct mat3
{
	float3 c0;
	float3 c1;
	float3 c2;
};

struct GPURayHit
{
	bool didHit;

	float distance;

	float4 hitPosition;
	float2 uv;
	mat3 tbnMatrix;

	GPUMaterial* material;
};

struct GPUMaterialPositionData
{
	float4 albedo;
	float4 normal;
	float3 ao;
	float roughness;
	float metal;
	float4 emission;
};

struct GPUTriangleHit
{
	float distance;
	float3 barycentricCoords;
};


struct GPURay
{
	float4	origin;
	float4	direction;
	int		bounceCount;
	float	maxDistance;
};

struct ObjectData
{
	mat4 modelMatrix;
	GPUMeshData* mesh;
	GPUMaterial* material;
};

struct ObjectDataVector
{
	ObjectData* data;
	int size;
};

struct CameraParams
{
	float4	origin;
	float4	rotation;
	float   exposure;
	int		width;
	int 	height;

	cudaTextureObject_t rays;
};

#define vec3transfer(a, b) \
	a.x = b.x; \
	a.y = b.y; \
	a.z = b.z;

#define vec4transfer(a, b) \
	a.x = b.x; \
	a.y = b.y; \
	a.z = b.z; \
	a.w = b.w;

#define mat4transfer(a, b) \
	vec4transfer(a.c0, b[0]); \
	vec4transfer(a.c1, b[1]); \
	vec4transfer(a.c2, b[2]); \
	vec4transfer(a.c3, b[3]);

class GPURaytracer : public Raytracer
{
public:
	void raytrace(std::shared_ptr<Scene> s, std::shared_ptr<Camera> c, cudaSurfaceObject_t o);

private:
	unsigned int frameCount = 0;
	unsigned int progressiveFrameCount = 0;
}; 

// GPU kernel forward declarations
__global__ void raytraceKernel(CameraParams camera, cudaSurfaceObject_t canvas, ObjectDataVector objectDataVector, const int bounceCount, const float maxDistance, const float aoIntensity, const int frameCount, const unsigned int progressiveFrameCount);

__device__ GPURay setupRay(const CameraParams& camera, const int x, const int y, const int bounceCount, const float maxDistance, unsigned int& seed);

__device__ float4 trace(GPURay& ray, const ObjectDataVector& objectDataVector, const float aoIntensity, unsigned int& seed);

__device__ GPURayHit getIntersectionPoint(const GPURay& ray, const ObjectDataVector& dataVector);

__device__ GPUMaterialPositionData getMaterialData(const GPURayHit& hit);

__device__ bool intersectsBoundingBox(const GPURay& ray, const float3& minBound, const float3& maxBound);

__device__ GPURayHit getIntersectionPoint(const GPURay& ray, const ObjectData& data);

__device__ GPUTriangleHit distToTriangle(const GPURay& ray, const float4& v0, const float4& v1, const float4& v2);

__device__ __forceinline__ float4 exposureCorrection(const float4 color, const float exposure);

// GPU math functions

__device__ __forceinline__ float4 normalize(const float4 v);

__device__ __forceinline__ float3 matVecMul(const mat3 m, const float3 v);

__device__ __forceinline__ float4 matVecMul(const mat4 m, const float4 v);

__device__ __forceinline__ float4 cross(const float4 a, const float4 b);

__device__ __forceinline__ float dot(const float4 a, const float4 b);

__device__ __forceinline__ float4 negate(const float4 v);

__device__ __forceinline__ float4 lerp(const float4 a, const float4 b, const float t);

__device__ __forceinline__ float4 normalize(const float4 v);

__device__ __forceinline__ float3 normalize(const float3 v);

// Credit https://forums.developer.nvidia.com/t/cuda-for-quaternions-hyper-complex-numbers-operations/44116/2
__device__ __forceinline__ float4 rotate(const float4 v, const float4 q); 

__device__ __forceinline__ float randomValue(unsigned int& seed);

__device__ __forceinline__ float randomValueNormalDistribution(unsigned int& seed);

__device__ __forceinline__ float4 randomUnitVector(unsigned int& seed);

__device__ __forceinline__ float4 randomUnitVectorInHemisphere(unsigned int& seed, const float4& normal);

__device__ __forceinline__ float4 randomUnitVectorInCosineHemisphere(unsigned int& seed, const float4& normal);

__device__ __forceinline__ float4 reflect(const float4& v, const float4& normal);





