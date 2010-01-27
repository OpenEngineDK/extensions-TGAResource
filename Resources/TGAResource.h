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

#include <Resources/ITextureResource.h>
#include <Resources/IResourcePlugin.h>
#include <string>
#include <iostream>
#include <fstream>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/extended_type_info.hpp>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * TGA image resource.
 *
 * @class TGAResource TGAResource.h Resources/TGAResource.h
 */
class TGAResource : public ITextureResource {
private:
    string filename;            //!< file name

public:
    //    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        
        ar & boost::serialization::base_object<ITextureResource>(*this);
        ar & filename;
        
    }

    TGAResource() : ITextureResource() {}

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
class TGAPlugin : public IResourcePlugin<ITextureResource> {
public:
	TGAPlugin();
    ITextureResourcePtr CreateResource(string file);
};

} //NS Resources
} //NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Resources::TGAResource)

#endif // _TGA_RESOURCE_H_
