#include "PBLightRenderer.h"

#include <sstream>

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
    constexpr auto projectionMatrixLabel = "projection";
    constexpr auto modelMatrixLabel = "model";
    constexpr auto viewMatrixLabel = "view";

    constexpr auto positionLabel = "aPos";
    constexpr auto normalLabel = "aNormal";

    constexpr auto albedoLabel = "albedo";
    constexpr auto metaricLabel = "metallic";
    constexpr auto roughbessLabel = "roughness";
    constexpr auto aoLabel = "ao";

    constexpr auto camerPosLabel = "camPos";

    // lights
    //uniform vec3 lightPositions[4];
    //uniform vec3 lightColors[4];

    struct UniformLoc
    {
        GLuint projectionMatrix;
        GLuint modelMatrix;
        GLuint viewMatrix;
        GLuint albedo;
        GLuint metaric;
        GLuint roughness;
        GLuint ao;
        GLuint lightPos;
        GLuint lightColor;
        GLuint eyePos;
    };
    UniformLoc uniforms;

    struct AttrLoc
    {
        GLuint position;
        GLuint normal;
    };
    AttrLoc attrs;
}

PBLightRenderer::PBLightRenderer()
{
}

void PBLightRenderer::link()
{
    uniforms.projectionMatrix = shader->findUniformLocation(::projectionMatrixLabel);
    uniforms.modelMatrix = shader->findUniformLocation(::modelMatrixLabel);
    uniforms.viewMatrix = shader->findUniformLocation(::viewMatrixLabel);

    uniforms.albedo = shader->findUniformLocation(::albedoLabel);
    uniforms.metaric = shader->findUniformLocation(::metaricLabel);
    uniforms.roughness = shader->findUniformLocation(::roughbessLabel);
    uniforms.ao = shader->findUniformLocation(::aoLabel);

    uniforms.eyePos = shader->findUniformLocation(::camerPosLabel);

    for (int i = 0; i < 1; ++i) {
        uniforms.lightPos = shader->findUniformLocation("lightPositions[" + std::to_string(i) + "]");
        uniforms.lightColor = shader->findUniformLocation("lightColors[" + std::to_string(i) + "]");
    }

    attrs.position = shader->findAttribLocation(::positionLabel);
    attrs.normal = shader->findAttribLocation(::normalLabel);
}

void PBLightRenderer::render()
{
    shader->bind();
    shader->bindOutput("FragColor");

    shader->enable(GL_DEPTH_TEST);

    Uniform projectionMatrix(uniforms.projectionMatrix);
    Uniform modelMatrix(uniforms.modelMatrix);
    Uniform viewMatrix(uniforms.viewMatrix);
    Uniform cameraPos(uniforms.eyePos);

    //shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
    projectionMatrix.send(buffer.projectionMatrix);
    modelMatrix.send(buffer.modelMatrix);
    viewMatrix.send(buffer.viewMatrix);
    cameraPos.send(buffer.eyePosition);

    Uniform albedo(uniforms.albedo);
    Uniform metalic(uniforms.metaric);
    Uniform roughness(uniforms.roughness);
    Uniform ao(uniforms.ao);
    
    albedo.send(buffer.albedo);
    metalic.send(buffer.metalic);
    roughness.send(buffer.roughness);
    ao.send(buffer.ao);

    Uniform lightPos(uniforms.lightPos);
    Uniform lightColor(uniforms.lightColor);

    lightPos.send(buffer.lightPosition);
    lightColor.send(buffer.lightColor);

    VertexAttribute posAttr(attrs.position);
    VertexAttribute normalAttr(attrs.normal);

    posAttr.sendVertexAttribute3df(*buffer.position);
    normalAttr.sendVertexAttribute3df(*buffer.normal);

    shader->drawTriangles(buffer.indices);

    shader->disable(GL_DEPTH_TEST);

    shader->unbind();
}