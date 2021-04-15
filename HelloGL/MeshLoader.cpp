#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

namespace MeshLoader
{
	Mesh* MeshLoader::LoadOBJ(char* path) {
		Mesh* mesh = new Mesh();
		ifstream inFile;
		inFile.open(path);
		if (!inFile.good())
		{
			cerr << "Can't open obj file " << path << endl;
			return nullptr;
		}
		std::string line;
		int vertexCount;
		int texCoordCount;
		int normalCount;
		int faceCount;
		std::vector<Vertex*> vertices;
		std::vector<TexCoord*> texCoords;
		std::vector<Vector3*> normals;
		std::vector<Face*> faces;
		while (getline(inFile, line)) {
			if (line.at(0) == 'v') {
				vertexCount++;
				std::istringstream stream(line.substr(2));
				Vertex* nextV = new Vertex();
				stream >> nextV->x >> nextV->y >> nextV->z;
				vertices.push_back(nextV);
			}
			else if (line.at(0) == 'v' && line.at(1) == 't') {
				texCoordCount++;
				std::istringstream stream(line.substr(3));
				TexCoord* nextT = new TexCoord();
				stream >> nextT->u >> nextT->v;
				texCoords.push_back(nextT);
			}
			else if (line.at(0) == 'v' && line.at(1) == 'n') {
				normalCount++;
				std::istringstream stream(line.substr(3));
				Vector3* nextN = new Vector3();
				stream >> nextN->x >> nextN->y >> nextN->z;
				normals.push_back(nextN);
			}
			else if (line.at(0) == 'f') {
				faceCount++;
				std::replace(line.begin(), line.end(), '/', ' ');
				std::istringstream stream(line.substr(2));
				Face* nextF = new Face();
				stream >> nextF->vIndex1 >> nextF->vIndex2 >> nextF->vIndex3 >> nextF->tIndex1 >>
					nextF->tIndex2 >> nextF->tIndex3 >> nextF->nIndex1 >> nextF->nIndex2 >> nextF->nIndex3;
				faces.push_back(nextF);
			}
		}
		mesh->VertexCount = vertexCount;
		mesh->TexCoordCount = texCoordCount;
		mesh->NormalCount = normalCount;
		mesh->FaceCount = faceCount;
		mesh->Vertices = new Vertex[vertexCount];
		mesh->TexCoords = new TexCoord[texCoordCount];
		mesh->Normals = new Vector3[normalCount];
		mesh->Faces = new Face[faceCount];
		for (int i = 0; i < vertices.size(); i++) {
			mesh->Vertices[i] = *vertices.at(i);
		}
		for (int i = 0; i < texCoords.size(); i++) {
			mesh->TexCoords[i] = *texCoords.at(i);
		}
		for (int i = 0; i < normals.size(); i++) {
			mesh->Normals[i] = *normals.at(i);
		}
		for (int i = 0; i < faces.size(); i++) {
			mesh->Faces[i] = *faces.at(i);
		}
		return mesh;
	}

}