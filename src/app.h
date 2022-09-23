#pragma once

#include <vector>
#include <math.h>

#include "./entity.h"
#include "../inc/yoshix.h"

using namespace gfx;

enum class EObstacleTypes
{
	EARTH,
	MOON,
	GDIMP, // :D
	TRUNK,
	BOOKSHELF,
	CHEST,
	OATMILK
};

struct SWorldSegment
{
	SEntity ground;
	SEntity leftBorder;
	SEntity rightBorder;
	std::vector<SObstacleEntity> obstacles;
};

class CApplication : public IApplication
{
	public:
		CApplication();
		virtual ~CApplication();

	private:
		float fieldOfViewY;             // Vertical view angle of the camera
		
		// textures
		BHandle earthTexture;
		BHandle wallTexture;
		BHandle playerTexture;
		BHandle moonTexture;
		BHandle gdimpTexture;
		BHandle trunkTexture;
		BHandle bookShelfTexture;
		BHandle oatMilkTexture;
		BHandle chestTexture;
		BHandle startScreenTexture;
		BHandle optionsScreenTexture;
		BHandle endScreenTexture;

		// materials
		BHandle earthMaterial;
		BHandle wallMaterial;
		BHandle playerMaterial;
		BHandle moonMaterial;
		BHandle gdimpMaterial;
		BHandle trunkMaterial;
		BHandle bookShelfMaterial;
		BHandle oatMilkMaterial;
		BHandle chestMaterial;
		BHandle startScreenMaterial;
		BHandle optionsScreenMaterial;
		BHandle endScreenMaterial;

		// constant buffers
		BHandle cb_worldMatrix;
		BHandle cb_viewProjectionMatrix;
		BHandle cb_lightInfo;
		BHandle cb_cameraInfo;

		// shaders
		BHandle vertexShader;
		BHandle pixelShader;

		// meshes
		BHandle groundMesh;
		BHandle obstacleMesh;
		BHandle obstacleMeshB;
		BHandle playerMesh;
		BHandle gdimpObstacleMesh;
		BHandle trunkObstacleMesh;
		BHandle bookShelfObstacleMesh;
		BHandle oatMilkMesh;
		BHandle chestMesh;
		BHandle startScreenMesh;
		BHandle optionsScreenMesh;
		BHandle endScreenMesh;

		SEntity screen = {
			&this->startScreenMesh,
			0.0f, 11.0f, -5.0f,
			4.0f, 4.0f, 4.0f,
			10.0f, 0.0f, 0.0f
		};

		const float CAMERA_START_POSITION[3] = { 0.0f, 3.0f, -8.0f };
		const float CAMERA_START_TARGET[3]   = { 0.0f, 0.0f,  2.0f };

		const float CAMERA_SCREEN_POSITION[3] = { 0.0f, 12.0f, -10.0f };
		const float CAMERA_SCREEN_TARGET[3]   = { 0.0f, 10.0f, 2.0f };

		// player
		SEntity player;

		// entities
		std::vector<SWorldSegment> worldSegments;

		std::vector<SObstacleEntity> spaceJunk;

		// will be overwritten on InternOnResize()
		int windowHeight = 600;
		int windowWidth = 800;

		// used to store the game state
		bool START_GAME = false;
		bool DEAD_BY_OBSTACLE = false;
		bool PLAYER_IS_FALLING = false;
		bool SHOW_GAME_OVER_SCREEN = false;
		bool SHOW_OPTIONS_SCREEN = false;

		// ascii keys
		const unsigned int UP_KEY = 38;
		const unsigned int DOWN_KEY = 40;
		const unsigned int LEFT_KEY = 37;
		const unsigned int RIGHT_KEY = 39;
		const unsigned int SPACE_KEY = 32;
		const unsigned int O_KEY = 79;
		const unsigned int G_KEY = 71;
		const unsigned int E_KEY = 69;
		const unsigned int M_KEY = 77;
		const unsigned int H_KEY = 72;

		// used for debugging the application
		const bool OBSTACLES_ENABLED = true;
		const bool PLAYER_ENABLED = true;
		bool MORTALITY_ENABLED = false;

		//	indicates if the game is still running or not
		bool GAME_OVER = false;

		
		//	indicates the movement state of the player
		bool PLAYER_IS_JUMPING = false;
		bool PLAYER_IS_SHRUNKEN = false;

		// indicates how fast the player and the camera are moving along the psoitive z axis
		float MOVEMENT_SPEED = 0.15f;
		const float EASY_SPEED = 0.1f;
		const float MIDDLE_SPEED = 0.15f;
		const float HARD_SPEED = 0.2f;

		// indicates how many world segments are generated upfront
		const int NUM_OF_WORLD_SEGMENTS = 25;

		const int NUM_OF_SPACE_JUNK_ITEMS = 100;

		// sensitivity of the collision detection, lower number means you can die just grazing the obstacle
		const int VERTICAL_COLLISION_SENSITIVITY = 3;
		const int HORIZONTAL_COLLISION_SENSITIVITY = 3;

		
		//	variables used for the world generation
		const float SEGMENT_Z_OFFSET = 10.0f;
		const float OBSTACLE_Z_OFFSET = 10.0f;

		const float SEGMENT_LENGTH = 10.0f;

		const float SEGMENT_WIDTH = 5.0f;
		const float HALF_SEGMENT_WIDTH = SEGMENT_WIDTH / 2;
		const float HALF_BROKEN_SEGMENT_WIDTH = HALF_SEGMENT_WIDTH / 2;

		
		//	variables used for x axes movements of the player
		const float LEFT_MOVEMENT_BOUND = -2.0f;
		const float RIGHT_MOVEMENT_BOUND = 2.0f;
		const float X_MOVEMENT_STEP = 1.0f;

		const float SCREEN_POSITION[3] = { 0.0f, 1.0f, -5.0f };
 
	private:
		bool StartGame(const float speed = 0.15f);
		bool EndGame();
		bool RestartGame();
		bool OptionsMenu();

		// used to create the different materials
		bool CreateMaterial(BHandle& texture, BHandle& material);

		// initialize the camera
		bool InitCamera(int windowWidth, int windowHeight);

		// handles the drwaing of an individual mesh
		bool DrawEntity(SEntity entity, float matrix[16]);

		bool DrawScene();

		// move the camera and the player along the positive z axis
		bool UpdateCameraAndPlayer();

		bool EntitiesAreColliding3D(SEntity entity, SObstacleEntity obstacle);
		bool ObserveForCollision();

		bool ObserveForGravity();

		bool HandleSpaceJunk();

		bool MoveCameraToScreen();
		bool MoveCameraToField();

		// function takes a number as parameter and generates world segments accordingly
		bool GenerateSpaceJunkItems(int numOfSpaceJunkItems);
		bool GenerateWorldSegments(int numOfSegments);
		SObstacleEntity GenerateObstacle(EObstacleTypes obstacleType);

		bool HandleMovableObstacles();

		virtual bool InternOnStartup();
		virtual bool InternOnShutdown();
		virtual bool InternOnCreateTextures();
		virtual bool InternOnReleaseTextures();
		virtual bool InternOnCreateConstantBuffers();
		virtual bool InternOnReleaseConstantBuffers();
		virtual bool InternOnCreateShader();
		virtual bool InternOnReleaseShader();
		virtual bool InternOnCreateMaterials();
		virtual bool InternOnReleaseMaterials();
		virtual bool InternOnCreateMeshes();
		virtual bool InternOnReleaseMeshes();
		virtual bool InternOnResize(int _Width, int _Height);
		virtual bool InternOnUpdate();
		virtual bool InternOnFrame();
		virtual bool InternOnKeyEvent(unsigned _Key, bool _IsKeyDown, bool _IsAltDown);
};