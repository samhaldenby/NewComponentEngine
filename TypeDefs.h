#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED

#include <vector>
#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Vector2d.h"
#include <list>

//forward decs
class Effect;



typedef boost::property_tree::ptree Blueprint;
typedef unsigned long ObjectId;
typedef unsigned long CompType;
typedef unsigned long ComponentFlag;
typedef std::vector<std::string> Parameters;
typedef std::map<std::string, double> StatsMap;
typedef std::map<std::string, Effect*> EffectsMap;
typedef std::map<std::string, std::string> NamedParams;
typedef std::list<Vector2d> Path;

//collision typedefs
typedef std::pair<int,int> GridLocation;
typedef std::multimap<GridLocation,std::vector<ObjectId> > CollisionHash;

const Vector2d NO_VECTOR(-18021982,-27041977);
const int MIN_DIST = 4;
const int MAX_OBJECT_DIMENSION = 50;
const int MAX_CONCURRENT_SOUNDS = 16;
const double NO_DURATION = -999999;
const double PI = 3.14159265;
const double DEG_TO_RAD_MOD = PI/180.00;
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
            Trigger=12,
            Stats=13,
            Effects=14,
            Path=15,
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
            Effects =0x20,//=32,
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
            Path    =0x10000,//65536
            MAX     =0x20000//131072,
        };


}

#endif // TYPEDEFS_H_INCLUDED
