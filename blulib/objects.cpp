namespace Blu {
    StillBody::StillBody(Rect HITBOX) : hitbox(HITBOX) {}

    void StillBody::runScript(void (*func)(StillBody&)) {
        func(*this);
    }

    Area::Area(Rect HITBOX) : hitbox(HITBOX) {}
    PhysicsBody::PhysicsBody(Rect HITBOX) {
        IsOnFloor = false;
        IsOnWall = false;
        IsOnFloorOnly = false;
        IsOnWallOnly = false;
        hitbox = HITBOX;
        pos = { hitbox.x, hitbox.y };
        vel = { 0, 0 };
    }

    void PhysicsBody::update() {
        pos.x += vel.x;
        pos.y += vel.y;
        hitbox.x = pos.x;
        hitbox.y = pos.y;
    }

    void PhysicsBody::collide(std::vector<StillBody> Stillbody) {
        std::vector<Rect> Stillbodies;
        for (auto& i : Stillbody) {
            Stillbodies.push_back(i.hitbox);
        }

        IsOnWall = false;
        IsOnFloor = false;

        int collide[4] = {
            collidelist(Rect{ pos.x, pos.y + vel.y, hitbox.width, -vel.y + 1 }, Stillbodies),
            collidelist(Rect{ pos.x, pos.y + hitbox.height, hitbox.width, vel.y - 1 }, Stillbodies),
            collidelist(Rect{ pos.x + vel.x, pos.y + 1, vel.x - 1, hitbox.height - 1 }, Stillbodies),
            collidelist(Rect{ pos.x + hitbox.width, pos.y + 1, vel.x + 1, hitbox.height - 1 }, Stillbodies)
        };

        if (collide[0] >= 0 && vel.y <= 0) {
            vel.y = 0;
            pos.y = Stillbodies[collide[0]].y + Stillbodies[collide[0]].height;
            IsOnFloor = true;
        }

        if (collide[1] >= 0 && vel.y > 0) {
            vel.y = 0;
            pos.y = Stillbodies[collide[1]].y - hitbox.height;
        }

        if (collide[2] >= 0 && vel.x <= 0) {
            vel.x = 0;
            pos.x = Stillbodies[collide[2]].x + Stillbodies[collide[2]].width;
            IsOnWall = true;
        }

        if (collide[3] >= 0 && vel.x > 0) {
            vel.x = 0;
            pos.x = Stillbodies[collide[3]].x - hitbox.width;
            IsOnWall = true;
        }

        IsOnWallOnly = (IsOnWall && !IsOnFloor);
        IsOnFloorOnly = (IsOnFloor && !IsOnWall);
    }

    bool PhysicsBody::IsInside(Area area) {
        return colliderect(area.hitbox, hitbox);
    }

    void PhysicsBody::runScript(void (*func)(PhysicsBody&)) {
        func(*this);
    }

    Clock::Clock(int Waittime) : WaitTime(Waittime), currentf(0) {}

    bool Clock::isready() {
        return currentf >= WaitTime;
    }

    void Clock::tick() {
        currentf++;
    }

    void Clock::reset() {
        currentf = 0;
    }

    Scene_Controller* Scene_Controller::instance = nullptr;

    Scene_Controller::Scene_Controller() : currentScene(nullptr) {}

    Scene_Controller* Scene_Controller::getInstance() {
        if (instance == nullptr) {
            instance = new Scene_Controller();
        }
        return instance;
    }

    void Scene_Controller::changeScene(Scene* newScene) {
        if (currentScene) {
            currentScene->unload();
        }
        currentScene = newScene;
        currentScene->load();
    }

    void Scene_Controller::update() {
        if (currentScene) {
            currentScene->update();
        }
    }

    void Scene_Controller::render() {
        if (currentScene) {
            currentScene->render();
        }
    }
}

Blu::Scene_Controller* SceneController = Blu::Scene_Controller::getInstance();