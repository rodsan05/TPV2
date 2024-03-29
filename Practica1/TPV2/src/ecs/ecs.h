// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>

namespace ecs {

class Manager;
class Entity;
class Component;

// We define type for the identifiers so we can change them easily.
// For example, if we have less than 256 components we can use one
// byte, i.e. uint8_t, if we have up to 512 we can use uint16_t,
// and so on ...
//
using cmpId_type = uint8_t;
using grpId_type = uint8_t;
using hdlrId_type = uint8_t;

// You should define a file ../game/ecs_defs.h with the list of your
// components, groups, and handlers. See ecs_defs_example.h for an
// example file
//
#if __has_include("../game/ecs_defs.h")
#include "../game/ecs_defs.h"
#else
#define _CMPS_LIST_ _CMP_1
#define _GRPS_LIST_ _GRP_2
#define _HDLRS_LIST_ _HDLR_1
#endif


// list of component identifiers
enum cmpId : cmpId_type {
	_CMPS_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_CMP_ID
};

// list of group identifiers
enum grpId : cmpId_type {
	_grp_GENERAL,
	_GRPS_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_GRP_ID
};

// list of handler identifiers
enum hdlrId : hdlrId_type {
	_HDLRS_LIST_, /* taken from ../game/ecs_defs */

	// do not remove this
	_LAST_HDLR_ID
};

constexpr cmpId_type maxComponentId = cmpId::_LAST_CMP_ID;
constexpr cmpId_type maxGroupId = grpId::_LAST_GRP_ID;
constexpr hdlrId_type maxHdlrId = hdlrId::_LAST_HDLR_ID;

// a macro for component identifier declaration, e.g., __CMPID_DECL__(ecs::_TRANSFORM)
// expands to:
//
//   constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;
//
#define __CMPID_DECL__(cId) constexpr static ecs::cmpId_type id = cId;

} // end of namespace

