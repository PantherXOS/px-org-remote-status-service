//
// Created by Fakhri on 4/14/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_UTILS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_UTILS_H
using namespace std;

#include <string>
#include <array>
#include <bits/unique_ptr.h>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <wordexp.h>
#include <dirent.h>
#include <stdarg.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>


namespace UTILS {
    namespace DATETIME {
        int    ConvertToTimeStamp(string datetime);
    }
    namespace COMMAND {
        string Execute(const char* cmd);
    }

    namespace PXFILE
    {
        string abspath(const string &path);

        string basedir(const string &path);

        string filename(const string &path);

        vector<string> dirfiles(const string &path, string ext);

        string extpart(const string &fname);

        bool exists(const string &path);

        bool remove(const string &path);

        bool write(const string &path, const string &data);
    }

    namespace PATH
    {
        bool isunix(const string &path);

        string unix2path(const string &upath);
    }

}



#endif //PX_ORG_REMOTE_STATUS_SERVICE_UTILS_H
