#if !defined(C_MESH_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey's disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */
#define C_MESH_H

struct Texture{
    unsigned int id;
    string type;
    string path;
};

struct Mesh{
    unsigned int VBO, EBO;
    vector<Vertex> verticles;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;
    // MESH constructor
    Mesh( vector<Vertex> verticles,
          vector<unsigned int> indices,
          vector<Texture> textures):verticles(verticles), indices(indices), textures(textures)
          {
              setupMesh();
          }    
};

void setupMesh();
void Draw(Shader &shader);

#endif
