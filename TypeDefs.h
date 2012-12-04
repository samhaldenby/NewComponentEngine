#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED

#include <vector>
#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

typedef boost::property_tree::ptree Blueprint;
typedef unsigned long ObjectId;
typedef unsigned long CompType;
typedef unsigned long ComponentFlag;
typedef std::vector<std::string> Parameters;
typedef std::map<std::string, std::string> NamedParams;

//collision typedefs
typedef std::pair<int,int> GridLocation;
typedef std::multimap<GridLocation,std::vector<ObjectId> > CollisionHash;

const int MIN_DIST = 4;
const int MAX_OBJECT_DIMENSION = 50;
const int MAX_CONCURRENT_SOUNDS = 16;

namespace cType
{
    enum{   Health=1,
            Name=2,
            Coords=3,
            Move=4,
            Gfx=5,
            Audio=6,
            Launcher=7,
            Collision=8,
            Ai=9,
            Event=10,
            Anchor=11,
            Trigger=12
        };
}

//@@@Requires updating on addition on new subsystem" when adding new subsystems
namespace cFlag
{
    enum{   Obj     =0x0,//0,
            Gfx     =0x1,//1,
            Coords  =0x2,//2,
            Audio   =0x4,//4,
            Move    =0x8,//8,
            Input   =0x10,//16,
            Brain   =0x20,//=32,
            Stats   =0x40,//=64,
            Collision=0x80,//=128,
            Health  =0x100,//256,
            OnSelect=0x200,//512,
            Name    =0x400,//1024,
            Launcher=0x800,//2048,
            Ai      =0x1000,//4096
            Event   =0x2000,//8192
            Anchor  =0x4000,//16384
            Trigger =0x8000,//32768
            MAX     =65536//65536,
        };


}

#endif // TYPEDEFS_H_INCLUDED
