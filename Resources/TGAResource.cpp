// TGA image resource, TGA Loading inspired by Nate Miller.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// Modified by Anders Bach Nielsen <abachn@daimi.au.dk> - 21. Nov 2007
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/TGAResource.h>
#include <Resources/Exceptions.h>
#include <Resources/File.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Utils::Convert;

TGAPlugin::TGAPlugin() {
    this->AddExtension("tga");
}

ITextureResourcePtr TGAPlugin::CreateResource(string file) {
    return ITextureResourcePtr(new TGAResource(file));
}

TGAResource::TGAResource(string filename)
    : loaded(false),
      filename(filename),
      data(NULL) {
    width = height = depth = id = 0;
}

TGAResource::~TGAResource() {
    Unload();
}

void TGAResource::Load() {
    if (loaded) return;
    ifstream* file = File::Open(filename,ios::binary);

    // read in colormap info and image type, unsigned char 0 ignored
    unsigned char* type = new unsigned char[3];
    file->read((char*)type, sizeof(unsigned char)*3); 
    // check for supported tga file type
    if (type[1] != 0 || (type[2] != 2 && type[2] != 3)) {
        file->close();
    	throw ResourceException("Unsupported tga file: " + filename);
    }
    char dataIndex = type[0];
    delete[] type;
    // seek past the header and useless info
    file->seekg(12);
    unsigned char* info = new unsigned char[6];
    file->read((char*)info, sizeof(unsigned char)*6);
    width =  info[0] + (info[1] << 8);
    height = info[2] + (info[3] << 8);
    depth =  info[4];

    bool flipHori = (info[5]>>4) & 1; // bit number 4 (left-to-right)
    bool flipVert = (info[5]>>5) & 1; // bit number 5 (top-to-bottom)

    delete[] info;

    // make sure we are loading a supported color depth 
    if (depth != 32 && depth != 24 && depth != 8) {
        file->close();
        delete file;
        string msg = "Unsupported color depth: ";
        msg += Convert::ToString(depth) + " in file: " + filename;
        throw ResourceException(msg);
    }

    // load data, taking color depth into acount
    int numberOfCharsPerColor = (depth/8);
    long size = width * height * numberOfCharsPerColor;
    data = new unsigned char[size]; 
    
    file->seekg(dataIndex, ios_base::cur); // skip past image identification
    file->read((char*)data, sizeof(unsigned char)*size); 
    if (file->fail()) {
        delete [] data;
        data = NULL;
        file->close();
        delete file;
        throw ResourceException("Error loading TGA data in: " + filename);
    }
    if (depth != 8) { // this is not needed for 8bit as it does not have colors
        // convert the data from BGR to RGB
        for (int i=0; i < size; i+=numberOfCharsPerColor) {
            unsigned char temp = data[i];
            data[i] = data[i + 2];
            data[i + 2] = temp;
        }
    }

    file->close();
    delete file;

    // no image data 
    if (data == NULL)
    	throw ResourceException("Unsupported data in file: " + filename);

    // flip if needed
    if (flipVert && !flipHori)
      ReverseVertecally();
    else if (!flipVert && flipHori)
      ReverseHorizontally();
    else if (flipVert && flipHori)
      Reverse();

    loaded = true;
}

void TGAResource::Unload() {
    if (loaded) {
        delete[] data;
        loaded = false;
    }
}

int TGAResource::GetID(){
    return id;
}

void TGAResource::SetID(int id){
    this->id = id;
}

int TGAResource::GetWidth(){
    return width;
}

int TGAResource::GetHeight(){
    return height;
}

int TGAResource::GetDepth(){
    return depth;
}

unsigned char* TGAResource::GetData(){
    return data;
}

} //NS Resources
} //NS OpenEngine
