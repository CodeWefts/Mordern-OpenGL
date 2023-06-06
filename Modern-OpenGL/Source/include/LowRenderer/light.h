#pragma once

#include <iostream>
#include <string>
#include <vec3.h>
#include <shader.h>
#include <vector>

using namespace std;

enum Distance
{
    DIST_7,
    DIST_13,
    DIST_20,
    DIST_32,
    DIST_50,
    DIST_65,
    DIST_100,
    DIST_160,
    DIST_200,
    DIST_325,
    DIST_600
};

const int MAX_DIR_LIGHT = 10;
const int MAX_POINT_LIGHT = 100;
const int MAX_SPOT_LIGHT = 50;

struct DirLight
{
    Vector3 direction;

    Vector3 diffuse;
    Vector3 ambient;
    Vector3 specular;
};

struct PointLight
{
    Vector3 position;

    Vector3 diffuse;
    Vector3 ambient;
    Vector3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    Vector3 position;
    Vector3 direction;

    Vector3 diffuse;
    Vector3 ambient;
    Vector3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

const Vector3 DIR_DIRECTION = Vector3(-0.3f, -1.0f, -0.3f);
const Vector3 DIR_DIFFUSE = Vector3(0.4f, 0.4f, 0.4f);
const Vector3 DIR_AMBIENT = Vector3(0.05f, 0.05f, 0.05f);
const Vector3 DIR_SPECULAR = Vector3(0.5f, 0.5f, 0.5f);

const Vector3 POINT_POSITION = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 POINT_DIFFUSE = Vector3(0.8f, 0.8f, 0.8f);
const Vector3 POINT_AMBIENT = Vector3(0.05f, 0.05f, 0.05f);
const Vector3 POINT_SPECULAR = Vector3(1.0f, 1.0f, 1.0f);
const Distance POINT_ATTENUATION_RADIUS = DIST_50;

const Vector3 SPOT_POSITION = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 SPOT_DIRECTION = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 SPOT_DIFFUSE = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 SPOT_AMBIENT = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 SPOT_SPECULAR = Vector3(1.0f, 1.0f, 1.0f);
const float SPOT_INNER_CONE_ANGLE = 12.5f;
const float SPOT_OUTER_CONE_ANGLE = 15.0f;
const Distance SPOT_ATTENUATION_RADIUS = DIST_50;
class Light
{
private:
	Shader* m_lightShader = nullptr;
	Shader* m_lightCubeShader = nullptr;

public:

	
    vector<DirLight> dirLights;
    vector<PointLight> pointLights;
    vector<SpotLight> spotLights;

	void Init(Shader* lightShader, Shader* lightCubeShader);
    unsigned int CreatePointLight(const Vector3& position = POINT_POSITION, const Vector3& diffuse = POINT_DIFFUSE, const Vector3& ambient = POINT_AMBIENT, const Vector3& specular = POINT_SPECULAR, const Distance& attenuationRadius = POINT_ATTENUATION_RADIUS);
    unsigned int CreateSpotLight(const Vector3& position = SPOT_POSITION, const Vector3& direction = SPOT_DIRECTION, const Vector3& diffuse = SPOT_DIFFUSE, const Vector3& ambient = SPOT_AMBIENT, const Vector3& specular = SPOT_SPECULAR, const float& innerConeAngle = SPOT_INNER_CONE_ANGLE, const float& outerConeAngle = SPOT_OUTER_CONE_ANGLE, const Distance& attenuationRadius = SPOT_ATTENUATION_RADIUS);
    unsigned int CreateDirLight(const Vector3& direction = DIR_DIRECTION, const Vector3& diffuse = DIR_DIFFUSE, const Vector3& ambient = DIR_AMBIENT, const Vector3& specular = DIR_SPECULAR);
	
    float GetLinearFromDist(const Distance& attenuationRadius);
    float GetQuadraticFromDist(const Distance& attenuationRadius);
    void Update();

    Light();


};