#if !defined(MODEL_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey's disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */

#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

using namespace std;

class Model{
public:
    Model(char *path){
        loadModel(path);        
    };
    void Draw(Shader& shader);
    
private:
    // Model data
    vector<Mesh>meshes;
    string directory;
    vector<Texture>loaded_textures;
    
    void loadModel(char* path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector <Texture>loadMaterialTextures(aiMaterial* mat, atTextureType type, string typeName);
};

#endif
