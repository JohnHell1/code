#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<sstream>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
int setShader(string,string,unsigned int);


float vertexx[] = {
	0.5f,0.5f,0.0f,
	-0.5f,0.0f,0.0f,
	0.0f,0.5f,0.0f


};
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
unsigned int indicies[] = {
	0,1,2

};
int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* mywindow = glfwCreateWindow(800, 800, "mywindow", NULL, NULL);
	glfwMakeContextCurrent(mywindow);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return 0;
	}
	unsigned int program;
	program = glCreateProgram();
	int check = setShader("vshader.glsl", "fshader.glsl", program);

	if (check == -1) {
		printf("CompileError");
		return -2;

	}

	glfwSetFramebufferSizeCallback(mywindow,framebuffer_size_callback);
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(VBO, sizeof(vertexx), &vertexx, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(EBO,sizeof(indicies), &indicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(mywindow)) {


		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(mywindow);
	}
	glfwTerminate();
	return 1;
}

int setShader(string vshaderfile,string fshaderfile,unsigned int myprog) {

	unsigned int vertexshader;
	unsigned int fragmentshader;

	ifstream vreader;
	ifstream freader;

	stringstream fsstream, vsstream;
	fsstream << freader.rdbuf();
	vsstream << vreader.rdbuf();
	vreader.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	freader.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
	// open files
	vreader.open(vshaderfile.c_str());
	freader.open(fshaderfile.c_str());
	std::stringstream vShaderStream, fShaderStream;
	// read file’s buffer contents into streams
	vShaderStream << vreader.rdbuf();
	fShaderStream << freader.rdbuf();
	// close file handlers
	vreader.close();
	freader.close();
	// convert stream into string
	}
	catch(std::ifstream::failure e)
	{
	std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	string vshadersources = vsstream.str();
	string fshadersources = fsstream.str();
	const char* vshadersource = vshadersources.c_str();
	const char* fshadersource = fshadersources.c_str();
	cout << vshadersources;

	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader,1 , &vshadersource, NULL);
	glCompileShader(vertexshader);
	
	int success;
	char infoLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
		printf("%s", infoLog);
		return -1;
	}
	
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fshadersource, NULL);
	glCompileShader(fragmentshader);
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
		printf("%s", infoLog);
		return -1;
	}


	glAttachShader(myprog, vertexshader);
	glAttachShader(myprog, fragmentshader);
	glLinkProgram(myprog);

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	return 0;



}