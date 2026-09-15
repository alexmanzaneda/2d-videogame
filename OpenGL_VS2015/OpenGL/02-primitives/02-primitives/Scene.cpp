#include <iostream>
#include "Scene.h"
#include "Game.h"


Scene::Scene()
{
	for(int i = 0; i < 4; i++)
		quads[i] = NULL;

	// Added
	circle = NULL;
	circleScene = false;
}

Scene::~Scene()
{
	for(int i = 0; i < 4; i++)
		if(quads[i] != NULL)
			delete quads[i];

	// Added
	if(circle != NULL)
		delete circle;
}


void Scene::init()
{
	initShaders();

	for(int i = 0; i < 4; i++)
		quads[i] = Quad::createQuad(-0.75f + (i % 2), -0.75f + (i / 2), 0.5f, 0.5f, program);

	// Added
	circleScene = false;
	circle = Circle::createCircle(0.0f, 0.0f, 0.5f, 50, program);
}

// Added
void Scene::update(int deltaTime)
{
	// Si se pulsa la tecla 'C', mostramos el círculo
	if (Game::instance().getKey('c') || Game::instance().getKey('C')) {
		circleScene = true;
	}
	// Si se pulsa la tecla 'Q', mostramos los cuadrados
	if (Game::instance().getKey('q') || Game::instance().getKey('Q')) {
		circleScene = false;
	}
}

void Scene::render()
{
	program.use();

	// Added
	if (circleScene) {
		circle->render();
	}
	else {
		for (int i = 0; i < 4; i++)
			quads[i]->render();
	}
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

