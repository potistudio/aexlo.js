#pragma once

#include <iostream>

// void LogInfo (const char *msg) { std::cout << "\033[31m[INFO]\033[m " << msg << std::endl; }
// void LogWarning (const char *msg) { std::cout << "[WARNING] " << msg << std::endl; }

#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARNING 3
#define LOG_LEVEL_CRITICAL 4
#define LOG_LEVEL_NONE 5

#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif

#if LOG_LEVEL <= LOG_LEVEL_NONE
#define LOG_BORDER() std::cout << "----------------------------------------------------------------" << std::endl
#else
#define LOG_BORDER(...) (void) 0
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_DEBUG(msg) std::cout << "\033[34m<DEBUG>\033[m    " << msg << std::endl
#else
#define LOG_DEBUG(msg) (void )0
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(msg) std::cout << "\033[32m<INFO>\033[m     " << msg << std::endl
#else
#define LOG_INFO(msg) (void )0
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARNING
#define LOG_WARNING(msg) std::cout << "\033[33m<WARNING>\033[m  " << msg << std::endl
#else
#define LOG_WARNING(msg) (void )0
#endif

#if LOG_LEVEL <= LOG_LEVEL_CRITICAL
#define LOG_CRITICAL(msg) std::cout << "\033[31m<CRITICAL>\033[m " << msg << std::endl
#else
#define LOG_CRITICAL(...) (void) 0
#endif

#define LOG_CALL(name, ...)
