#pragma once
//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
// 用来为我们的3D模型封装成几何图形
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType				//这个类型将结合vertix buffer用
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	
	//这里的方法，是控制初始化和关闭，模型的顶点，索引缓冲区域
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);			//把几何模型输出到显卡内存里，为接下来的基础着色(CloroShader)做准备

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;  //在DirectX11里的所有buffer，都是这个类型。
	int m_vertexCount, m_indexCount;						//存两个buffer的size信息
};


