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

// Variables Globales
float GLOBAL_Tz = 0.f;
float GLOBAL_Fov = 35.0f;
float GLOBAL_Rc = 2.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	if (action == GLFW_REPEAT || action == GLFW_PRESS)
		switch (key)
		{
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_0: GLOBAL_Fov += 1.f;
			break;
		case GLFW_KEY_1: GLOBAL_Fov -= 1.f;
			break;
		case GLFW_KEY_UP: GLOBAL_Rc -= 0.025f;
			break;
		case GLFW_KEY_DOWN: GLOBAL_Rc += 0.025f;
			break;
		}

}

GLfloat f_esfera(float x)
{
	//return 0.25f;
	return (GLfloat)sqrt(0.0625f - (x - 0.5f) * (x - 0.5f));
}

void f_normal_esfera(float * normal, float * v)
{
	float dx = *v - 0.5;
	float dy = *(v + 1);
	float dz = *(v + 2);

	float norma = sqrt(dx * dx + dy * dy + dz * dz);

	*normal = dx / norma;
	*(normal + 1) = dy / norma;
	*(normal + 2) = dz / norma;

}

GLfloat f_cilindro(float x)
{
	return (GLfloat) 0.05f;
}

void f_normal_cilindro(float * normal, float * v)
{
	float dx = 0;
	float r = sqrt((*(v + 1)) * (*(v + 1)) + (*(v + 2)) * (*(v + 2)));
	float dy = *(v + 1) / r;
	float dz = *(v + 2) / r;

	float norma = sqrt(dx * dx + dy * dy + dz * dz);

	*normal = dx / norma;
	*(normal + 1) = dy / norma;
	*(normal + 2) = dz / norma;

}



GLfloat f_cono(float x)
{
	return (GLfloat)(0.5f * (x - 0.25f));
}




void inyectaSolidoDeRevolucionAlambre(GLfloat f(float x), GLfloat color[])
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

void inyectaSolidoDeRevolucion(GLfloat f(float x), void f_normal(float*, float*), GLfloat color[])
{
	GLenum modo = GL_TRIANGLES;
	// ------------------------
	//          Material
	// ------------------------
	const GLfloat model_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat model_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //{ 0.6f, 0.6f, 0.6f, 1.0f };
	const GLfloat model_shininess = 10.0f;

	glBegin(modo);

	// Set model material (used for perspective view, lighting enabled)
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, model_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, model_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, model_shininess);
	// ------------------------
	float x, fx, y, z, deltaX, x0 = 0.25f, x1 = 0.75f;
	float t, deltaT;
	float *p_ant, *p, *p_temp, *normales, *normales_ant;
	int k, j, m = 50, n = 20;
	deltaX = (x1 - x0) / n;
	deltaT = 6.2832f / m;

	p_ant = (float*)malloc(3 * (m + 1) * sizeof(float));
	p = (float*)malloc(3 * (m + 1) * sizeof(float));

	normales_ant = (float*)malloc(3 * (m + 1) * sizeof(float));
	normales = (float*)malloc(3 * (m + 1) * sizeof(float));

	if (!p_ant || !p || !normales_ant || !normales)
	{
		printf("Fracasó por falta de memoria al inyectar un Sólido de Revolución...\n");
		exit(1);
	}

	for (k = 0; k <= n; k++)
	{
		x = x0 + k * deltaX;
		fx = f(x);

		//glColor3f(color[0], color[1], color[2]);

		for (j = 0; j <= m; j++)
		{
			t = j * deltaT;
			y = fx * cosf(t);
			z = fx * sinf(t);

			p[3 * j] = x;
			p[3 * j + 1] = y;
			p[3 * j + 2] = z;

			f_normal(&normales[3 * j], &p[3 * j]);
		}

		if (k == 1) // tapa inicial, como pirámide m-gonal
		{
			for (j = 0; j < m; j++)
			{
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glVertex3f(p_ant[0], p_ant[1], p_ant[2]);

				glNormal3f(normales[3 * (j + 1) + 0], normales[3 * (j + 1) + 1], normales[3 * (j + 1) + 2]);
				glVertex3f(p[3 * (j + 1) + 0], p[3 * (j + 1) + 1], p[3 * (j + 1) + 2]);

				glNormal3f(normales[3 * j + 0], normales[3 * j + 1], normales[3 * j + 2]);
				glVertex3f(p[3 * j + 0], p[3 * j + 1], p[3 * j + 2]);
			}
		}

		if (k == n) // tapa final, como pirámide m-gonal
		{
			for (j = 0; j < m; j++)
			{
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3f(p[0], p[1], p[2]);

				glNormal3f(normales_ant[3 * j + 0], normales_ant[3 * j + 1], normales_ant[3 * j + 2]);
				glVertex3f(p_ant[3 * j + 0], p_ant[3 * j + 1], p_ant[3 * j + 2]);

				glNormal3f(normales_ant[3 * (j + 1) + 0], normales_ant[3 * (j + 1) + 1], normales_ant[3 * (j + 1) + 2]);
				glVertex3f(p_ant[3 * (j + 1) + 0], p_ant[3 * (j + 1) + 1], p_ant[3 * (j + 1) + 2]);

			}
		}


		if (k > 1 && k < n)
		{
			for (j = 0; j < m; j++)
			{
				//glVertex3f(p[3 * j + 0], p[3 * j + 1], p[3 * j + 2]);
				//glVertex3f(p_ant[3 * j + 0], p_ant[3 * j + 1], p_ant[3 * j + 2]);

				// normal punto "0"
				glNormal3f(normales[3 * j + 0], normales[3 * j + 1], normales[3 * j + 2]);
				// vértice punto "0" (p[j])
				glVertex3f(p[3 * j + 0], p[3 * j + 1], p[3 * j + 2]);

				// normal punto "1"
				glNormal3f(normales_ant[3 * j + 0], normales_ant[3 * j + 1], normales_ant[3 * j + 2]);
				// vértice punto "1" (p_ant[j])
				glVertex3f(p_ant[3 * j + 0], p_ant[3 * j + 1], p_ant[3 * j + 2]);

				// normal punto "2"
				glNormal3f(normales_ant[3 * (j + 1) + 0], normales_ant[3 * (j + 1) + 1], normales_ant[3 * (j + 1) + 2]);
				// vértice punto "2" (p_ant[j+1])
				glVertex3f(p_ant[3 * (j + 1) + 0], p_ant[3 * (j + 1) + 1], p_ant[3 * (j + 1) + 2]);

				// normal punto "2"
				glNormal3f(normales_ant[3 * (j + 1) + 0], normales_ant[3 * (j + 1) + 1], normales_ant[3 * (j + 1) + 2]);
				// vértice punto "2" (p_ant[j+1])
				glVertex3f(p_ant[3 * (j + 1) + 0], p_ant[3 * (j + 1) + 1], p_ant[3 * (j + 1) + 2]);

				// normal punto "3"
				glNormal3f(normales[3 * (j + 1) + 0], normales[3 * (j + 1) + 1], normales[3 * (j + 1) + 2]);
				// vértice punto "3" (p[j+1])
				glVertex3f(p[3 * (j + 1) + 0], p[3 * (j + 1) + 1], p[3 * (j + 1) + 2]);

				// normal punto "0"
				glNormal3f(normales[3 * j + 0], normales[3 * j + 1], normales[3 * j + 2]);
				// vértice punto "0" (p[j])
				glVertex3f(p[3 * j + 0], p[3 * j + 1], p[3 * j + 2]);
			}

		}
		// paso la rodaja actual a la rodaja anterior sin perder los lugares.
		p_temp = p;
		p = p_ant;
		p_ant = p_temp;

		p_temp = normales;
		normales = normales_ant;
		normales_ant = p_temp;

	}
	glEnd();
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


void inyectaOtroPoliedro()
{
	const GLfloat model_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat model_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //{ 0.6f, 0.6f, 0.6f, 1.0f };
	const GLfloat model_shininess = 10.0f;
	int k, ki, kp;
	float coordenadas[21] = {
		0.5f,  0.0f,  0.5f, //Vértice superior de la pirámide
		0.2f,  0.3f,  0.0f, // Vértice 1
		0.2f, -0.3f,  0.0f, // Vértice 2
		0.8f, -0.3f,  0.0f, // Vértice 3
		0.8f,  0.3f,  0.0f, // Vértice 4
		0.5f,  0.0f,  0.0f }; // Origen base

	GLenum modo = GL_TRIANGLE_FAN;
	glBegin(modo);
	// Set model material (used for perspective view, lighting enabled)
	glMaterialfv(GL_FRONT, GL_DIFFUSE, model_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, model_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, model_shininess);

	vec3 origen_base;
	origen_base[0] = coordenadas[15];
	origen_base[1] = coordenadas[16];
	origen_base[2] = coordenadas[17];

	vec3 origen;
	origen[0] = coordenadas[0];
	origen[1] = coordenadas[1];
	origen[2] = coordenadas[2];

	vec3 actual, siguiente, siguienteMenosOrigenBase, origenMenosActual, vecNormal;

	glNormal3f(0.f, 0.f, 1.f);
	glVertex3f((GLfloat)origen[0], (GLfloat)origen[1], (GLfloat)origen[2]);


	for (ki = 0; ki <= 4; ki++)
	{
		k = 1 + ki % 4;
		actual[0] = coordenadas[3 * k];
		actual[1] = coordenadas[3 * k + 1];
		actual[2] = coordenadas[3 * k + 2];

		siguiente[0] = coordenadas[3 * (k + 1)];
		siguiente[1] = coordenadas[3 * (k + 1) + 1];
		siguiente[2] = coordenadas[3 * (k + 1) + 2];

		vec3_sub(siguienteMenosOrigenBase, siguiente, origen_base);
		vec3_sub(origenMenosActual, origen, actual);

		vec3_mul_cross(vecNormal, siguienteMenosOrigenBase, origenMenosActual);
		vec3_norm(vecNormal, vecNormal);

		glNormal3f((GLfloat)vecNormal[0], (GLfloat)vecNormal[1], (GLfloat)vecNormal[2]);
		glVertex3f((GLfloat)actual[0], (GLfloat)actual[1], (GLfloat)actual[2]);
	}
	glEnd();

	const GLfloat model_diffuse_tapa[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat model_specular_tapa[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //{ 0.6f, 0.6f, 0.6f, 1.0f };
	const GLfloat model_shininess_tapa = 10.0f;

	// tapa

	glBegin(GL_QUADS);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, model_diffuse_tapa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, model_specular_tapa);
	glMaterialf(GL_FRONT, GL_SHININESS, model_shininess_tapa);


	// punto 1
	kp = 3 * 1;
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((GLfloat)coordenadas[kp], (GLfloat)coordenadas[kp + 1], (GLfloat)coordenadas[kp + 2]);

	// punto 4
	kp = 3 * 4;
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((GLfloat)coordenadas[kp], (GLfloat)coordenadas[kp + 1], (GLfloat)coordenadas[kp + 2]);

	// punto 3
	kp = 3 * 3;
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((GLfloat)coordenadas[kp], (GLfloat)coordenadas[kp + 1], (GLfloat)coordenadas[kp + 2]);

	// punto 2
	kp = 3 * 2;
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((GLfloat)coordenadas[kp], (GLfloat)coordenadas[kp + 1], (GLfloat)coordenadas[kp + 2]);

	glEnd();
}

void inyectaOtroOtroPoliedro() // vectores normales para caras planas
{
	const GLfloat model_diffuse[4] = { 1.0f, 0.1f, 0.1f, 1.0f };
	const GLfloat model_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //{ 0.6f, 0.6f, 0.6f, 1.0f };
	const GLfloat model_shininess = 10.0f;
	int k, ki, kp;
	float coordenadas[18] = {
		0.5f,  0.0f,  0.5f, //Vértice superior de la pirámide
		0.2f,  0.3f,  0.0f, // Vértice 1
		0.2f, -0.3f,  0.0f, // Vértice 2
		0.8f, -0.3f,  0.0f, // Vértice 3
		0.8f,  0.3f,  0.0f, // Vértice 4
		0.2f,  0.3f,  0.0f }; //Repito el Vértice 1

	GLenum modo = GL_TRIANGLES;
	glBegin(modo);
	// Set model material (used for perspective view, lighting enabled)
	glMaterialfv(GL_FRONT, GL_DIFFUSE, model_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, model_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, model_shininess);

	vec3 origen_base;
	origen_base[0] = coordenadas[15];
	origen_base[1] = coordenadas[16];
	origen_base[2] = coordenadas[17];

	vec3 origen;
	origen[0] = coordenadas[0];
	origen[1] = coordenadas[1];
	origen[2] = coordenadas[2];

	vec3 actual, siguiente, siguienteMenosOrigen, actualMenosOrigen, vecNormal;

    // cada cara es un triángulo

	for (ki = 0; ki < 4; ki++)
	{
		k = 1 + ki % 4;
		actual[0] = coordenadas[3 * k];
		actual[1] = coordenadas[3 * k + 1];
		actual[2] = coordenadas[3 * k + 2];

		siguiente[0] = coordenadas[3 * (k + 1)];
		siguiente[1] = coordenadas[3 * (k + 1) + 1];
		siguiente[2] = coordenadas[3 * (k + 1) + 2];

		vec3_sub(actualMenosOrigen, actual, origen); 
		vec3_sub(siguienteMenosOrigen, siguiente, origen);
		
		vec3_mul_cross(vecNormal, actualMenosOrigen, siguienteMenosOrigen);
		vec3_norm(vecNormal, vecNormal);

		glNormal3f((GLfloat)vecNormal[0], (GLfloat)vecNormal[1], (GLfloat)vecNormal[2]);
		glVertex3f((GLfloat)origen[0], (GLfloat)origen[1], (GLfloat)origen[2]);

		glNormal3f((GLfloat)vecNormal[0], (GLfloat)vecNormal[1], (GLfloat)vecNormal[2]);
		glVertex3f((GLfloat)actual[0], (GLfloat)actual[1], (GLfloat)actual[2]);

		glNormal3f((GLfloat)vecNormal[0], (GLfloat)vecNormal[1], (GLfloat)vecNormal[2]);
		glVertex3f((GLfloat)siguiente[0], (GLfloat)siguiente[1], (GLfloat)siguiente[2]);
	}
	glEnd();

	const GLfloat model_diffuse_tapa[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat model_specular_tapa[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //{ 0.6f, 0.6f, 0.6f, 1.0f };
	const GLfloat model_shininess_tapa = 10.0f;

	// tapa

	glBegin(GL_QUADS);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, model_diffuse_tapa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, model_specular_tapa);
	glMaterialf(GL_FRONT, GL_SHININESS, model_shininess_tapa);


	// punto 1
	kp = 3 * 1;
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((GLfloat)coordenadas[kp], (GLfloat)coordenadas[kp + 1], (GLfloat)coordenadas[kp + 2]);

	// punto 4
	kp = 3 * 4;
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((GLfloat)coordenadas[kp], (GLfloat)coordenadas[kp + 1], (GLfloat)coordenadas[kp + 2]);

	// punto 3
	kp = 3 * 3;
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((GLfloat)coordenadas[kp], (GLfloat)coordenadas[kp + 1], (GLfloat)coordenadas[kp + 2]);

	// punto 2
	kp = 3 * 2;
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((GLfloat)coordenadas[kp], (GLfloat)coordenadas[kp + 1], (GLfloat)coordenadas[kp + 2]);

	glEnd();
}

void luces()
{
	float d = 3.0f;

	const GLfloat light_position0[4] = { 0.5f, 0.866f * d, -0.5f * d, 1.0f };
	const GLfloat light_diffuse0[4] = { 0.0f, 0.0f, 1.0f, 1.0f };   // azul
	const GLfloat light_specular0[4] = { 0.5f, 0.5f, 0.5f, 1.0f };  // charolazos blancos
	const GLfloat light_ambient0[4] = { 0.0f, 0.0f, 1.0f, 1.0f };   // ambiental azul

	const GLfloat light_position1[4] = { 0.5f, -0.866f * d, -0.5f * d, 1.0f };
	const GLfloat light_diffuse1[4] = { 1.0f, 0.0f, 0.0f, 1.0f };  // roja
	const GLfloat light_specular1[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // charolazo blanco
	const GLfloat light_ambient1[4] = { 0.25f, 0.0f, 0.0f, 1.0f };  // ambiente rojo

	const GLfloat light_position2[4] = { 0.5f, 0.0f, d, 1.0f };
	const GLfloat light_diffuse2[4] = { 0.0f, 1.0f, 0.0f, 1.0f };  // verde
	const GLfloat light_specular2[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // charolazo blanco
	const GLfloat light_ambient2[4] = { 0.0f, 0.25f, 0.0f, 1.0f };  // ambiente verde

	const GLfloat light_position3[4] = { -1.0 * d , 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse3[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // blanca
	const GLfloat light_specular3[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // charolazo blanco
	const GLfloat light_ambient3[4] = { 0.25f, 0.25f, 0.25f, 1.0f };  // ambiente blanco


	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
	glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
	GLfloat spot_dir[3] = { 1.0f,0.0f,0.0f };
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_dir);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 90.0f);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular3);
	glEnable(GL_LIGHT3);

	glEnable(GL_LIGHTING);
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

		float Rc, x_eye, y_eye, z_eye, T, theta;

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

		//  ======================= PROYECCION =============================

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Enable face culling (faster rendering)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_NORMALIZE);
		//glEnable(GL_DEPTH_TEST);

		vec3 eye; //= { 0.0f,0.0f,0.125f};
		vec3 target = { 0.0f,0.0f,-2.5f };
		vec3 up = { 0.0f,1.0f,0.0f };

		Rc = 2.0f;
		T = 10.0F; // en "segundos"
		theta = 6.2832 / T * tiempo_t;
		x_eye = GLOBAL_Rc * sinf(theta);
		y_eye = sinf(0.5f * tiempo_t);
		z_eye = GLOBAL_Rc * cosf(theta) - 2.5f;

		eye[0] = x_eye;
		eye[1] = y_eye;
		eye[2] = z_eye;


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4 Rview, Rat, Rp;
		mat4x4_look_at(Rat, eye, target, up);
		mat4x4_perspective(Rp, (float)(GLOBAL_Fov*3.1416 / 180.0), 800.0f / 600.0f, 0.2f, 100.0f);
		mat4x4_mul(Rview, Rp, Rat);
		glMultMatrixf(Rp);
		//luces();
		glMultMatrixf(Rat);

		luces();

		//  ======================= MODELO =============================
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

		inyectaPoliedro();
		//inyectaOtroPoliedro();
		//inyectaOtroOtroPoliedro();
		//inyectaSolidoDeRevolucionAlambre(&f_cilindro, blanco);
		//inyectaSolidoDeRevolucionAlambre(&f_cono, verde);
		
		inyectaSolidoDeRevolucion(&f_esfera, &f_normal_esfera, rojo);
		//inyectaSolidoDeRevolucion(&f_cilindro, &f_normal_cilindro, rojo);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//! [code]
