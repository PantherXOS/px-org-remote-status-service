//
// Created by Fakhri on 4/24/19.
//

#include "JsonBuilder.h"

StringBuffer JsonBuilder::cpupart(CpuParams cpuParams) {

    StringBuffer cpuPart;
    Writer<StringBuffer> writer(cpuPart);

    writer.StartObject();
    writer.Key("User");
    writer.Double(cpuParams.getUser());
    writer.Key("System");
    writer.Double(cpuParams.getSystem());
    writer.Key("Wait");
    writer.Double(cpuParams.getWait());           
    writer.EndObject();
    cout << cpuPart.GetString() << endl;

    return cpuPart;
}
