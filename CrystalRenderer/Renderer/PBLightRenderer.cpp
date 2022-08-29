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
        GLuint modelviewMatrix;
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
    uniforms.modelviewMatrix = shader->findUniformLocation(::modelMatrixLabel);
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
    /*
    shader->bind();
    shader->bindOutput("FragColor");

    shader->enable(GL_DEPTH_TEST);

    shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
    shader->sendUniform(::modelMatrixLabel, buffer.modelMatrix);
    shader->sendUniform(::viewMatrixLabel, buffer.viewMatrix);
    shader->sendUniform(::camerPosLabel, buffer.eyePosition);

    shader->sendUniform(::albedoLabel, buffer.albedo);
    shader->sendUniform(::metaricLabel, buffer.metalic);
    shader->sendUniform(::roughbessLabel, buffer.roughness);
    shader->sendUniform(::aoLabel, buffer.ao);

    shader->sendUniform("lightPositions[0]", buffer.lightPosition);
    shader->sendUniform("lightColors[0]", buffer.lightColor);

    shader->sendVertexAttribute3df(::positionLabel, buffer.position);
    shader->sendVertexAttribute3df(::normalLabel, buffer.normal);

    buffer.position.bind();
    buffer.normal.bind();
    shader->enableVertexAttribute(::positionLabel);
    shader->enableVertexAttribute(::normalLabel);

    shader->drawTriangles(buffer.indices);

    shader->disableVertexAttribute(::positionLabel);
    shader->disableVertexAttribute(::normalLabel);

    shader->disable(GL_DEPTH_TEST);

    shader->unbind();
    */
}