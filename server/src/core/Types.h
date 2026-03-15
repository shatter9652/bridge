// LCEServer — Core type definitions
// Standalone types so we don't drag in the full LCE stdafx.h
#pragma once

#define _HAS_STD_BYTE 0
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include <cstdint>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <atomic>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cassert>
