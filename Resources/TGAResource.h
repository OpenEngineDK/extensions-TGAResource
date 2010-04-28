// TGA image resource, TGA Loading inspired by Nate Miller.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// Modified by Anders Bach Nielsen <abachn@daimi.au.dk> - 21. Nov 2007
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TGA_RESOURCE_H_
#define _TGA_RESOURCE_H_

#include <Resources/Texture2D.h>
#include <Resources/IResourcePlugin.h>
#include <string>
#include <iostream>
#include <fstream>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * TGA image resource.
 *
 * @class TGAResource TGAResource.h Resources/TGAResource.h
 */
class TGAResource : public Texture2D<unsigned char> {
private:
    string filename;            //!< file name

public:
    TGAResource() : Texture2D<unsigned char>() {}

    /**
     * Constructor
     *
     * @param file tga file to load.
     */
    TGAResource(string file);
    ~TGAResource();

    // resource methods
    void Load();
};

/**
 * TGA texture resource plug-in.
 *
 * @class TGAPlugin TGAResource.h Resources/TGAResource.h
 */
class TGAPlugin : public IResourcePlugin<ITexture2D> {
public:
	TGAPlugin();
    ITexture2DPtr CreateResource(string file);
};

/**
 * TGA texture resource plug-in.
 *
 * @class UCharTGAPlugin TGAResource.h Resources/TGAResource.h
 */
class UCharTGAPlugin : public IResourcePlugin<UCharTexture2D> {
public:
	UCharTGAPlugin();
    UCharTexture2DPtr CreateResource(string file);
};

} //NS Resources
} //NS OpenEngine

#endif // _TGA_RESOURCE_H_
