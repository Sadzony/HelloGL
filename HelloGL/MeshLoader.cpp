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
		mesh->FaceCount = 0;
		std::vector<Vertex> tempVertices;
		std::vector<TexCoord> tempTexCoords;
		std::vector<Vector3> tempNormals;
		std::vector<Face> faces;
		while (getline(inFile, line)) {
			if (line.at(0) == 'v' && line.at(1) == ' ') {
				std::istringstream stream(line.substr(2));
				Vertex nextV;
				stream >> nextV.x >> nextV.y >> nextV.z;
				tempVertices.push_back(nextV);
			}
			else if (line.at(0) == 'v' && line.at(1) == 't') {
				std::istringstream stream(line.substr(3));
				TexCoord nextT;
				stream >> nextT.u >> nextT.v;
				tempTexCoords.push_back(nextT);
			}
			else if (line.at(0) == 'v' && line.at(1) == 'n') {
				std::istringstream stream(line.substr(3));
				Vector3 nextN;
				stream >> nextN.x >> nextN.y >> nextN.z;
				tempNormals.push_back(nextN);
			}
			else if (line.at(0) == 'f' && line.at(1) == ' ') {
				mesh->FaceCount++;
				std::replace(line.begin(), line.end(), '/', ' ');
				std::istringstream stream(line.substr(2));
				Face nextF;
				stream >> nextF.v1 >> nextF.t1 >> nextF.n1 >> nextF.v2 >>
					nextF.t2 >> nextF.n2 >> nextF.v3 >> nextF.t3 >> nextF.n3;

				faces.push_back(nextF);
			}
		}
		std::vector<Vertex*> outVertices;
		std::vector<TexCoord*> outTexCoords;
		std::vector<Vector3*> outNormals;
		int vIndex, tIndex, nIndex;
		for (int i = 0; i < mesh->FaceCount; i++) {
			Vertex* outVertex1 = new Vertex();
			TexCoord* outTex1 = new TexCoord();
			Vector3* outNormal1 = new Vector3();
			vIndex = faces.at(i).v1 - 1;
			tIndex = faces.at(i).t1 - 1;
			nIndex = faces.at(i).n1 - 1;

			outVertex1->x = tempVertices[vIndex].x;
			outVertex1->y = tempVertices[vIndex].y;
 			outVertex1->z = tempVertices[vIndex].z;
			outVertices.push_back(outVertex1);

			outTex1->u = tempTexCoords[tIndex].u;
			outTex1->v = tempTexCoords[tIndex].v;
			outTexCoords.push_back(outTex1);

			outNormal1->x = tempNormals[nIndex].x;
			outNormal1->y = tempNormals[nIndex].y;
			outNormal1->z = tempNormals[nIndex].z;
			outNormals.push_back(outNormal1);


			Vertex* outVertex2 = new Vertex();
			TexCoord* outTex2  = new TexCoord();
			Vector3* outNormal2 = new Vector3();
			vIndex = faces.at(i).v2 - 1;
			tIndex = faces.at(i).t2 - 1;
			nIndex = faces.at(i).n2 - 1;

			outVertex2->x = tempVertices[vIndex].x;
			outVertex2->y = tempVertices[vIndex].y;
			outVertex2->z = tempVertices[vIndex].z;
			outVertices.push_back(outVertex2);

			outTex2->u = tempTexCoords[tIndex].u;
			outTex2->v = tempTexCoords[tIndex].v;
			outTexCoords.push_back(outTex2);

			outNormal2->x = tempNormals[nIndex].x;
			outNormal2->y = tempNormals[nIndex].y;
			outNormal2->z = tempNormals[nIndex].z;
			outNormals.push_back(outNormal2);


			Vertex* outVertex3 = new Vertex();
			TexCoord* outTex3 = new TexCoord();
			Vector3* outNormal3 = new Vector3();
			vIndex = faces.at(i).v3 - 1;
			tIndex = faces.at(i).t3 - 1;
			nIndex = faces.at(i).n3 - 1;

			outVertex3->x = tempVertices[vIndex].x;
			outVertex3->y = tempVertices[vIndex].y;
			outVertex3->z = tempVertices[vIndex].z;
			outVertices.push_back(outVertex3);

			outTex3->u = tempTexCoords[tIndex].u;
			outTex3->v = tempTexCoords[tIndex].v;
			outTexCoords.push_back(outTex3);

			outNormal3->x = tempNormals[nIndex].x;
			outNormal3->y = tempNormals[nIndex].y;
			outNormal3->z = tempNormals[nIndex].z;
			outNormals.push_back(outNormal3);
		}
		mesh->VertexCount = outVertices.size();
		mesh->Vertices = new Vertex[outVertices.size()];
		for (int i = 0; i < outVertices.size(); i++) {
			mesh->Vertices[i] = *outVertices.at(i);
		}

		mesh->TexCoordCount = outTexCoords.size();
		mesh->TexCoords = new TexCoord[outTexCoords.size()];
		for (int i = 0; i < outTexCoords.size(); i++) {
			mesh->TexCoords[i] = *outTexCoords.at(i);
		}

		mesh->NormalCount = outNormals.size();
		mesh->Normals = new Vector3[outNormals.size()];
		for (int i = 0; i < outNormals.size(); i++) {
			mesh->Normals[i] = *outNormals.at(i);
		}
		return mesh;
	}

}