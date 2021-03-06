#include "GraphicsPipeline.h"

GraphicsPipeline::GraphicsPipeline()
{

}

GraphicsPipeline::~GraphicsPipeline()
{
	for (GraphicsModule* module : modules)
	{
		delete (module);
	}
	modules.clear();
}

void GraphicsPipeline::toggleModule(std::string moduleIdentifier)
{
	for (GraphicsModule* module : modules)
	{
		if (module->getIdentifier() == moduleIdentifier) 
		{
			module->toggleModule();
			break;
		}
	}
}

void GraphicsPipeline::intialisePipeline()
{
	for (GraphicsModule* module : modules)
	{
		if (module->isEnabled())
		{
			module->initialise();
		}
	}
}

void GraphicsPipeline::executeModules()
{
	for (GraphicsModule* module : modules)
	{
		if (module->isEnabled())
		{
			module->apply();
		}
	}
}


void GraphicsPipeline::addModule(GraphicsModule * module)
{
	modules.push_back(module);
}
