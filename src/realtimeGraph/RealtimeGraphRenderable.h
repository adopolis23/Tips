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

        // Generate model needs to be called every time here becuase as data gets added the model
        // regens and moves the data into the bounds of the screen.
        inline const glm::mat4& GetModel() { GenerateModel(); return mModel; }

        inline SDL_Rect GetViewport() { return mViewport; }

        virtual void GenerateModel() = 0;


    protected:
        GLuint mVbo;
        GLuint mVao;

        Shader* mDefaultShader;

        // pointer to the global camera
        Camera* mCamera;

        SDL_Rect mViewport;

        glm::mat4 mModel;

};
