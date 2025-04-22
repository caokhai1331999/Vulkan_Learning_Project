#if !defined(C_MODEL_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey's disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */

#define C_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#if !defined
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

#include "C_Mesh.h"

struct Model{
    // Model data
    vector<Mesh>meshes;
    string directory;
    vector<Texture>loaded_textures;

    Model(char *path = nullptr){
        if(path != nullptr){
            loadModel(path);
        }
    };    
};

unsigned int TextureFromFile(Model& model, const char *path, const string &directory, bool gamma = false);
void loadModel(Model& model, string path);
void processNode(Model& model, aiNode* node, const aiScene* scene);
Mesh processMesh(Model& model, aiMesh* mesh, const aiScene* scene);
vector <Texture>loadMaterialTextures(Model& model, aiMaterial* mat, aiTextureType type, string typeName);

#endif
