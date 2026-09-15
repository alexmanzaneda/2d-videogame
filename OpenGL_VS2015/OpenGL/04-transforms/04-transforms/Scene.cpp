#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"


Scene::Scene()
{
	quad = NULL;
}

Scene::~Scene()
{
	if(quad != NULL)
		delete quad;
}


void Scene::init()
{
	initShaders();
	quad = Quad::createQuad(0.f, 0.f, 128.f, 128.f, program);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH), float(CAMERA_HEIGHT), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Scene::render()
{
	glm::mat4 modelview;

	// We can now, using matrices, draw four quads at different screen locations
	// using a single Quad object.
	program.use();
	program.setUniformMatrix4f("projection", projection);
	program.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	// 1. Oscilación entre 0.0 (izquierda) y 1.0 (derecha)
	float factor = (sin(currentTime / 1000.f) + 1.0f) / 2.0f;

	// 2. Desplazamiento máximo en X (ej: 200 píxeles hacia la derecha)
	float movimientoX = factor * 200.0f;

	// 3. Escala progresiva: 1.0f cuando factor es 0, 0.25f cuando factor es 1
	float escala = 1.0f - (0.75f * factor);

	// --- PRIMER QUAD ---
	float startX = 128.f;
	float startY = 48.f;

	// Aplicamos de ABAJO hacia ARRIBA

	// C: Movemos el quad a su posición final en la pantalla + el desplazamiento animado
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(startX + movimientoX, startY, 0.f));

	// B2: Devolvemos el centro a su sitio
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	// B1: Aplicamos la escala
	modelview = glm::scale(modelview, glm::vec3(escala, escala, 1.0f));
	// B0: Movemos el quad para que su centro quede en (0,0)
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));

	program.setUniformMatrix4f("modelview", modelview);
	quad->render();

	// --- SEGUNDO QUAD ---
	startX = 384.f;
	startY = 48.f;

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(startX + movimientoX, startY, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(escala, escala, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));

	program.setUniformMatrix4f("modelview", modelview);
	quad->render();

	// --- TERCER QUAD ---
	startX = 128.f;
	startY = 304.f;

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(startX + movimientoX, startY, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(escala, escala, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));

	program.setUniformMatrix4f("modelview", modelview);
	quad->render();

	// --- CUARTO QUAD ---
	startX = 384.f;
	startY = 304.f;

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(startX + movimientoX, startY, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(escala, escala, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));

	program.setUniformMatrix4f("modelview", modelview);
	quad->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.link();
	if(!program.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << program.log() << endl << endl;
	}
	program.bindFragmentOutput("outColor");
}

