#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"

class CScene
{
public:
	CKeyEventHandler* key_handler;
	int id;
	LPCWSTR sceneFilePath;

	//Custom
	int typeMap;
	int typeCamera;
public:
	CScene(int id, LPCWSTR filePath, int typeMap, int typeCamera);

	CKeyEventHandler* GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef CScene* LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
protected:
	CScene* scence;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;                 
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene* s) :CKeyEventHandler() { scence = s; } // Dung swithc scence
};