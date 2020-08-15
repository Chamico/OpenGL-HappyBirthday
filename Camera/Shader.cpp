#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	ifstream vertexFile;
	ifstream fragmentFile;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) {
			throw exception("open file error");
		}


		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();


		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		CheckCompilErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		CheckCompilErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		CheckCompilErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
}

void Shader::Use() {

	glUseProgram(ID);
}

void Shader::CheckCompilErrors(unsigned int ID, string type) {

	int success;
	char infLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, infLog);
			cout << "Shader compile error: " << infLog << endl;
		}
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infLog);
			cout << "program linking error: " << infLog << endl;
		}
	}
}