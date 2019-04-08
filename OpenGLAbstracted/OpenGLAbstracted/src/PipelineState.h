#pragma once

#include "InputAssembler.h"
#include "VertexShader.h"
#include "FragmentShader.h"

struct PipelineState
{
	InputAssembler InputAssembler;
	VertexShader VertexShader;
	FragmentShader FragmentShader;
};