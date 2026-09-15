#ifndef _CIRCLE_INCLUDE
#define _CIRCLE_INCLUDE

#include "ShaderProgram.h"

// Clase que encapsula la geometría y el renderizado de un círculo 2D.

class Circle
{
public:
	// Crea un círculo dinámicamente (patrón fábrica).
	// x, y: posición del centro en coordenadas de mundo/ventana.
	// radius: radio del círculo.
	// segments: número de segmentos usados para aproximar el círculo (mayor => más suave).
	// program: referencia al shader program que se usará para renderizar.
	static Circle* createCircle(float x, float y, float radius, int segments, ShaderProgram& program);

	// Constructor: inicializa la geometría y configura los buffers/atributos.
	Circle(float x, float y, float radius, int segments, ShaderProgram& program);

	// Dibuja el círculo usando el VAO/VBO y el shader previamente configurado.
	void render() const;

	// Libera los recursos GPU (buffers, VAO) asociados al círculo.
	// Debe llamarse antes de destruir el programa o cuando ya no se necesite el objeto.
	void free();

private:
	GLuint vao;        // Vertex Array Object: configura el formato de los datos de vértice
	GLuint vbo;        // Vertex Buffer Object: contiene las posiciones de los vértices
	GLint posLocation; // Localización del atributo de posición en el shader
	int numVertices;   // Número total de vértices usados para dibujar el círculo
};

#endif // _CIRCLE_INCLUDE
