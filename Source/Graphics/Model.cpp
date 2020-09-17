#include "Injector/Graphics/Model.hpp"
#include "Injector/Exception/Exception.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Injector
{
    Model::Model(const std::string& filePath)
    {
        auto importer = Assimp::Importer();
        auto scene = importer.ReadFile(filePath, aiProcess_ConvertToLeftHanded);

        if(!scene)
            throw Exception("Model", "Model", "Failed to load model");
    }
    Model::~Model()
    {
        
    }
}