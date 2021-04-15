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
		ifstream inFile;
		inFile.open(path);
		if (!inFile.good())
		{
			cerr << "Can't open obj file " << path << endl;
			return nullptr;
		}
		Mesh* mesh = new Mesh();
		std::string line;
		int faceCount = 0;
		mesh->VertexCount = 0;
		mesh->TexCoordCount = 0;
		mesh->NormalCount = 0;
		std::vector<Vertex> tempVertices;
		std::vector<TexCoord> tempTexCoords;
		std::vector<Vector3> tempNormals;
		std::vector<GLushort> vertexIndices, texIndices, normalIndices;
		while (getline(inFile, line)) {
			if (line.at(0) == 'v' && line.at(1) == ' ') {
				mesh->VertexCount++;
				std::istringstream stream(line.substr(2));
				Vertex nextV;
				stream >> nextV.x >> nextV.y >> nextV.z;
				tempVertices.push_back(nextV);
			}
			else if (line.at(0) == 'v' && line.at(1) == 't') {
				mesh->TexCoordCount++;
				std::istringstream stream(line.substr(3));
				TexCoord nextT;
				stream >> nextT.u >> nextT.v;
				tempTexCoords.push_back(nextT);
			}
			else if (line.at(0) == 'v' && line.at(1) == 'n') {
				mesh->NormalCount++;
				std::istringstream stream(line.substr(3));
				Vector3 nextN;
				stream >> nextN.x >> nextN.y >> nextN.z;
				tempNormals.push_back(nextN);
			}
			else if (line.at(0) == 'f' && line.at(1) == ' ') {
				faceCount++;
				std::replace(line.begin(), line.end(), '/', ' ');
				std::istringstream stream(line.substr(2));
				GLushort vertexIndex[3], tIndex[3], normalIndex[3];
				stream >> vertexIndex[0] >> tIndex[0] >> normalIndex[0] >> vertexIndex[1] >>
					tIndex[1] >> normalIndex[1] >> vertexIndex[2] >> tIndex[2] >> normalIndex[2];
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				texIndices.push_back(tIndex[0]);
				texIndices.push_back(tIndex[1]);
				texIndices.push_back(tIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

			}
		}
		mesh->Vertices = new Vertex[mesh->VertexCount];
		mesh->TexCoords = new TexCoord[mesh->TexCoordCount];
		mesh->Normals = new Vector3[mesh->NormalCount];
		for (int i = 0; i < vertexIndices.size(); i++) {
			GLushort vertexIndex = vertexIndices.at(i);
			mesh->Vertices[i] = tempVertices[vertexIndex - 1];

		}
		for (int i = 0; i < texIndices.size(); i++) {
			GLushort texIndex = texIndices.at(i);
			mesh->TexCoords[i] = tempTexCoords[texIndex - 1];

		}
		for (int i = 0; i < normalIndices.size(); i++) {
			GLushort normalIndex = normalIndices.at(i);
			mesh->Normals[i] = tempNormals[normalIndex - 1];
		}
		return mesh;
	}

}