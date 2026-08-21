#pragma once

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "shaders/Shader.h"
#include "scene/Camera.h"


class RealtimeGraphRenderable
{
    public:
        inline GLuint GetVbo() { return mVbo; }
        
        inline GLuint GetVao() {return mVao; }

        inline Shader* GetShader() { return mDefaultShader; }

        inline const glm::mat4& GetModel() { return mModel; }

        inline SDL_Rect GetViewport() { return mViewport; }


    protected:
        GLuint mVbo;
        GLuint mVao;

        Shader* mDefaultShader;

        // pointer to the global camera
        Camera* mCamera;

        SDL_Rect mViewport;

        glm::mat4 mModel;

};
