#include "DX3D/InputSystem/InputSystem.h"
#include <Windows.h>

dx3d::InputSystem::InputSystem()
{
}

dx3d::InputSystem::~InputSystem()
{
}

void dx3d::InputSystem::update()
{
    static bool initialized = false;

    if (::GetKeyboardState(m_keys_state))
    {
        
        if (!initialized)
        {
            ::memcpy(m_old_keys_state, m_keys_state, sizeof(m_keys_state));
            initialized = true;
            return;
        }

        for (unsigned int i = 0; i < 256; i++)
        {
            bool isDown = (m_keys_state[i] & 0x80) != 0;
            bool wasDown = (m_old_keys_state[i] & 0x80) != 0;

            if (isDown && !wasDown) // Key just pressed
            {
                for (auto& pair : m_map_listeners)
                {
                    pair.second->onKeyDown(i);
                }
            }
            else if (!isDown && wasDown) // Key just released
            {
                for (auto& pair : m_map_listeners)
                {
                    pair.second->onKeyUp(i);
                }
            }
        }

        ::memcpy(m_old_keys_state, m_keys_state, sizeof(m_keys_state));
    }
}


void dx3d::InputSystem::addListener(InputListener* listener)
{
	m_map_listeners.insert(std::make_pair<InputListener*, InputListener* >(std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)));
}

void dx3d::InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = m_map_listeners.find(listener);

	if (it != m_map_listeners.end())
	{
		m_map_listeners.erase(it);
	}
}

dx3d::InputSystem* dx3d::InputSystem::get()
{
	static InputSystem system;

	return &system;
}
