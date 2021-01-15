#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath, int typeMap, int typeCamera)
{
	this->id = id;
	this->sceneFilePath = filePath;
	this->typeMap = typeMap;
	this->typeCamera = typeCamera;
}