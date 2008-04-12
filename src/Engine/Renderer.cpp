#include "Renderer.h"
//--------------------------------------------------------------------------------
Renderer::Renderer(HWND hWnd)
:
m_hWnd(hWnd),
m_pkDevice(NULL)
{

}
//--------------------------------------------------------------------------------
Renderer::~Renderer()
{

}
//--------------------------------------------------------------------------------
bool Renderer::InitDX(HWND hWnd)
{
	IDirect3D9 * _pD3D;

	// Intento crear el objeto DX9
	_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!_pD3D)
		return false;

	//guardo la resoluci�n actual del escritorio
	D3DDISPLAYMODE displayMode;
	HRESULT hr = _pD3D->GetAdapterDisplayMode (
					D3DADAPTER_DEFAULT,
			 		&displayMode
				);

	if (hr!=D3D_OK)
		return false;

	// Fijo los valores a la estructura D3DPRESENT_PARAMETERS
	D3DPRESENT_PARAMETERS d3dPresentParameters;
	ZeroMemory( &d3dPresentParameters, sizeof(d3dPresentParameters));
	d3dPresentParameters.BackBufferFormat = displayMode.Format;
	d3dPresentParameters.Windowed = true;
	d3dPresentParameters.BackBufferCount = 1; 
	d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPresentParameters.hDeviceWindow = 0; 
	d3dPresentParameters.Flags = 0;
	d3dPresentParameters.EnableAutoDepthStencil = TRUE;
	d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8; d3dPresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//invocaremos al m�todo CreateDevice
	hr = _pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
 			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dPresentParameters,
			&m_pkDevice
		);

	if (hr!=D3D_OK)
		return false;

	if (!m_pkDevice)
		return false;

	m_pkDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pkDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	
	/*
	D3DXMatrixIdentity(&d3dmat);
	//D3DXMatrixTranslation(& d3dmat, 0,  0, 1.0f);
	//D3DXMatrixRotationZ(& d3dmat, 0);
	hr = m_pkDevice->SetTransform(D3DTS_WORLD, &d3dmat);

	if (hr!=D3D_OK)
		return false;
	D3DXMatrixIdentity(&d3dmat);
	D3DXVECTOR3 eyePos(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 lookPos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f); 
	D3DXMatrixLookAtLH(&d3dmat, &eyePos, &lookPos, &upVec);
	hr = m_pkDevice->SetTransform(D3DTS_VIEW, &d3dmat);

	if (hr!=D3D_OK)
		return false;
	D3DVIEWPORT9 kViewport;

	m_pkDevice->GetViewport(&kViewport);

	D3DXMatrixOrthoLH(&m_mProjectionMatrix, (float) kViewport.Height, (float) kViewport.Height, -25, 25);
	hr = m_pkDevice->SetTransform(D3DTS_PROJECTION, &m_mProjectionMatrix);

	if (hr!=D3D_OK)
		return false;

*/
	m_pkVertexBuffer = new VertexBuffer<ColorVertex,COLOR_VERTEX>();
	
	if (!m_pkVertexBuffer)
		return false;

	if (!m_pkVertexBuffer->Create(m_pkDevice, true))
		return false;


	return true;
}
//--------------------------------------------------------------------------------
void Renderer::StartFrame()
{
	// Limpia la escena
	m_pkDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 150, 150), 1.0f, 0);
	
	// Comienzo el render de una escena
	m_pkDevice->BeginScene();
}
//--------------------------------------------------------------------------------
void Renderer::EndFrame()
{
	// Termina el render de una escena
	m_pkDevice->EndScene();

	//Present
	m_pkDevice->Present(NULL, NULL, NULL, NULL);
}
//--------------------------------------------------------------------------------
void Renderer::Draw(
	ColorVertex * vertexColletion, 
	D3DPRIMITIVETYPE prim, 
	unsigned int uiVertexCount)
{
	StartFrame();
	m_pkVertexBuffer->Bind();
	m_pkVertexBuffer->Draw(vertexColletion, prim, uiVertexCount);
	EndFrame();
}
//--------------------------------------------------------------------------------
void Renderer::setViewPosition(float fPosX, float fPosY) 
{
	D3DXMATRIX kMatrix;
	D3DXVECTOR3 kEyePos;
	D3DXVECTOR3 kLookPos;
	D3DXVECTOR3 kUpVector;

	kEyePos.x = fPosX;	kEyePos.y = fPosY;	kEyePos.z = -5.0f;
	kLookPos.x = fPosX;	kLookPos.y = fPosY;	kLookPos.z = 0.0f;
	kUpVector.x = 0.0f;	kUpVector.y = 1.0f;	kUpVector.z = 0.0f;

	D3DXMatrixLookAtLH(&kMatrix, &kEyePos, &kLookPos, &kUpVector);
	m_pkDevice->SetTransform(D3DTS_VIEW, &kMatrix);
}
//----------------------------------------------------------------
void Renderer::setMatrixMode (MatrixMode eMode)
{
	m_eCurrentMatMode = eMode;
}
//----------------------------------------------------------------
void Renderer::loadIdentity ()
{
	D3DXMATRIX kTempMatrix;

	// set identity matrix
	D3DXMatrixIdentity(&kTempMatrix);

	// if it is a view matrix, use default values
	if (m_eCurrentMatMode == VIEW) {
		
		D3DXVECTOR3 kEyePos(0,0,-1);
		D3DXVECTOR3 kLookPos(0,0,0);
		D3DXVECTOR3 kUpVector(0,1,0);
		
		// generate the view matrix
		D3DXMatrixLookAtLH(&kTempMatrix, &kEyePos, &kLookPos, &kUpVector);
	}
	
	// convert from MatrixMode to D3DTRANSFORMSTATETYPE
	D3DTRANSFORMSTATETYPE eMatMode = static_cast<D3DTRANSFORMSTATETYPE>(m_eCurrentMatMode);
	
	// set the matrix
	m_pkDevice->SetTransform(eMatMode, &kTempMatrix);
}
//----------------------------------------------------------------
void Renderer::translate (float fX, float fY, float fZ)
{
	D3DXMATRIX kTempMatrix;

	// generate translation matrix
	D3DXMatrixTranslation(&kTempMatrix, fX,  fY, 1.0f);

	// convert from MatrixMode to D3DTRANSFORMSTATETYPE
	D3DTRANSFORMSTATETYPE eMatMode = static_cast<D3DTRANSFORMSTATETYPE>(m_eCurrentMatMode);

	// set the matrix
	m_pkDevice->MultiplyTransform(eMatMode, &kTempMatrix);
}
//----------------------------------------------------------------
void Renderer::rotateZ (float fAngle)
{
	D3DXMATRIX kTempMatrix;

	// generate translation matrix
	D3DXMatrixRotationZ(&kTempMatrix, fAngle);

	// convert from MatrixMode to D3DTRANSFORMSTATETYPE
	D3DTRANSFORMSTATETYPE eMatMode = static_cast<D3DTRANSFORMSTATETYPE>(m_eCurrentMatMode);

	// set the matrix
	m_pkDevice->MultiplyTransform(eMatMode, &kTempMatrix);
}
//----------------------------------------------------------------


