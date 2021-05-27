//
// Created by Fakhri on 4/24/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_JSONBUILDER_H
#define PX_ORG_REMOTE_STATUS_SERVICE_JSONBUILDER_H
#include <iostream>
#include <math.h>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "StatsParam.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "EventObject.h"
#include "Utils.h"


using namespace rapidjson;
using namespace std;

class JsonBuilder {
public:

    StringBuffer allStatus(StatsParam statsParam);
    StringBuffer event(vector<EventObject> eventObject);
private:
    StringBuffer cpuPart(CpuParams cpuParams);
    StringBuffer memoryPart(MemoryParams memoryParams);
    StringBuffer swapPart(MemoryParams swapParams);
    StringBuffer diskPart(vector<DiskParams> diskParams);
    StringBuffer generalPart(GeneralParams generalParams);
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_JSONBUILDER_H
