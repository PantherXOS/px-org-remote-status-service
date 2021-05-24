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
    Value sys;
    sys.SetString(StringRef(statsParam.generalParams.getSystem().c_str()));
    system.AddMember("system", "TODO" , allocator);
    //system.AddMember("upTime", statsParam.generalParams.getUpTime(), allocator);
    system.AddMember("cpu", cpu, allocator);
    system.AddMember("memory",memory , allocator);
    system.AddMember("swap",swap , allocator);
    rapidjson::Value Hardware(rapidjson::kObjectType);
        {
        Value disks(kArrayType);
        for(DiskParams d : statsParam.diskParams){
            Value disk(kObjectType);
            Value name;
            name.SetString(StringRef(d.getName().c_str()));
            disk.AddMember("name", name, alloc);
            disk.AddMember("total", d.getTotal(), alloc);
            disk.AddMember("free", d.getFree(), alloc);
            disk.AddMember("used", d.getUsed(), alloc);
            disk.AddMember("usage", d.getUsage(), alloc);
            disks.PushBack(disk, alloc);
            }
        Hardware.AddMember("disks", disks, alloc);
    }
    Document d2;
    d2.SetObject();
    rapidjson::Value Network(rapidjson::kObjectType);
        {
        Value networks(kArrayType);
        for(auto n : statsParam.networkParamList){
            Value network(kObjectType);
            //Value name;
           // name.SetString(StringRef(d.getName().c_str()));
            network.AddMember("name", n.getName(), d2.GetAllocator());
            network.AddMember("mac", n.getMac(), d2.GetAllocator());
            network.AddMember("type", n.getType(), d2.GetAllocator());
            // rapidjson::Value ipv4(rapidjson::kObjectType);
            //     ipv4.AddMember("ip", n.getIP4().ip, allocator);
            //     ipv4.AddMember("extip",n.getIP4().extIp , allocator);
            //     ipv4.AddMember("gateway", n.getIP4().gateway, allocator);
                // Value dns4(kArrayType);
                // for(auto dn : n.getIP4().dns){
                //     ipv4.AddMember("dns",dn , allocator);
                //      dns4.PushBack(dn,alloc);
                // }
                // ipv4.AddMember("dns",dns4,alloc);
            // network.AddMember("ip4",ipv4,alloc);
            // rapidjson::Value ipv6(rapidjson::kObjectType);
            //     ipv6.AddMember("ip", n.getIP6().ip, allocator);
            //     ipv6.AddMember("extip",n.getIP6().extIp , allocator);
            //     ipv6.AddMember("gateway", n.getIP6().gateway, allocator);
                // Value dns6(kArrayType);
                // for(auto dn : n.getIP6().dns){
                //     ipv6.AddMember("dns",dn , allocator);
                //     dns6.PushBack(dn,alloc);
                // }
                // ipv6.AddMember("dns",dns6,alloc);
            // network.AddMember("ip6",ipv6,alloc);

            network.AddMember("active", n.isActive(), alloc);
            networks.PushBack(network, d2.GetAllocator());
        }
        Network.AddMember(" ", networks, alloc);
    }

    document.AddMember("boot_time", statsParam.generalParams.getBootTime(), allocator);
    document.AddMember("firmware", "TODO", allocator);
    document.AddMember("network", Network, allocator);
    document.AddMember("hardware", Hardware, allocator);
    document.AddMember("system", system, allocator);


    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    document.Accept(writer);

    return strbuf;
}

StringBuffer JsonBuilder::event(vector<EventObject> eventObject) {
    rapidjson::Document document;
    Value name,val;
    Document::AllocatorType& alloc = document.GetAllocator();
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value events(rapidjson::kArrayType);
    for (auto _event : eventObject)
    {
        rapidjson::Value event(kObjectType);
        name.SetString(StringRef(_event.getEvent().c_str()));
        event.AddMember("event",name,alloc);
        name.SetString(StringRef(_event.getTopic().c_str()));
        event.AddMember("topic",name,alloc);
        event.AddMember("time",_event.getTime(),alloc);
        rapidjson::Value params(rapidjson::kArrayType);
        for(auto _param : _event.getParam()){
            rapidjson::Value param(kObjectType);
            name.SetString(StringRef(_param.first.c_str()));
            val.SetString(StringRef(_param.second.c_str()));
            param.AddMember(name,val,alloc);
            params.PushBack(param,alloc);
        }
        event.AddMember("params",params,alloc);
        events.PushBack(event,alloc);
    }
    document.AddMember("events",events,alloc);
    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    document.Accept(writer);

    return strbuf;
}



