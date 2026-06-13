#pragma once

#include "MeshRenderer.h"

#define FUNCTION_PREFIX extern "C" [[maybe_unused]] __declspec(dllexport)

FUNCTION_PREFIX MeshRenderer::Internal::IMesh* IMesh_CreateByNifPath(const char* nifPath, uint32_t width, uint32_t height);
FUNCTION_PREFIX void IMesh_Delete(MeshRenderer::Internal::IMesh* mesh);
FUNCTION_PREFIX void IMesh_Save(MeshRenderer::Internal::IMesh* mesh, const char* filePath);
