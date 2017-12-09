#pragma once

//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include "d3dclass.h"
#include <iostream>
#include <fstream>
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "AlignedAllocPolicy.h"
//把图形相关的全局变量都放在这里，这样代码就很清晰了
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////


class GraphicsClass 
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	void StoreTheVideoCardMsg();

private:
	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
};

