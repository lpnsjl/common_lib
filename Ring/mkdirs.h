//
// Created by andrew on 6/16/23.
//

#ifndef RING_MKDIRS_H
#define RING_MKDIRS_H

#ifdef WIN32
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif
#include <stdint.h>
#include <string>
#include <iostream>
#define MAX_PATH_LEN 256

#ifdef WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

// 从左到右依次判断文件夹是否存在,不存在就创建
// example: /home/root/mkdir/1/2/3/4/
static bool mkdirs(const std::string &directoryPath)
{
    uint32_t dirPathLen = directoryPath.length();
    if (dirPathLen > MAX_PATH_LEN)
    {
        return false;
    }
    char tmpDirPath[MAX_PATH_LEN] = { 0 };
    for (uint32_t i = 0; i < dirPathLen; ++i)
    {
        tmpDirPath[i] = directoryPath[i];
        if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/' || i==dirPathLen-1)
        {
            if (ACCESS(tmpDirPath, 0) != 0)
            {
                int32_t ret = MKDIR(tmpDirPath);
                if (ret != 0)
                {
                    return false;
                }
            }
            else
            {
                std::cout << "目录: " << tmpDirPath << " 已存在" << std::endl;
            }
        }
    }
    return true;
}

#endif //RING_MKDIRS_H
