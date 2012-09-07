#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED

#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

typedef boost::property_tree::ptree Blueprint;
typedef unsigned long ObjectId;
typedef unsigned long CompType;
typedef unsigned short ComponentFlag;
typedef std::vector<std::string> Parameters;

const int MIN_DIST = 4;

namespace cType
{
    enum{   Health=1,
            Name=2,
            Coords=3,
            Move=4,
            Gfx=5,
            Launcher=6,
            Collision=7
        };
}

//@@@Requires updating on addition on new subsystem" when adding new subsystems
namespace cFlag
{
    enum{   Obj=0,
            Gfx=1,
            Coords=2,
            Audio=4,
            Move=8,
            Input=16,
            Brain=32,
            Stats=64,
            Collision=128,
            Health=256,
            OnSelect=512,
            Name=1024,
            Launcher=2048,
            MAX=8192,
        };


}

#endif // TYPEDEFS_H_INCLUDED
