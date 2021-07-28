#pragma once
#include "Mesh.h"
#include "CorePCH.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	Model(const char* path, bool gamma = false) : gammaCorrection(gamma)
	{	loadModel(path);	}

	void Draw(Shader& shader);

	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
	bool gammaCorrection;

private:

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	void loadModel(std::string path);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

