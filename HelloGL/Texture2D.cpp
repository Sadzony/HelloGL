#include "Texture2D.h"
using namespace std;
Texture2D::Texture2D()
{
    
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
    char* tempTextureData; int fileSize; ifstream inFile;
    _width = width; _height = height;
    inFile.open(path, ios::binary);
    if (inFile.bad()) {
        cerr << "Can't open texture file " << path << endl;
        return false;
    }
    inFile.seekg(0, ios::end);
    fileSize = (int)inFile.tellg();
    tempTextureData = new char[fileSize];
    inFile.seekg(0, ios::beg);
    inFile.read(tempTextureData, fileSize);
    inFile.close();
    cout << path << " loaded." << endl;
    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
    delete[]tempTextureData;
    return true;
}

bool Texture2D::LoadTGA(char* path)
{
    char* tempHeaderData = new char[18];
    char* tempTextureData;
    int fileSize;
    char type, pixelDepth, mode;
    ifstream inFile;
    inFile.open(path, ios::binary);
    if (inFile.bad()) {
        cerr << "Can't open texture file " << path << endl;
        return false;
    }
    inFile.seekg(0, ios::beg);
    inFile.read(tempHeaderData, 18);
    inFile.seekg(0, ios::end);
    fileSize = (int)inFile.tellg() - 18;
    tempTextureData = new char[fileSize];
    inFile.seekg(18, ios::beg);
    inFile.read(tempTextureData, fileSize);
    inFile.close();
    type = tempHeaderData[2];
    _width = ((unsigned char)tempHeaderData[13] << 8u) + (unsigned char)tempHeaderData[12];
    _height = ((unsigned char)tempHeaderData[15] << 8u) + (unsigned char)tempHeaderData[14];
    pixelDepth = tempHeaderData[16];
    bool flipped = false;
    if ((int)((tempHeaderData[11] << 8) + tempHeaderData[10]) == 0) {
        flipped = true;
    }
    if (type == 2) {
        cout << path << " loaded." << endl;
        glGenTextures(1, &_ID);
        glBindTexture(GL_TEXTURE_2D, _ID);
    }
    mode = pixelDepth / 8;
    if (mode == 4) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, _width, _height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tempTextureData);
    }
    else {
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, _width, _height, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);
    }
    delete [] tempHeaderData;
    delete[] tempTextureData;
    return true;

}

bool Texture2D::LoadBMP(char* path)
{
    char* tempHeaderData = new char[54];
    char* tempTextureData;
    ifstream inFile;
    inFile.open(path, ios::binary);
    if (inFile.bad()) {
        cerr << "Can't open texture file " << path << endl;
        return false;
    }
    inFile.seekg(0, ios::beg);
    inFile.read(tempHeaderData, 54);
    int dataPos = *(int*)&(tempHeaderData[0x0A]);
    int fileSize = *(int*)&(tempHeaderData[0x22]);
    _width = *(int*)&(tempHeaderData[0x12]);
    _height = *(int*)&(tempHeaderData[0x16]);
    if (tempHeaderData[0] != 'B' || tempHeaderData[1] != 'M') {
        cerr << path << " is not a correct BMP file" << endl;
        return 0;
    }
    if (dataPos == 0) {
        dataPos = 54;
    }
    if (fileSize == 0) {
        fileSize = _width * _height * 3;
    }
    tempTextureData = new char[fileSize];
    inFile.read(tempTextureData, fileSize);
    inFile.close();
    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, _width, _height, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);
    delete[] tempHeaderData;
    delete[] tempTextureData;
    return true;
}
