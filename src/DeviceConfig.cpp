//
// Created by Fakhri on 4/28/19.
//

#include "DeviceConfig.h"

#define CONFIG_PATH "/etc/px-device-identity/device.yml"

#define CFG_CLIENT_ID_KEY "client_id"
#define CFG_CONFIG_VERSION_KEY "config_version"
#define CFG_DOMAIN_KEY "domain"
#define CFG_HOST_KEY "host"
#define CFG_ID_KEY "id"
#define CFG_INITED_ON_KEY "initiated_on"
#define CFG_IS_MANAGED_KEY "is_managed"
#define CFG_KEY_SECURITY_KEY "key_security"
#define CFG_KEY_TYPE_KEY "key_type"
#define CFG_LOCATION_KEY "location"
#define CFG_ROLE_KEY "role"
#define CFG_TITLE_KEY "title"

DeviceConfig::DeviceConfig(const string& path) {
    auto cfgPath = path.empty() ? string(CONFIG_PATH) : path;
    this->inited = false;
    try {
        auto config = YAML::LoadFile(cfgPath);
        this->client_id = config[CFG_CLIENT_ID_KEY].as<string>();
        this->config_version = config[CFG_CONFIG_VERSION_KEY].as<string>();
        this->domain = config[CFG_DOMAIN_KEY].as<string>();
        this->host = config[CFG_HOST_KEY].as<string>();
        this->id = config[CFG_ID_KEY].as<string>();
        this->initiated_on = config[CFG_INITED_ON_KEY].as<string>();
        this->is_managed = config[CFG_IS_MANAGED_KEY].as<bool>();
        this->key_security = config[CFG_KEY_SECURITY_KEY].as<string>();
        this->key_type = config[CFG_KEY_TYPE_KEY].as<string>();
        this->location = config[CFG_LOCATION_KEY].as<string>();
        this->role = config[CFG_ROLE_KEY].as<string>();
        this->title = config[CFG_TITLE_KEY].as<string>();
        this->inited = true;
    } catch(exception& e) {
        GLOG_INF("Exception: " + string(e.what()));
    }
}
