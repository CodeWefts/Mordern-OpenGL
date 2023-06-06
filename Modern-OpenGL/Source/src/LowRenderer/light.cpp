#include <light.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>




void Light::Init(Shader* lightShader, Shader* lightCubeShader)
{
	m_lightCubeShader = lightCubeShader;
	m_lightShader = lightShader;

}
float Light::GetLinearFromDist(const Distance& attenuationRadius)
{
    switch (attenuationRadius)
    {
    case DIST_7:
        return 0.7f;
    case DIST_13:
        return 0.35f;
    case DIST_20:
        return 0.22f;
    case DIST_32:
        return 0.14f;
    case DIST_50:
        return 0.09f;
    case DIST_65:
        return 0.07f;
    case DIST_100:
        return 0.045f;
    case DIST_160:
        return 0.027f;
    case DIST_200:
        return 0.022f;
    case DIST_325:
        return 0.014f;
    case DIST_600:
        return 0.07f;
    }
}

float Light::GetQuadraticFromDist(const Distance& attenuationRadius)
{
    switch (attenuationRadius)
    {
    case DIST_7:
        return 1.8f;
    case DIST_13:
        return 0.44f;
    case DIST_20:
        return 0.20f;
    case DIST_32:
        return 0.07f;
    case DIST_50:
        return 0.032f;
    case DIST_65:
        return 0.017f;
    case DIST_100:
        return 0.0075f;
    case DIST_160:
        return 0.0028f;
    case DIST_200:
        return 0.0019f;
    case DIST_325:
        return 0.0007f;
    case DIST_600:
        return 0.0002f;
    }
}

unsigned int Light::CreateDirLight(const Vector3& direction, const Vector3& diffuse, const Vector3& ambient, const Vector3& specular)
{

    if (dirLights.size() >= MAX_DIR_LIGHT)
    {
        return 0;
    }

    DirLight newDirLight;
    newDirLight.direction = direction;
    newDirLight.diffuse = diffuse;
    newDirLight.ambient = ambient;
    newDirLight.specular = specular;
    dirLights.push_back(newDirLight);


    unsigned int lightID = pointLights.size() - 1;
    return lightID;
}
unsigned int Light::CreatePointLight(const Vector3& position, const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Distance& attenuationRadius)
{

    if (pointLights.size() >= MAX_POINT_LIGHT)
    {
        return 0;
    }

    float linear = GetLinearFromDist(attenuationRadius);
    float quadratic = GetQuadraticFromDist(attenuationRadius);

    PointLight newPointLight;
    newPointLight.position = position;
    newPointLight.diffuse = diffuse;
    newPointLight.ambient = ambient;
    newPointLight.specular = specular;
    newPointLight.constant = 1.0f;
    newPointLight.linear = linear;
    newPointLight.quadratic = quadratic;
    pointLights.push_back(newPointLight);


    unsigned int lightID = pointLights.size() - 1;
    return lightID;
}
unsigned int Light::CreateSpotLight(const Vector3& position, const Vector3& direction, const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const float& innerConeAngle, const float& outerConeAngle, const Distance& attenuationRadius)
{

    if (spotLights.size() >= MAX_SPOT_LIGHT)
    {
        return 0;
    }

    float linear = GetLinearFromDist(attenuationRadius);
    float quadratic = GetQuadraticFromDist(attenuationRadius);
    float cutOff = cos(innerConeAngle);
    float outerCutOff = cos(outerConeAngle);

    SpotLight newPointLight;
    newPointLight.position = position;
    newPointLight.direction = direction;
    newPointLight.diffuse = diffuse;
    newPointLight.ambient = ambient;
    newPointLight.specular = specular;
    newPointLight.cutOff = cutOff;
    newPointLight.outerCutOff = outerCutOff;
    newPointLight.constant = 1.0f;
    newPointLight.linear = linear;
    newPointLight.quadratic = quadratic;
    spotLights.push_back(newPointLight);


    unsigned int lightID = spotLights.size() - 1;
    return lightID;
}

void Light::Update()
{
    m_lightShader->setInt("DirLightNr", dirLights.size());
    m_lightShader->setInt("PointLightNr", pointLights.size());
    m_lightShader->setInt("SpotLightNr", spotLights.size());

    // Update all directional lights
    // -----------------------------
    for (unsigned int i = 0; i < dirLights.size(); i++)
    {
        string number = to_string(i);
        m_lightShader->setVec3(("dirLights[" + number + "].direction").c_str(), dirLights[i].direction);
        m_lightShader->setVec3(("dirLights[" + number + "].diffuse").c_str(), dirLights[i].diffuse);
        m_lightShader->setVec3(("dirLights[" + number + "].ambient").c_str(), dirLights[i].ambient);
        m_lightShader->setVec3(("dirLights[" + number + "].specular").c_str(), dirLights[i].specular);
    }

    // Update all point lights
    // -----------------------
    for (unsigned int i = 0; i < pointLights.size(); i++)
    {
        string number = to_string(i);
        m_lightShader->setVec3(("pointLights[" + number + "].position").c_str(), pointLights[i].position);
        m_lightShader->setVec3(("pointLights[" + number + "].diffuse").c_str(), pointLights[i].diffuse);
        m_lightShader->setVec3(("pointLights[" + number + "].ambient").c_str(), pointLights[i].ambient);
        m_lightShader->setVec3(("pointLights[" + number + "].specular").c_str(), pointLights[i].specular);
        m_lightShader->setFloat(("pointLights[" + number + "].constant").c_str(), 1.0f);
        m_lightShader->setFloat(("pointLights[" + number + "].linear").c_str(), pointLights[i].linear);
        m_lightShader->setFloat(("pointLights[" + number + "].quadratic").c_str(), pointLights[i].quadratic);
    }
    // Update all spot lights
    // ----------------------
    for (unsigned int i = 0; i < spotLights.size(); i++)
    {
        string number = to_string(i);
        m_lightShader->setVec3(("spotLights[" + number + "].position").c_str(), spotLights[i].position);
        m_lightShader->setVec3(("spotLights[" + number + "].direction").c_str(), spotLights[i].direction);
        m_lightShader->setVec3(("spotLights[" + number + "].diffuse").c_str(), spotLights[i].diffuse);
        m_lightShader->setVec3(("spotLights[" + number + "].ambient").c_str(), spotLights[i].ambient);
        m_lightShader->setVec3(("spotLights[" + number + "].specular").c_str(), spotLights[i].specular);
        m_lightShader->setFloat(("spotLights[" + number + "].cutOff").c_str(), spotLights[i].cutOff);
        m_lightShader->setFloat(("spotLights[" + number + "].outerCutOff").c_str(), spotLights[i].outerCutOff);
        m_lightShader->setFloat(("spotLights[" + number + "].constant").c_str(), 1.0f);
        m_lightShader->setFloat(("spotLights[" + number + "].linear").c_str(), spotLights[i].linear);
        m_lightShader->setFloat(("spotLights[" + number + "].quadratic").c_str(), spotLights[i].quadratic);
    }
}

Light::Light()
{

}