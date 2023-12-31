//
// Created by Fakhri on 4/24/19.
//

#include "JsonBuilder.h"

// StringBuffer JsonBuilder::cpuPart(CpuParams cpuParams) {
//     StringBuffer cpuPart;
//     Writer<StringBuffer> writer(cpuPart);

//     writer.StartObject();
//     writer.Key("User");
//     writer.Double(cpuParams.getUser());
//     writer.Key("System");
//     writer.Double(cpuParams.getSystem());
//     writer.Key("Wait");
//     writer.Double(cpuParams.getWait());
//     writer.EndObject();
//     cout << cpuPart.GetString() << endl;

//     return cpuPart;
// }

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

StringBuffer JsonBuilder::allStatus(StatsParam statsParam,vector<InstalledApplication> applicationList) {
// document is the root of a json message
    rapidjson::Document document;
    Document::AllocatorType& alloc = document.GetAllocator();

// define the document as an object rather than an array
    document.SetObject();

// must pass an allocator when the object may need to allocate memory
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

// create a rapidjson object type
    
    Value cpuNum(kArrayType);
    {
        for(auto d : statsParam.cpuParams){
            Value cpus(kObjectType);
            std::string s1(d.getFrequency());
            rapidjson::Value frq;
            char buffer[s1.length()];
            int len = sprintf(buffer, s1.c_str());
            frq.SetString(buffer, len, allocator);

            std::string s2(d.getmodel());
            char buffer2[s2.length()];
            Value cpModel;
            int len2 = sprintf(buffer2, s2.c_str());
            cpModel.SetString(buffer2, len2, allocator);

            cpus.AddMember("cores", d.getNumber(), alloc);
            cpus.AddMember("frequency", frq, alloc);
            cpus.AddMember("model", cpModel, allocator);
            cpuNum.PushBack(cpus,alloc);
        }  
    }
    // cpu.AddMember("user", statsParam.cpuParams.getUser(), allocator);
    // cpu.AddMember("system",statsParam.cpuParams.getSystem() , allocator);
    // cpu.AddMember("wait", statsParam.cpuParams.getWait(), allocator);
    Value applications(kArrayType);
    for(auto app : applicationList){
        Value application(kObjectType);
        Value name,version,loc;
        name.SetString(app.getName().c_str(),allocator);
        version.SetString(app.getVersion().c_str(),allocator);
        loc.SetString(app.getStoreLocation().c_str(),allocator);
        application.AddMember("name",name,alloc);
        application.AddMember("version",version,alloc);
        application.AddMember("storeLocation",loc,alloc);
        applications.PushBack(application,alloc);
    }
    rapidjson::Value softwareSystem(rapidjson::kObjectType); 
    softwareSystem.AddMember("system",applications, allocator);

    rapidjson::Value cpu(rapidjson::kObjectType);    
    cpu.AddMember("usage",statsParam.generalParams.getcpuUsage() , allocator);
    cpu.AddMember("used", statsParam.generalParams.getcpuUsed(), allocator);

   

    rapidjson::Value hdd(rapidjson::kObjectType);    
    hdd.AddMember("usage",statsParam.generalParams.getHddUsage() , allocator);
    hdd.AddMember("used", statsParam.generalParams.getHddUsed(), allocator);

    rapidjson::Value loadAvrage(rapidjson::kObjectType);
    loadAvrage.AddMember("user", statsParam.loadAverage.getUser(), allocator);
    loadAvrage.AddMember("system",statsParam.loadAverage.getSystem() , allocator);
    loadAvrage.AddMember("wait", statsParam.loadAverage.getWait(), allocator);

    
    rapidjson::Value memory(rapidjson::kObjectType);    
    memory.AddMember("usage",statsParam.memoryParams.getUsage() , allocator);
    memory.AddMember("used", statsParam.memoryParams.getUsed(), allocator);


    rapidjson::Value swap(rapidjson::kObjectType);
    swap.AddMember("usage",statsParam.swapParams.getUsage() , allocator);
    swap.AddMember("used", statsParam.swapParams.getUsed(), allocator);
    


    rapidjson::Value system(rapidjson::kObjectType);
    Value osVersion;
    osVersion.SetString(statsParam.generalParams.getVersion().c_str(),alloc);
    Value sys;    
    sys.SetString(StringRef(statsParam.generalParams.getSystem().c_str()));
    system.AddMember("osVersion", osVersion , allocator);
    system.AddMember("loadAverage", loadAvrage, allocator);
    //system.AddMember("upTime", statsParam.generalParams.getUpTime(), allocator);
    system.AddMember("cpu", cpu, allocator);
    system.AddMember("memory",memory , allocator);
    system.AddMember("swap",swap , allocator);
    system.AddMember("hdd",hdd , allocator);
    rapidjson::Value Hardware(rapidjson::kObjectType);
        {
        Value disks(kArrayType);
        for(DiskParams d : statsParam.diskParams){
            Value disk(kObjectType);            
            
            std::string s(d.getType());
            char buffer[s.length()];
            Value ty;
            int len = sprintf(buffer, s.c_str());
            ty.SetString(buffer, len, allocator);

            std::string s2(d.getModel());
            char buffer2[s2.length()];
            Value diskModel;
            int len2 = sprintf(buffer2, s2.c_str());
            diskModel.SetString(buffer2, len2, allocator);

            disk.AddMember("capacity", d.getCapacity(), alloc);
            disk.AddMember("type", ty, alloc);
            disk.AddMember("model", diskModel, alloc);            
            disks.PushBack(disk, alloc);
            }
        Hardware.AddMember("memory", statsParam.memoryParams.getTotal(), alloc);
        Hardware.AddMember("cpu", cpuNum, alloc);
        Hardware.AddMember("disks", disks, alloc);
    }

    
    Value networks(kArrayType);
        {        
        for(auto n : statsParam.networkParamList){
            Value network(kObjectType);
            Value name,type,mac;
           // version.erase(std::remove(version.begin(), version.end(), '\n'), version.end());
           name.SetString(n.getName().c_str(),allocator);
           type.SetString(n.getType().c_str(),allocator);
           mac.SetString(n.getMac().c_str(),allocator);
           network.AddMember("name", name, allocator);
           network.AddMember("mac", mac, allocator);
           network.AddMember("type", type, allocator);
            rapidjson::Value ipv4(rapidjson::kObjectType);
            {
                Value _ipv4_ip, _ipv4_extip, _ipv4_gatevay;
                _ipv4_ip.SetString(n.getIP4().ip.c_str(),allocator);
                _ipv4_extip.SetString(n.getIP4().extIp.c_str(),allocator);
                _ipv4_gatevay.SetString(n.getIP4().gateway.c_str(),allocator);
                ipv4.AddMember("ip", _ipv4_ip, allocator);
                ipv4.AddMember("extIp",_ipv4_extip , allocator);
                ipv4.AddMember("gateway", _ipv4_gatevay, allocator);
                Value dns4List(kArrayType);
                {
                    for(auto dn : n.getIP4().dns){
                       Value _dns;
                       _dns.SetString(dn.c_str(),allocator);
                        dns4List.PushBack(_dns , allocator);
                    }
                }
                ipv4.AddMember("dns",dns4List,alloc);
            }
            network.AddMember("ip4",ipv4,alloc);
            rapidjson::Value ipv6(rapidjson::kObjectType);
            {
                Value _ipv6_ip, _ipv6_extip, _ipv6_gatevay;
                _ipv6_ip.SetString(n.getIP6().ip.c_str(),allocator);
                _ipv6_extip.SetString(n.getIP6().extIp.c_str(),allocator);
                _ipv6_gatevay.SetString(n.getIP6().gateway.c_str(),allocator);
                ipv6.AddMember("ip", _ipv6_ip, allocator);
                ipv6.AddMember("extIp", _ipv6_extip, allocator);
                ipv6.AddMember("gateway", _ipv6_gatevay, allocator);
                Value dns6(kArrayType);
                {
                    for(auto dn : n.getIP6().dns){
                        Value _dns;
                       _dns.SetString(dn.c_str(),allocator);
                        dns6.PushBack(_dns, alloc);
                    }
                }
                ipv6.AddMember("dns",dns6,alloc);
            }
            network.AddMember("ip6",ipv6,alloc);
            network.AddMember("active", n.isActive(), allocator);
            networks.PushBack(network, allocator);
        }
       //Network.AddMember(" ",networks, alloc);
    }

    document.AddMember("bootTime", statsParam.generalParams.getBootTime(), allocator);
    document.AddMember("firmware", "TODO", allocator);
    document.AddMember("network", networks, allocator);
    document.AddMember("hardware", Hardware, allocator);
    document.AddMember("software", softwareSystem, allocator);
    document.AddMember("system", system, allocator);


    StringBuffer strbuf;
    Writer<StringBuffer> writer(strbuf);
    writer.SetMaxDecimalPlaces(2);
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




