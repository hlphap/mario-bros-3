#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath, int typeMap)
{
	this->typeMap = typeMap;
	this->id = id;
	this->sceneFilePath = filePath;
}