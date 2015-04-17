

#include "Asteroids.h"

float Asteroids::lerp(float v0, float v1, float t) {
	return (1.0f - t)*v0 + t*v1;
}

void Asteroids::DrawText(GLuint fontTexture, string text, float size, float spacing, float r, float g, float b, float a) {
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float texture_size = 1.0 / 16.0f;
	vector<float> vertexData;
	vector<float> texCoordData;
	vector<float> colorData;

	for (size_t i = 0; i < text.size(); i++) {
		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;

		colorData.insert(colorData.end(), { r, g, b, a, r, g, b, a, r, g, b, a, r, g, b, a });
		vertexData.insert(vertexData.end(), { ((size + spacing) * i) + (-0.5f* size), 0.5f* size, ((size + spacing) * i) + (-0.5f* size), -0.5f* size, ((size + spacing) * i) + (0.5f* size), -0.5f* size, ((size + spacing) * i) + (0.5f* size), 0.5f * size });
		texCoordData.insert(texCoordData.end(), { texture_x, texture_y, texture_x, texture_y + texture_size, texture_x + texture_size, texture_y + texture_size, texture_x + texture_size, texture_y });
	}

	glColorPointer(4, GL_FLOAT, 0, colorData.data());
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, text.size() * 4.0f);
	glDisableClientState(GL_COLOR_ARRAY);
}

float Asteroids::genRandomNum(float min, float max) {
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

Asteroids::Asteroids() {
	Init();
}

Asteroids::~Asteroids() {
	SDL_Quit();
}

void Asteroids::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33*2, 1.33*2, -1.0*2, 1.0*2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    done = false;
    lastFrameTicks = 0.0f;
    timeLeftOver = 0.0f;
    
    spriteSheetTexture = LoadTexture("sheet.png");
    fontSheetTexture = LoadTexture("pixel_font.png");
    
    state = STATE_GAME_LEVEL;

	SpriteSheet playerSprite = SpriteSheet(spriteSheetTexture, 425.0f / 1024.0f, 552.0f / 1024.0f, 93.0f / 1024.0f, 84.0f / 1024.0f);
	Entity* player = new Entity();
	player->sprite = playerSprite;
	player->scale_x = 1.0f;
	player->scale_y = 1.0f;
	player->x = 0.0f;
	player->y = 0.0f;
	player->friction_x = 3.0f;
	player->friction_y = 3.0f;
	entities.push_back(player);

	SpriteSheet asteroidSprite = SpriteSheet(spriteSheetTexture, 224.0f / 1024.0f, 664.0f / 1024.0f, 101.0f / 1024.0f, 84.0f / 1024.0f);
	for (int i = 0; i < 10; i++) {
		Entity* asteroid = new Entity();
		asteroid->sprite = asteroidSprite;
		float scale = genRandomNum(0.2f, 1.0f);
		asteroid->scale_x = scale;
		asteroid->scale_y = scale;

		asteroid->x = genRandomNum(-1.33f, 1.33f);
		asteroid->y = genRandomNum(-1.0f, 1.0f);

		asteroid->rotation = genRandomNum(-90.0f, 90.0f);

		asteroid->velocity_x = genRandomNum(-0.1f, 0.2f);
		asteroid->velocity_y = genRandomNum(-0.1f, 0.2f);
		entities.push_back(asteroid);
	}
}

void Asteroids::Update(float elapsed) {
	switch (state) {
	
	case STATE_GAME_LEVEL:
		updateGameLevel(elapsed);
		break;
	}
}

void Asteroids::updateGameLevel(float elapsed) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
	}
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) {
		entities[0]->velocity_x = 1.0f;
		entities[0]->velocity_y = 1.0f;
	}

	if (keys[SDL_SCANCODE_D]) {
		entities[0]->rotation -= 5.0f * elapsed;
	}
	else if (keys[SDL_SCANCODE_A]) {
		entities[0]->rotation += 5.0f * elapsed;
	}

	for (size_t i = 0; i < entities.size(); i++) {
		entities[i]->Update(elapsed);
	}
}

void Asteroids::FixedUpdate() {
	for (size_t i = 0; i < entities.size(); i++) {

		if (!entities[i]->isStatic) {
			for (size_t j = 0; j < entities.size(); j++) {
				if (entities[i] != entities[j])
					collision(entities[i], entities[j]);
			}
		}

	

		entities[i]->velocity_x = lerp(entities[i]->velocity_x, 0.0f, FIXED_TIMESTEP * entities[i]->friction_x);
		entities[i]->velocity_y = lerp(entities[i]->velocity_y, 0.0f, FIXED_TIMESTEP * entities[i]->friction_y);

		entities[i]->velocity_x += entities[i]->acceleration_x * FIXED_TIMESTEP;
		entities[i]->velocity_y += entities[i]->acceleration_y * FIXED_TIMESTEP;

		entities[i]->y += entities[i]->velocity_y * -cos(entities[i]->rotation) * FIXED_TIMESTEP;

		entities[i]->x += entities[i]->velocity_x * sin(entities[i]->rotation) * FIXED_TIMESTEP;
	}
}

void Asteroids::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	switch (state) {
	case STATE_GAME_LEVEL:
		renderGameLevel();
		break;
	}
	SDL_GL_SwapWindow(displayWindow);
}

void Asteroids::renderGameLevel() {
	glMatrixMode(GL_MODELVIEW);
	for (size_t i = 0; i < entities.size(); i++) {
		entities[i]->Render();
	}
}

bool Asteroids::UpdateAndRender() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > FIXED_TIMESTEP* MAX_TIMESTEPS) {
		fixedElapsed = FIXED_TIMESTEP* MAX_TIMESTEPS;
	}
	while (fixedElapsed >= FIXED_TIMESTEP) {
		fixedElapsed -= FIXED_TIMESTEP;
		FixedUpdate();
	}
	timeLeftOver = fixedElapsed;
	Update(elapsed);
	Render();
	return done;
}

bool Asteroids::collision(Entity* entity1, Entity* entity2) {
	entity1->buildMatrix();
	entity2->buildMatrix();

    float minA, maxA;
    Matrix inverseMatrix1 = entity1->matrix.inverse();
	Vector x1 = inverseMatrix1 * (entity2->matrix * entity2->TL);
	Vector x2 = inverseMatrix1 * (entity2->matrix * entity2->TR);
	Vector x3 = inverseMatrix1 * (entity2->matrix * entity2->BL);
	Vector x4 = inverseMatrix1 * (entity2->matrix * entity2->BR);
    
    minA = min(min(min(x1.x, x3.x), x2.x), x4.x);
    maxA = max(max(max(x1.x, x3.x), x2.x), x4.x);

    if (!(minA <= entity1->sprite.width * entity1->scale_x && maxA >= -entity1->sprite.width * entity1->scale_x)){
		return false;
    }

    minA = min(min(min(x1.y, x3.y), x2.y), x4.y);
    maxA = max(max(max(x1.y, x3.y), x2.y), x4.y);

    if (!(minA <= entity1->sprite.height * entity1->scale_y && maxA >= -entity1->sprite.height * entity1->scale_y)){
		return false;
    }
    
    float minB, maxB;
    Matrix inverseMatrix2 = entity2->matrix.inverse();
    Vector y1 = inverseMatrix2 *(entity1->matrix * entity1->TL);
    Vector y2 = inverseMatrix2 *(entity1->matrix * entity1->TR);
    Vector y3 = inverseMatrix2 *(entity1->matrix * entity1->BL);
    Vector y4 = inverseMatrix2 *(entity1->matrix * entity1->BR);

	 minB = min(min(min(y1.x, y3.x), y2.x), y4.x);
	 maxB = max(max(max(y1.x, y3.x), y2.x), y4.x);

    if (!(minB <= entity2->sprite.width * entity2->scale_x && maxB >= -entity2->sprite.width * entity2->scale_x)){
		return false;
    }

	 minB = min(min(min(y1.y, y3.y), y2.y), y4.y);
	 maxB = max(max(max(y1.y, y3.y), y2.y), y4.y);

    if (!(minB <= entity2->sprite.height * entity2->scale_y && maxB >= -entity2->sprite.height * entity2->scale_y)){
		return false;
    }

	float offset = 0.004f;
	if (entity1->x < entity2->x){
		entity1->x -= offset;
		if (entity1->y < entity2->y){
			entity1->y -= offset;
		}
		else if (entity1->y > entity2->y){
			entity1->y += offset;
		}
	}
	else if (entity1->x > entity2->x){
		entity1->x += offset;
		if (entity1->y < entity2->y){
			entity1->y -= offset;
		}
		else if (entity1->y > entity2->y){
			entity1->y += offset;
		}
	}


	return true;
}
