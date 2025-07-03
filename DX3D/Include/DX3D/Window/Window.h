#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>
#include <Windows.h>


namespace dx3d
{
	class Window: public Base
	{
	public:
		HWND getHandle() const { return static_cast<HWND>(m_handle); }
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;

	protected:
		void* m_handle{};
		Rect m_size{};
	};
}

