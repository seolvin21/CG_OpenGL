#pragma once
#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm/glm.hpp>
#include <gl/glm/glm/ext.hpp>
#include <gl/glm/glm/gtc/matrix_transform.hpp>

#pragma comment(lib, "winmm");
#include <mmsystem.h>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

#define SOUND_FILE_FAILED "../sound/failed.wav"
#define SOUND_FILE_SUCCESS "../sound/success.wav"
#define SOUND_FILE_BGM "../sound/BGM_SV_Mines.wav"

#define WIDTH 800
#define HEIGHT 600

