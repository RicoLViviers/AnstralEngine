#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>
#include "DX3D/InputSystem/InputSystem.h"
#include "DX3D/InputSystem/InputHandler.h"

dx3d::Game::Game(const GameDesc& desc) :
	Base({*std::make_unique<Logger>(desc.logLevel).release()}),
	m_loggerPtr(&m_logger)
{
	m_testInput = std::make_unique<InputHandler>();

	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_logger});
	m_display = std::make_unique<Display>(DisplayDesc{ {m_logger,desc.windowSize},m_graphicsEngine->getGraphicsDevice()});

	DX3DLogInfo("Game initialized.");
}

dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down...");
}

void dx3d::Game::onInternalUpdate()
{
	InputSystem::get()->update();

	m_graphicsEngine->render(m_display->getSwapChain());
}
