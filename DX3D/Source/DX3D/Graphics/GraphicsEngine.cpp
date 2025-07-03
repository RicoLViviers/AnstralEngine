#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Math/Vec3.h>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

	constexpr char shaderSourceCode[] =
		R"(
float4 VSMain(float3 pos: POSITION): SV_Position
{
return float4(pos.xyz, 1.0);
}
float4 PSMain(): SV_Target
{
return float4(1.0, 1.0, 1.0, 1.0);
}
)";
	constexpr char shaderSourceName[] = "Basic";
	constexpr auto shaderSourceCodeSize = std::size(shaderSourceCode);

	auto vs = device.compileShader({shaderSourceName, shaderSourceCode, shaderSourceCodeSize,
		"VSMain", ShaderType::VertexShader});
	auto ps = device.compileShader({ shaderSourceName, shaderSourceCode, shaderSourceCodeSize,
		"PSMain", ShaderType::PixelShader });

	m_pipeline = device.createGraphicsPipelineState({ *vs,*ps });

	const Vec3 vertexList[] =
	{
		// First triangle
		{-0.5f,  0.5f, 0.0f}, // Top-left
		{ 0.5f,  0.5f, 0.0f}, // Top-right
		{-0.5f, -0.5f, 0.0f}, // Bottom-left

		// Second triangle
		{-0.5f, -0.5f, 0.0f}, // Bottom-left
		{ 0.5f,  0.5f, 0.0f}, // Top-right
		{ 0.5f, -0.5f, 0.0f}  // Bottom-right
	};

	const Vec3 lineVertexList[] =
	{
		{-0.5f,  0.0f, 0.0f}, // Line 1 start
		{ 0.5f,  0.0f, 0.0f}, // Line 1 end
		{ 0.0f, -0.5f, 0.0f}, // Line 2 start
		{ 0.0f,  0.5f, 0.0f}  // Line 2 end
	};

	const Vec3 pointVertexList[] =
	{
		{-5.0, -5.0, 0.0},
		{ 0.0,  5.0, 0.0},
		{ 5.0, -5.0, 0.0},
		{10.0,  5.0, 0.0},
		{15.0, -5.0, 0.0},
		{20.0,  5.0, 0.0}
	};

	
	m_vb = device.createVertexBuffer({vertexList, std::size(vertexList), sizeof(Vec3)});
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0,0,0,1 });		//Set background color
	context.setGraphicsPipelineState(*m_pipeline);

	context.setViewportSize(swapChain.getSize());

	auto& vb = *m_vb;
	context.setVertexBuffer(vb);
	context.drawTriangleList(vb.getVertexListSize(), 0u); //Draw Triangle

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}
