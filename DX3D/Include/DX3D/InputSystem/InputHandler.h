#pragma once
#include "DX3D/InputSystem/InputSystem.h"
#include <iostream>

namespace dx3d
{
    class InputHandler : public InputListener
    {
    public:
        InputHandler()
        {
            dx3d::InputSystem::get()->addListener(this);
        }

        ~InputHandler()
        {
            dx3d::InputSystem::get()->removeListener(this);
        }

        void onKeyDown(int key) override
        {
            std::cout << "Key Down: " << key << std::endl;
        }

        void onKeyUp(int key) override
        {
            std::cout << "Key Up: " << key << std::endl;
        }
    };
}
