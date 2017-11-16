//========================================================================
// Simple GLFW example
// Copyright (c) Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
//! [code]

#include <GLFW/glfw3.h>
#include <linmath.h>

#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

// Variable Global
float GLOBAL_Tz  = 0.f;
float GLOBAL_Fov = 35.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	if(action == GLFW_PRESS)
		switch (key)
		{
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_0: GLOBAL_Fov += 1.f;
			break;
		case GLFW_KEY_1: GLOBAL_Fov -= 1.f;

		}
		
}

GLfloat f_esfera(float x)
{
	//return 0.25f;
	return (GLfloat)sqrt(0.0625f - (x - 0.5f) * (x - 0.5f));
}

GLfloat f_cilindro(float x)
{
	return (GLfloat) 0.05f;
}

GLfloat f_cono(float x)
{
	return (GLfloat)(0.5f * (x - 0.25f));
}



void inyectaSolidoDeRevolucion(GLfloat f(float x), GLfloat color[])
{
	GLenum modo = GL_LINE_LOOP;

	float x, fx, y, z, deltaX, x0 = 0.25f, x1 = 0.75f;
	float t, deltaT;
	float *p_ant, *p, *p_temp;
	int k, j, m = 25, n = 10;
	deltaX = (x1 - x0) / n;
	deltaT = 6.2832f / m;

	p_ant = (float*)malloc(3 * (m + 1) * sizeof(float));
	p = (float*)malloc(3 * (m + 1) * sizeof(float));

	if (!p_ant || !p)
	{
		printf("Fracasó por falta de memoria al inyectar un Sólido de Revolución...\n");
		exit(1);
	}

	for (k = 0; k <= n; k++)
	{
		x = x0 + k * deltaX;
		fx = f(x);

		glBegin(modo);
		glColor3f(color[0], color[1], color[2]);

		for (j = 0; j <= m; j++)
		{
			t = j * deltaT;
			y = fx * cosf(t);
			z = fx * sinf(t);

			p[3 * j] = x;
			p[3 * j + 1] = y;
			p[3 * j + 2] = z;

			glVertex3f(x, y, z);
		}
		glEnd();

		if (k > 0)
		{
			glBegin(modo);
			for (j = 0; j < m; j++)
			{
				glVertex3f(p[3 * j + 0], p[3 * j + 1], p[3 * j + 2]);
				glVertex3f(p_ant[3 * j + 0], p_ant[3 * j + 1], p_ant[3 * j + 2]);
			}
			glEnd();
		}
		// paso la rodaja actual a la rodaja anterior sin perder los lugares.
		p_temp = p;
		p = p_ant;
		p_ant = p_temp;
	}
	// libero la memoria
	free(p);
	free(p_ant);
}


void inyectaPoliedro()
{
	GLenum modo = GL_LINE_LOOP;
	/*
	// CARA I (FRONT)
	glBegin(modo);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	
	glVertex3f(-0.5f, 0.5f, 0.5f);
	
	glVertex3f(-0.5f, -0.5f, 0.5f);
	
	glVertex3f(0.5f, -0.5f, 0.5f);
	
	//glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	// CARA II (REAR)
	glBegin(modo);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	//glColor3f(0.f, 1.f, 0.f);
	//glVertex3f(0.5f, 0.5f, -0.5f);

	glEnd();
*/
	// CARA III (TOP)
	glBegin(modo);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	// CARA IV (BOTTOM)
	glBegin(modo);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.5f);	
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();

/*
	// CARA V (LEFT)
	glBegin(modo);
	glColor3f(0.f, 1.f, 1.f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	//glColor3f(0.f, 1.f, 1.f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	//glColor3f(0.f, 1.f, 1.f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	//glColor3f(0.f, 1.f, 1.f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	//glColor3f(0.f, 1.f, 1.f);
	//glVertex3f(0.5f, 0.5f, 0.5f);

	glEnd();

	// CARA VI (RIGHT)
	glBegin(modo);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	//glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	//glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	//glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	//glColor3f(1.f, 1.f, 1.f);
	//glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();
*/
	// FIN DEL POLIEDRO
}


int main(void)
{
	GLFWwindow* window;
	mat4x4 Rid, Rx, Ry, Rz, Rtot;
	mat4x4 Sxyz, Tx, Txloc, Rzloc;


	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, key_callback);

	float alfa_z = 0.f;
	float fk = 0.1f;

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
			
		float tiempo_t;
		float radX, radY, radZ;
		int width, height;

		float blanco[] = { 1.f, 1.f, 1.f };
		float rojo[] = { 1.f, 0.f, 0.f };
		float verde[] = { 0.f, 1.f, 0.f };
		float azul[] = { 0.f, 0.f, 1.f };

		tiempo_t = (float)glfwGetTime();
		radX = tiempo_t * 10.0f * 3.14159f / 180.f;
		radY = tiempo_t * 20.0f * 3.14159f / 180.f;
		radZ = tiempo_t * 30.0f * 3.14159f / 180.f;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//  ====================================================

		vec3 eye = { 0.0f,0.0f,0.125f};
		vec3 target = {0.0f,0.0f,0.0f};
		vec3 up = {0.0f,1.0f,0.0f};

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4 Rview,Rat,Rp;
		mat4x4_look_at(Rat, eye, target, up);
		mat4x4_perspective(Rp, (float)(GLOBAL_Fov*3.1416 / 180.0), 800.0f/600.0f, 0.2f, 100.0f);
		mat4x4_mul(Rview, Rp, Rat);
		glMultMatrixf(Rview);

		//  ====================================================
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		//glRotatef( tiempo_t * 50.f, 1.f, 0.f, 0.f);

		mat4x4_identity(Rid);
		mat4x4_rotate_X(Rx, Rid, radX);

		mat4x4_rotate_Y(Ry, Rid, radY);

		alfa_z += fk * GLOBAL_Tz * 3.14159f / 180.f;
		mat4x4_rotate_Z(Rz, Rid, alfa_z);
		
		//mat4x4_mul(Rtot, Ry, Rx);
		//mat4x4_mul(Rtot, Rz, Rtot);
		//mat4x4_mul(Rtot, Tx, Ry );
		//mat4x4_mul(Rtot, Sxyz, Rtot);

		mat4x4_rotate_Z(Rzloc, Rid, 4.f*radZ);
		mat4x4_translate(Txloc, -0.5f, 0.f, 0.f);

		mat4x4_scale_aniso(Sxyz, Rid, 0.25, 0.25, 0.25);
		mat4x4_translate(Tx, 0.75f, 0.f, 0.f);

		mat4x4_mul(Rtot, Txloc, Rid);
		mat4x4_mul(Rtot, Sxyz, Rtot);
		//mat4x4_mul(Rtot, Rzloc, Rtot);
		mat4x4_mul(Rtot, Ry, Rtot);
		mat4x4_mul(Rtot, Tx, Rtot);
		mat4x4_mul(Rtot, Rz, Rtot);


		glMultMatrixf(Txloc);

		mat4x4 Tzv;
		mat4x4_translate(Tzv, 0.f, 0.f, -2.5f);
		glMultMatrixf(Tzv);
		//glMultMatrixf(Rtot);

	/*	
		glMultMatrixf(Rz);
		glMultMatrixf(Tx);
		glMultMatrixf(Sxyz);
		glMultMatrixf(Rzloc);
		glMultMatrixf(Ry);
		glMultMatrixf(Rx);
		glMultMatrixf(Txloc);
	*/	

		/*
		glBegin(GL_POLYGON);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glColor3f(0.f, 1.0f, 0.f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glColor3f(1.f, 1.f, 1.f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		//glColor3f(1.f, 0.f, 0.f);
		//glVertex3f(0.5f, 0.5f, 0.5f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glColor3f(0.f, 1.0f, 0.f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glColor3f(1.f, 1.f, 1.f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		//glColor3f(1.f, 0.f, 0.f);
		//glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
		*/

		inyectaPoliedro();

		inyectaSolidoDeRevolucion(&f_cilindro, blanco);
		inyectaSolidoDeRevolucion(&f_cono, verde);
		inyectaSolidoDeRevolucion(&f_esfera, rojo);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//! [code]
