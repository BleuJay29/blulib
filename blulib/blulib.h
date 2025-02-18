#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <d2d1_1.h>
typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
#define global_variable static
#define internal static
#define B_NONE -1
namespace Blu {
    class Rect {
    public:
        int x;
        int y;
        int width;
        int height;

        Rect(int X, int Y, int WIDTH, int HEIGHT);
    };
    class SpotF {
    public:
        float x;
        float y;

        SpotF(float x1, float y1);
    };
    class Spot {
    public:
        int x;
        int y;

        Spot(int x1, int y1);
        bool operator==(const Spot& s);
        Spot operator+(const Spot& s);
    };
    Spot operator+(const Spot& l, const Spot& r);
    bool operator==(const Spot& lhs, const Spot& rhs);
    int clamp(int min, int val, int max);
    float clampf(float min, float val, float max);
    bool InRange(int num, int min, int max);
    std::vector<int> range(int start, int end);
    float avg(std::vector<int> all);
    int AbsI(int i);
    float AbsF(float i);
    int IsLeast(std::vector<float> all);
    int IsMost(std::vector<float> all);
    float GetDst(int x0, int y0, int x1, int y1);
    float GetSlope(int x0, int y0, int x1, int y1);
    Spot rotatePoint(Spot p, float angle, Spot center);
    template <typename T>
    bool isin(T i, const std::vector<T>& vec);
    template <typename T>
    std::vector<std::vector<T>> GetAllUniqueCombos(const std::vector<T>& arr);
    std::string inttostring(int n);
    bool colliderect(Rect rect1, Rect rect2);
    bool collidespot(Spot spot, Rect rect2);
    int collidelist(Rect rect, std::vector<Rect> rects);
    float dotProduct(const Spot& a, const Spot& b);
    Spot subtract(const Spot& a, const Spot& b);
    std::pair<float, float> projectPolygon(const std::vector<Spot>& polygon, const Spot& axis);
    bool overlap(const std::pair<float, float>& range1, const std::pair<float, float>& range2);
    bool PolygonCollision(const std::vector<Spot>& polygon1, const std::vector<Spot>& polygon2);
    class Transformations {
    public:
        Transformations();
        void Rotate(float angle);
        void Translate(float offsetX, float offsetY);
        void reset();
    private:
        D2D1_MATRIX_3X2_F m_transform;
    };
    void ClearScreen(u32 color);
    void DrawRect(Rect rect, u32 color);
    void DrawPoint(Spot p, u32 color, int thickness = 1);
    void DrawLine(Spot start, Spot end, u32 color, int thickness = 1);
    void DrawCircle(Spot center, int radius, u32 color, float thickness = 1);
    void DrawOval(Spot center, int radiusX, int radiusY, u32 color, float thickness = 1);
    void DrawFilledCircle(Spot center, int radius, u32 color);
    void DrawFilledOval(Spot center, int radiusX, int radiusY, u32 color);
    void DrawPolygon(const std::vector<Spot>& points, u32 color);
    void DrawArc(Spot center, float rx, float ry, int startangle, int endangle, int color, float thickness = 1);
    void DrawFilledArc(Spot center, float rx, float ry, int startangle, int endangle, int color);
    class Shape {
    public:
        Shape();
        ~Shape();
        void Begin(Spot start);
        void AddLine(Spot end);
        void AddBigArc(Spot center, int rx, int ry);
        void AddLittleArc(Spot center, int rx, int ry);
        void AddBezier(Spot p1, Spot p2, Spot p3);
        void DrawFilled(int color);
        void DrawOutline(int color, int thickness = 1);
        void LoadBSP(const char * filename);
    private:
        ID2D1PathGeometry* Path;
        ID2D1GeometrySink* Sink;
    };
    class Sprite {
    public:
        int width;
        int height;
        std::vector<uint8_t> data;
        Sprite(const char* filename = (const char*)-1);
        void load(const char* filename);
        void resize(int newWidth, int newHeight);
        void draw(Spot pos);
        ~Sprite();
    private:
        ID2D1Bitmap* dbmp;
        void Convert();
    };
    struct Font;
    Font LoadFont(const char* filepath);
    void DrawWords(std::string text, int fontsize, Spot center, Font font, int color);
    struct Button_State {
        bool isdown;
        bool changed;
    };
    enum {
        K_UP,
        K_DOWN,
        K_LEFT,
        K_RIGHT,
        K_A, K_B, K_C, K_D, K_E, K_F, K_G, K_H, K_I, K_J, K_K, K_L, K_M, K_N, K_O, K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W, K_X, K_Y, K_Z,
        K_SPACE,
        K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9, K_0,
        K_RSHIFT, K_LSHIFT, K_RCTRL, K_LCTRL, K_RALT, K_LALT, K_TAB, K_BACKSPACE, K_ENTER, K_ESCAPE,
        RMOUSE, LMOUSE,

        BUTTON_COUNT,
    };
    struct Input {
        Button_State buttons[BUTTON_COUNT];
    };
    void InpOff(Input* input);
    typedef std::vector<int> Keybind;
    typedef std::vector<unsigned int> Keyfunc;
    bool isbudow(Input* input, int b);
    bool iskbdow(Input* input, Keybind b);
    bool iskfdow(Input* input, Keyfunc b);
    bool isbupre(Input* input, int b);
    bool iskbpre(Input* input, Keybind b);
    bool iskfpre(Input* input, Keyfunc b);
    bool isburel(Input* input, int b);
    bool iskbrel(Input* input, Keybind b);
    bool iskfrel(Input* input, Keyfunc b);
    Spot GetMousePos();
    void HideMouse();
    void ShowMouse();
    class SoundImpl;
    class Sound {
    private:
        SoundImpl* pImpl;
    public:
        Sound();
        ~Sound();
        bool load(const char* filename);
        void play();
        void stop();
        void setPitch(float pitch);
        void setHertz(float hertz);
    };
    class StillBody {
    public:
        Rect hitbox;
        StillBody(Rect HITBOX);
        void runScript(void (*func)(StillBody&));
    };
    class Area {
    public:
        Rect hitbox;
        const char* name;
        Area(Rect HITBOX);
    };
    class PhysicsBody {
    public:
        Spot pos = { 0, 0 };
        Rect hitbox = { 0, 0, 0, 0 };
        Spot vel = { 0, 0 };
        bool IsOnWall;
        bool IsOnFloor;
        bool IsOnWallOnly;
        bool IsOnFloorOnly;
        PhysicsBody(Rect HITBOX);
        void update();
        void collide(std::vector<StillBody> Stillbody);
        bool IsInside(Area area);
        void runScript(void (*func)(PhysicsBody&));
    };
    class Button {
    public:
        Rect hitbox = { 0, 0, 0, 0 };

        Button(Rect HITBOX);

        bool IsClicked(Input* input);
        bool IsRightClicked(Input* input);
        bool IsOver();
        void draw(u32 color);
    };
    class Clock {
    public:
        int WaitTime;
        int currentf;
        Clock(int Waittime);
        bool isready();
        void tick();
        void reset();
    };
    class Scene {
    public:
        virtual ~Scene() = default;
        virtual void load() = 0;
        virtual void update() = 0;
        virtual void unload() = 0;
        virtual void render() = 0;
    };
    class Scene_Controller {
    private:
        static Scene_Controller* instance;
        Scene* currentScene;
        Scene_Controller();
    public:
        static Scene_Controller* getInstance();
        void changeScene(Scene* newScene);
        void update();
        void render();
    };
    extern Blu::Scene_Controller* SceneController;
    //You define this (runs every frame)
    void Update(Input* input);
    int BluMain(HINSTANCE hInstance, HINSTANCE prevInstance, int nCmdShow);
    extern const char* GAME_NAME;
}
#define IsDown(b) Blu::isbudow(input, b)
#define pressed(b) Blu::isbupre(input, b)
#define released(b) Blu::isburel(input, b)
#define IsBindDown(b) Blu::iskbdow(input, b)
#define BindPressed(b) Blu::iskbpre(input, b)
#define BindReleased(b) Blu::iskbrel(input, b)
#define IsFuncDown(b) Blu::iskfdow(input, b)
#define FuncPressed(b) Blu::iskfpre(input, b)
#define FuncReleased(b) Blu::iskfrel(input, b)