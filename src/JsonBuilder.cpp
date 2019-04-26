//
// Created by Fakhri on 4/24/19.
//

#include "JsonBuilder.h"

StringBuffer JsonBuilder::cpuPart(CpuParams cpuParams) {
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

StringBuffer JsonBuilder::memoryPart(MemoryParams memoryParams) {
    StringBuffer memory;
    Writer<StringBuffer> writer(memory);
    writer.StartObject();
    writer.Key("Used");
    writer.Double(memoryParams.getUsed());
    writer.Key("Usage");
    writer.Double(memoryParams.getUsage());
    writer.EndObject();
    cout << memory.GetString() << endl;
    return memory;
}

StringBuffer JsonBuilder::swapPart(MemoryParams swapParams) {
    StringBuffer swap;
    Writer<StringBuffer> writer(swap);
    writer.StartObject();
    writer.Key("Used");
    writer.Double(swapParams.getUsed());
    writer.Key("Usage");
    writer.Double(swapParams.getUsage());
    writer.EndObject();
    cout << swap.GetString() << endl;
    return swap;
    return rapidjson::StringBuffer();
}

StringBuffer JsonBuilder::allStatus(StatsParam statsParam) {


// document is the root of a json message
    rapidjson::Document document;
    Document::AllocatorType& alloc = document.GetAllocator();

// define the document as an object rather than an array
    document.SetObject();


// must pass an allocator when the object may need to allocate memory
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

// create a rapidjson object type
    rapidjson::Value cpu(rapidjson::kObjectType);
    cpu.AddMember("user", statsParam.cpuParams.getUser(), allocator);
    cpu.AddMember("system",statsParam.cpuParams.getSystem() , allocator);
    cpu.AddMember("wait", statsParam.cpuParams.getWait(), allocator);

    rapidjson::Value memory(rapidjson::kObjectType);
    memory.AddMember("used", statsParam.memoryParams.getUsed(), allocator);
    memory.AddMember("usage",statsParam.memoryParams.getUsage() , allocator);

    rapidjson::Value swap(rapidjson::kObjectType);
    swap.AddMember("used", statsParam.swapParams.getUsed(), allocator);
    swap.AddMember("usage",statsParam.swapParams.getUsage() , allocator);

    rapidjson::Value system(rapidjson::kObjectType);
//    string s = statsParam.generalParams.getSystem().
    system.AddMember("system", "TODO" , allocator);
    system.AddMember("upTime", statsParam.generalParams.getUpTime(), allocator);
    system.AddMember("cpuUsage", cpu, allocator);
    system.AddMember("memory",memory , allocator);
    system.AddMember("swap",swap , allocator);

    rapidjson::Value Hardware(rapidjson::kObjectType);
    {
        Value disks(kArrayType);
for(DiskParams d : statsParam.diskParams){
    {
        Value disk(kObjectType);
        disk.AddMember("name", "TODO", alloc);
        disk.AddMember("total", d.getTotal(), alloc);
        disk.AddMember("free", d.getFree(), alloc);
        disk.AddMember("used", d.getUsed(), alloc);
        disk.AddMember("usage", d.getUsage(), alloc);
        disks.PushBack(disk, alloc);
    }}

        Hardware.AddMember("disks", disks, alloc);
    }


   // Hardware.AddMember("disk",disks , allocator);
    document.AddMember("bootTime", statsParam.generalParams.getBootTime(), allocator);
    document.AddMember("firimware", "TODO", allocator);
    document.AddMember("network", NULL, allocator);
    document.AddMember("hardware", Hardware, allocator);
    document.AddMember("system", system, allocator);



    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    document.Accept(writer);

    return strbuf;
}



