//
// Created by Fakhri on 4/24/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_JSONBUILDER_H
#define PX_ORG_REMOTE_STATUS_SERVICE_JSONBUILDER_H

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "CpuParams.h"
#include "GeneralParams.h"
#include <iostream>

using namespace rapidjson;
using namespace std;

class JsonBuilder {
public:
    StringBuffer cpupart(CpuParams cpuParams);
    StringBuffer generalPart(GeneralParams generalParams);


};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_JSONBUILDER_H
