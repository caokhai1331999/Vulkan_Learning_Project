/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey Muratori's disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */
#include "Model.h"


void Model::Draw(Shader& shader){
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].Draw(shader);
    }
}

void Model::loadModel(char* path){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        cout<<"ERROR::ASSIMP::"<<importer.GetErrorString()<<endl;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene){
    // process all the node'scene meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene){
    vector<unsigned int>indices;
    vector<Texture>textures;
    vector<vertex>verticles;

    Vertex vertex;

    for(unsigned int i = 0; i < mesh->mNumVerticles; i++){
        glm::vec3 vector;
        // Verticle is position
        vector.x = mesh->mVerticles[i].x;
        vector.y = mesh->mVerticles[i].y;
        vector.z = mesh->mVerticles[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0]){
            glm::vec2 vec;
            vec.x = mesh->mTexCoords[0][i].x;
            vec.y = mesh->mTexCoords[0][i].y;
            vertex.TexCoords = vec;            
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        verticles->push_back(vertex)
        // Process VERTEX Position, Normal, Texure Coordinates
    }

    // Process INDICES(order of mesh vertex(which contain Position, Norm, TexCoords))
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        };
    }
    // Process MATERIAL
    if(mesh->mMaterialIndex > 0){
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // Texture is simple a type which recall texture from given path
        vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                                           aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material, 
                                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return Mesh(verticles, indices, textures);
}

vector <Texture>loadMaterialTextures(aiMaterial* mat, atTextureType type, string typeName){
    vector<Texture>textures ;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < loaded_textures.size(); j++){
            if(!std::strcmp(loaded_textures[j].path.C_Str(), str.C_Str())){
                loaded_textures.push_back(loaded_textures[j]);
                skip = true;
                break;
            }
        };
        if(!skip){
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            loaded_textures.push_back(texture);
        }
    };
    return textures;
}
