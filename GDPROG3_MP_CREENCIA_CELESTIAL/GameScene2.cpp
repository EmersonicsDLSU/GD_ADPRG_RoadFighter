#include "GameScene2.h"
#include "BGObject.h"
#include "AirplanePlayer.h"
#include "AirplaneSupport.h"
#include "EnemyAirplane.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EmptyGameObject.h"
#include "EnemySwarmHandler.h"
#include "HUDScreen.h"
#include "UtilityBullet.h"
#include "BulletHandler.h"
#include "PhysicsManager.h"
#include "Collider.h"
#include "CollisionListener.h"
#include "Game.h"
#include "GameSystem.h"
#include "GameObjectManager.h"
#include "SFXManager.h"
#include "ProgressBar.h"
#include "ProgressCarObject.h"
#include "startObject.h"
#include "finishObject.h"

GameScene2::GameScene2() :AScene("GameScene2")
{

}

GameScene2::~GameScene2()
{
}

void GameScene2::onLoadResources()
{

}

void GameScene2::onLoadObjects()
{
    EmptyGameObject* gameSystem = new EmptyGameObject("gameSystem", sf::Vector2f(0, 0));
    GameSystem* gameSystem1 = new GameSystem("gameSystem1");
    gameSystem->attachComponent(gameSystem1);
    this->registerObject(gameSystem);

    BGObject* bgObject = new BGObject("BGObject", "road_2");
    this->registerObject(bgObject);

    AirplanePlayer* planeObject = new AirplanePlayer("PlaneObject");
    this->registerObject(planeObject);

    ProgressBar* progressbar = new ProgressBar("ProgressBar");
    this->registerObject(progressbar);
    progressbar->setPosition(Game::WINDOW_WIDTH - 985, Game::WINDOW_HEIGHT - 385);

    ProgressCarObject* progresscar = new ProgressCarObject("ProgressCarSprite");
    progressbar->attachChild(progresscar);
    progresscar->setPosition(0, 350);

    startObject* start = new startObject("startObjectsprite");
    this->registerObject(start);
    start->setPosition(550, 350);

    finishObject* finish = new finishObject("finishObjectsprite");
    this->registerObject(finish);
    finish->setPosition(2000, 2000);

    SFXManager::getInstance()->playSound("bgmusic");
    SFXManager::getInstance()->soundVolume("bgmusic", 40);


    //play the start sound
    SFXManager::getInstance()->playSound("Start");


    /*BulletHandler* bulletHandler = new BulletHandler(10, "BulletHandler");
    planeObject->attachComponent(bulletHandler);*/

    /*AirplaneSupport* support1 = new AirplaneSupport("AirSupport_1");
    planeObject->attachChild(support1);
    support1->setPosition(50, 100);

    AirplaneSupport* support2 = new AirplaneSupport("AirSupport_2");
    planeObject->attachChild(support2);
    support2->setPosition(-50, 100);*/

    //quit button-AirplanePlayer-EnemyAirplane
    HUDScreen* hudScreen = new HUDScreen("HUDScreen");
    this->registerObject(hudScreen);

    //create N enemies via object pooling
    srand(time(NULL));
    //1st gameObjectSpawn; normal cars
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager1", sf::Vector2f(400, -30)), 10, "SwarmHandler1",
        ObjectPoolHolder::ENEMY_POOL1_TAG, RandomFloat(1, 2), "EnemiesManager1", "normal");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager2", sf::Vector2f(500, -30)), 10, "SwarmHandler2",
        ObjectPoolHolder::ENEMY_POOL2_TAG, RandomFloat(1, 2), "EnemiesManager2", "normal");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager3", sf::Vector2f(600, -30)), 10, "SwarmHandler3",
        ObjectPoolHolder::ENEMY_POOL3_TAG, RandomFloat(1, 2), "EnemiesManager3", "normal");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager4", sf::Vector2f(700, -30)), 10, "SwarmHandler4",
        ObjectPoolHolder::ENEMY_POOL4_TAG, RandomFloat(1, 2), "EnemiesManager4", "normal");
    //2nd gameObjectSpawn; bonus cars
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager5", sf::Vector2f(400, -30)), 10, "SwarmHandler5",
        ObjectPoolHolder::BONUS_POOL1_TAG, RandomFloat(1, 2), "EnemiesManager5", "bonus");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager6", sf::Vector2f(500, -30)), 10, "SwarmHandler6",
        ObjectPoolHolder::BONUS_POOL2_TAG, RandomFloat(1, 2), "EnemiesManager6", "bonus");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager7", sf::Vector2f(600, -30)), 10, "SwarmHandler7",
        ObjectPoolHolder::BONUS_POOL3_TAG, RandomFloat(1, 2), "EnemiesManager7", "bonus");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager8", sf::Vector2f(700, -30)), 10, "SwarmHandler8",
        ObjectPoolHolder::BONUS_POOL4_TAG, RandomFloat(1, 2), "EnemiesManager8", "bonus");
    //3rd gameObjectSpawn; truck cars
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager9", sf::Vector2f(400, -30)), 10, "SwarmHandler9",
        ObjectPoolHolder::TRUCK_POOL1_TAG, RandomFloat(1, 2), "EnemiesManager9", "truck");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager10", sf::Vector2f(500, -30)), 10, "SwarmHandler10",
        ObjectPoolHolder::TRUCK_POOL2_TAG, RandomFloat(1, 2), "EnemiesManager10", "truck");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager11", sf::Vector2f(600, -30)), 10, "SwarmHandler11",
        ObjectPoolHolder::TRUCK_POOL3_TAG, RandomFloat(1, 2), "EnemiesManager11", "truck");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager12", sf::Vector2f(700, -30)), 10, "SwarmHandler12",
        ObjectPoolHolder::TRUCK_POOL4_TAG, RandomFloat(1, 2), "EnemiesManager12", "truck");
    //3rd gameObjectSpawn; truck cars
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager13", sf::Vector2f(400, -30)), 10, "SwarmHandler13",
        ObjectPoolHolder::OIL_POOL1_TAG, RandomFloat(1, 2), "EnemiesManager13", "oil");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager14", sf::Vector2f(500, -30)), 10, "SwarmHandler14",
        ObjectPoolHolder::OIL_POOL2_TAG, RandomFloat(1, 2), "EnemiesManager14", "oil");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager15", sf::Vector2f(600, -30)), 10, "SwarmHandler15",
        ObjectPoolHolder::OIL_POOL3_TAG, RandomFloat(1, 2), "EnemiesManager15", "oil");
    instantiateEnemySpawn(new EmptyGameObject("EnemiesManager16", sf::Vector2f(700, -30)), 10, "SwarmHandler16",
        ObjectPoolHolder::OIL_POOL4_TAG, RandomFloat(1, 2), "EnemiesManager16", "oil");

    /*EmptyGameObject* utilityManager = new EmptyGameObject("EnemiesManager");
    EnemySwarmHandler* swarmHandler = new EnemySwarmHandler(10, "SwarmHandler");
    enemiesManager->attachComponent(swarmHandler);
    this->registerObject(enemiesManager);*/

    PhysicsManager::getInstance()->initialize("Physics_Manager", planeObject);
}


/*instantiateEnemySpawn(new EmptyGameObject("EnemiesManager1", sf::Vector2f(400, -30)), 10, "SwarmHandler1",
    ObjectPoolHolder::ENEMY_POOL1_TAG, RandomFloat(1, 5), "EnemiesManager1");

EmptyGameObject* enemiesManager1 = new EmptyGameObject("EnemiesManager1", sf::Vector2f(400, -30));
EnemySwarmHandler* swarmHandler1 = new EnemySwarmHandler(10, "SwarmHandler1", enemiesManager1, ObjectPoolHolder::ENEMY_POOL1_TAG, RandomFloat(1, 5), "EnemiesManager1");
enemiesManager1->attachComponent(swarmHandler1);
enemiesManager1->setEnabled(false);
GameSystem* gs1 = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
gs1->addListLane(enemiesManager1);
this->registerObject(enemiesManager1);*/

void GameScene2::instantiateEnemySpawn(EmptyGameObject* eg, int size, std::string handlerName,
    std::string poolName, float random, std::string EOName, std::string carType)
{
    EnemySwarmHandler* es = new EnemySwarmHandler(size, handlerName, eg, poolName, random, EOName, carType);
    eg->attachComponent(es);
    eg->setEnabled(false);
    GameSystem* gs = (GameSystem*)GameObjectManager::getInstance()->findObjectByName("gameSystem")->findComponentByName("gameSystem1");
    gs->addListLane(eg, carType);
    this->poolContainer.push_back(poolName);
    this->registerObject(eg);
}

float GameScene2::RandomFloat(float a, float b)
{
    srand(time(NULL));
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void GameScene2::unLoadPool()
{
    for (std::string pool : poolContainer)
    {
        GameObjectPool* poolTag = ObjectPoolHolder::getInstance()->getPool(pool);
        ObjectPoolHolder::getInstance()->unregisterObjectPool(poolTag);
    }
    poolContainer.clear();
}

void GameScene2::onUnloadObjects()
{
    unLoadPool();
    PhysicsManager::getInstance()->clearTracks();
    AScene::onUnloadObjects();
    SFXManager::getInstance()->stopSound("bgmusic");
}

void GameScene2::onUnloadResources()
{
}


