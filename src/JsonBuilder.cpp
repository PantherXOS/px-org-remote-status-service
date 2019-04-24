//
// Created by Fakhri on 4/24/19.
//

#include "JsonBuilder.h"

StringBuffer JsonBuilder::cpupart(CpuParams cpuParams) {

    StringBuffer cpuPart;
    Writer<StringBuffer> writer(cpuPart);

    writer.StartObject();               // Between StartObject()/EndObject(),
    writer.Key("User");                // output a key,
    writer.Double(cpuParams.getUser());             // follow by a value.
    writer.Key("System");                // output a key,
    writer.Double(cpuParams.getSystem());             // follow by a value.
    writer.Key("Wait");                // output a key,
    writer.Double(cpuParams.getWait());             // follow by a value.
    writer.EndObject();

    // {"hello":"world","t":true,"f":false,"n":null,"i":123,"pi":3.1416,"a":[0,1,2,3]}
    cout << cpuPart.GetString() << endl;

    return cpuPart;
}
