#include <GL/glew.h>
#include <GL/gl.h>
#include "Circle.h"
#include <cmath>
#include <vector>

// Definimos PI si no viene por defecto
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Circle* Circle::createCircle(float x, float y, float radius, int segments, ShaderProgram& program)
{
	Circle* circle = new Circle(x, y, radius, segments, program);
	return circle;
}

Circle::Circle(float x, float y, float radius, int segments, ShaderProgram& program)
{
	// El número total de vértices es el centro + los puntos del borde + 1 para cerrar el círculo
	numVertices = segments + 2;
	std::vector<float> vertices(numVertices * 2); // Multiplicado por 2 porque cada vértice tiene (X, Y)

	// Vértice 0: El centro del círculo
	vertices[0] = x;
	vertices[1] = y;

	// Generamos los puntos del borde
	float angleStep = 2.0f * M_PI / segments;
	for (int i = 0; i <= segments; i++)
	{
		float angle = i * angleStep;
		// Índice en el array (saltamos el centro)
		int index = 2 + (i * 2);
		vertices[index] = x + radius * cos(angle);     // Coordenada X
		vertices[index + 1] = y + radius * sin(angle); // Coordenada Y
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Pasamos los datos del vector a la tarjeta gráfica
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2);
}

void Circle::render() const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	// Usamos GL_TRIANGLE_FAN en lugar de GL_TRIANGLES
	glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);
}

void Circle::free()
{
	glDeleteBuffers(1, &vbo);
}