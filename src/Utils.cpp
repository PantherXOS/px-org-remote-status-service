//
// Created by Fakhri on 4/14/19.
//
#include "Utils.h"

int    UTILS::DATETIME::ConvertToTimeStamp(string datetime){
    struct tm tm;
    time_t unixtime;
    strptime(datetime.c_str(),"%a, %e %h %Y %H:%M:%S %z",&tm);
    unixtime = mktime(&tm);
    // ignore invalid timestamps and send '0' instead (#34)
    if (unixtime < 0) {
        unixtime = 0;
    }
    return unixtime;
}

string UTILS::COMMAND::Execute(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

string UTILS::PXFILE::abspath(const string &path) {
    string res;
    wordexp_t w;
    if (wordexp(path.c_str(), &w, 0) == 0) {
        res = string(*w.we_wordv);
        wordfree(&w);
    }
    return res;
}

string UTILS::PXFILE::basedir(const string &path) {
    string dir;
    size_t lastpos = path.rfind('/');
    if (lastpos != std::string::npos) {
        dir = path.substr(0, lastpos);
    }
    return dir;
}

string UTILS::PXFILE::filename(const string &path) {
    string fname;
    size_t lastpos = path.rfind('/');
    if (lastpos != std::string::npos) {
        fname = path.substr(lastpos + 1);
    }
    return fname;
}

vector<string> UTILS::PXFILE::dirfiles(const string &path, string ext) {
    vector<string> result;
    if (!ext.empty() && ext[0] == '.') {
        ext = ext.substr(1);
    }

    DIR *dirp = opendir(path.c_str());
    if (dirp != nullptr) {
        struct dirent *dp;
        while ((dp = readdir(dirp)) != nullptr) {
            if (strcmp(dp->d_name, ".") == 0)
                continue;
            if (strcmp(dp->d_name, "..") == 0)
                continue;

            if (ext.empty() || UTILS::PXFILE::extpart(dp->d_name) == ext) {
                result.emplace_back(dp->d_name);
            }
        }
        closedir(dirp);
    }
    return result;
}

string UTILS::PXFILE::extpart(const string &fname) {
    const char *fpointer = fname.c_str();
    const char *d = strrchr(fpointer, '.');
    if (!d || d == fpointer) {
        return string();
    }
    return string(d + 1);
}

bool UTILS::PXFILE::exists(const string &fpath) {
    struct stat buff{};
    return (stat(fpath.c_str(), &buff) == 0);
}

bool UTILS::PXFILE::remove(const string &path) {
    return (::remove(path.c_str()) == 0);
}

bool UTILS::PXFILE::write(const string &path, const string &data) {
    ofstream of(path.c_str(), ios::out);
    of << data;
    of.close();
    return true;
}


#define UNIX_PATH_HEADER "unix:"

bool UTILS::PATH::isunix(const string &path) {
    return (path.find(UNIX_PATH_HEADER) == 0);
}

string UTILS::PATH::unix2path(const string &upath) {
    string path = upath;
    if (isunix(upath)) {
        path.replace(0, strlen(UNIX_PATH_HEADER), "");
    }
    return path;
}

string UTILS::PATH::getExecPath(){
    char *arg1;
    arg1=(char *)malloc(1000*sizeof(char));
    char exepath[PATH_MAX + 1] = {0};

    sprintf( arg1, "/proc/%d/exe", getpid() );
    readlink( arg1, exepath, 1024 );
    string ret = string( exepath );
    std::size_t found = ret.find_last_of("//");
    ret=ret.substr(0,found+1);
    free(arg1);
    return ret;
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string UTILS::STRING::ltrim(const std::string &value) {
    auto start = value.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : value.substr(start);
}

std::string UTILS::STRING::rtrim(const std::string &value) {
    auto end = value.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : value.substr(0, end + 1);;
}

std::string UTILS::STRING::trim(const std::string &value) {
    return ltrim(rtrim(value));
}
