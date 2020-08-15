#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::exception;
using std::stringstream;
using std::string;

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	string vertexString;
	string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;	// Shader Program ID

	void Use();

private:
	void CheckCompilErrors(unsigned int ID, string type);
};

