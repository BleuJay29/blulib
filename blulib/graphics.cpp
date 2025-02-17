class Graphics {
public:
    Graphics() : factory(nullptr), renderTarget(nullptr) {}
    void begin() {
        renderTarget->BeginDraw();
    }
    void end() {
        renderTarget->EndDraw();
    }
    bool init(HWND hwnd) {
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
        if (SUCCEEDED(hr)) {
            RECT rc;
            GetClientRect(hwnd, &rc);
            D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
            hr = factory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom)),
                &renderTarget
            );
            renderTarget->CreateSolidColorBrush(
                D2D1::ColorF(((0x000000 >> 16) & 0xFF) / 255.0f,
                    ((0x000000 >> 8) & 0xFF) / 255.0f,
                    ((0x000000 >> 0) & 0xFF) / 255.0f,
                    1.0f
                ),
                &Brush
            );
            return true;
        }
        return false;
    }
    void bmp(ID2D1Bitmap* dbmp, Rect p) {
        D2D1_RECT_F rect = D2D1::RectF(p.x, p.y, p.x + p.width, p.y + p.height);
        renderTarget->DrawBitmap(dbmp, rect);
    }
    void filledrect(Rect p, int color) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        if (renderTarget) {
            renderTarget->FillRectangle(D2D1::RectF(p.x, p.y, p.x + p.width, p.y + p.height), Brush);
        }
    }
    void clear(int color) {
        renderTarget->Clear(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f, 
                ((color >> 0) & 0xFF) / 255.0f, 
                1.0f
            )
        );
    }
    void line(Spot s1, Spot s2, int color, float thickness = 1) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        renderTarget->DrawLine(D2D1::Point2F(s1.x, s1.y), D2D1::Point2F(s2.x, s2.y), Brush, thickness);
    }
    void oval(Spot center, float rx, float ry, int color) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(center.x, center.y), rx, ry), Brush);
    }
    void ovalperim(Spot center, float rx, float ry, int color, float thickness) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(center.x, center.y), rx, ry), Brush, thickness);
    }
    void poly(const std::vector<Spot>& spots, int color) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        ID2D1GeometrySink* pSink = NULL;
        ID2D1PathGeometry* pathGeometry = nullptr;
        factory->CreatePathGeometry(&pathGeometry);
        pathGeometry->Open(&pSink);
        pSink->BeginFigure(
            D2D1::Point2F(spots[0].x, spots[0].y),
            D2D1_FIGURE_BEGIN_FILLED
        );
        for (int i = 1; i < spots.size(); i++) {
            pSink->AddLine(D2D1::Point2F(spots[i].x, spots[i].y));
        }
        pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
        pSink->Close();
        pSink->Release();
        renderTarget->FillGeometry(pathGeometry, Brush);
        pathGeometry->Release();
    }
    void arc(Spot center, float rx, float ry, int startangle, int endangle, int color, float thickness) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(center.x, center.y), rx, ry);

        // Create a path geometry for the arc
        ID2D1PathGeometry* pathGeometry = nullptr;\
        factory->CreatePathGeometry(&pathGeometry);

        ID2D1GeometrySink* sink = nullptr;
        pathGeometry->Open(&sink);
        
        // Begin the arc segment
        sink->BeginFigure(
            D2D1::Point2F(center.x, center.y),
            D2D1_FIGURE_BEGIN_FILLED
        );
        sink->AddLine(
            D2D1::Point2F(
                ellipse.point.x + ellipse.radiusX * cos(startangle * DEG2RAD),
                ellipse.point.y + ellipse.radiusY * sin(startangle * DEG2RAD)
            )
        );
        if (endangle-startangle>+180) {
            sink->AddArc(
                D2D1::ArcSegment(
                    D2D1::Point2F(
                        ellipse.point.x + ellipse.radiusX * cos(endangle * DEG2RAD),
                        ellipse.point.y + ellipse.radiusY * sin(endangle * DEG2RAD)
                    ),
                    D2D1::SizeF(ellipse.radiusX, ellipse.radiusY),
                    0,
                    D2D1_SWEEP_DIRECTION_CLOCKWISE,
                    D2D1_ARC_SIZE_LARGE
                )
            );
        }
        else {
            sink->AddArc(D2D1::ArcSegment(
                D2D1::Point2F(
                    ellipse.point.x + ellipse.radiusX * cos(endangle * DEG2RAD),
                    ellipse.point.y + ellipse.radiusY * sin(endangle * DEG2RAD)
                ),
                D2D1::SizeF(ellipse.radiusX, ellipse.radiusY),
                0,
                D2D1_SWEEP_DIRECTION_CLOCKWISE,
                D2D1_ARC_SIZE_SMALL)
            );
        }

        // End the figure
        sink->EndFigure(D2D1_FIGURE_END_CLOSED);
        sink->Close();

        // Draw the arc segment
        renderTarget->DrawGeometry(pathGeometry, Brush, thickness);

        // Release resources
        sink->Release();
        pathGeometry->Release();
    }
    void fillarc(Spot center, float rx, float ry, float startangle, float endangle, int color) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(center.x, center.y), rx, ry);

        // Create a path geometry for the arc
        ID2D1PathGeometry* pathGeometry = nullptr; \
            factory->CreatePathGeometry(&pathGeometry);

        ID2D1GeometrySink* sink = nullptr;
        pathGeometry->Open(&sink);

        // Begin the arc segment
        sink->BeginFigure(
            D2D1::Point2F(center.x, center.y),
            D2D1_FIGURE_BEGIN_FILLED
        );
        sink->AddLine(
            D2D1::Point2F(
                ellipse.point.x + ellipse.radiusX * cos(startangle * DEG2RAD),
                ellipse.point.y + ellipse.radiusY * sin(startangle * DEG2RAD)
            )
        );
        // Add the arc segment
        if (endangle - startangle > +180) {
            sink->AddArc(D2D1::ArcSegment(
                D2D1::Point2F(
                    ellipse.point.x + ellipse.radiusX * cos(endangle * DEG2RAD),
                    ellipse.point.y + ellipse.radiusY * sin(endangle * DEG2RAD)
                ),
                D2D1::SizeF(ellipse.radiusX, ellipse.radiusY),
                0,
                D2D1_SWEEP_DIRECTION_CLOCKWISE,
                D2D1_ARC_SIZE_LARGE)
            );
        }
        else {
            sink->AddArc(D2D1::ArcSegment(
                D2D1::Point2F(
                    ellipse.point.x + ellipse.radiusX * cos(endangle * DEG2RAD),
                    ellipse.point.y + ellipse.radiusY * sin(endangle * DEG2RAD)
                ),
                D2D1::SizeF(ellipse.radiusX, ellipse.radiusY),
                0,
                D2D1_SWEEP_DIRECTION_CLOCKWISE,
                D2D1_ARC_SIZE_SMALL)
            );
        }
        // End the figure
        sink->EndFigure(D2D1_FIGURE_END_OPEN);
        sink->Close();

        // Draw the arc segment
        renderTarget->FillGeometry(pathGeometry, Brush);

        // Release resources
        sink->Release();
        pathGeometry->Release();
    }
    void fillgeometry(ID2D1PathGeometry* Path, int color) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        renderTarget->FillGeometry(Path, Brush);
        Path->Release();
    }
    void drawgeometry(ID2D1PathGeometry* Path, int color, int thickness) {
        Brush->SetColor(
            D2D1::ColorF(
                ((color >> 16) & 0xFF) / 255.0f,
                ((color >> 8) & 0xFF) / 255.0f,
                ((color >> 0) & 0xFF) / 255.0f,
                1.0f
            )
        );
        renderTarget->DrawGeometry(Path, Brush, thickness);
    }
    ~Graphics() {
        if (renderTarget) {
            renderTarget->Release();
        }
        if (factory) {
            factory->Release();
        }
        if (Brush) {
            Brush->Release();
        }
    }
    ID2D1SolidColorBrush* Brush;
    ID2D1Factory1* factory;
    ID2D1HwndRenderTarget* renderTarget;
};
Graphics* gra;
namespace Blu {
    Transformations::Transformations(){
        m_transform = D2D1::Matrix3x2F::Identity();
    }
    void Transformations::Rotate(float angle) {
        m_transform = m_transform * D2D1::Matrix3x2F::Rotation(angle);
        gra->renderTarget->SetTransform(m_transform);
    }

    void Transformations::Translate(float offsetX, float offsetY) {
        m_transform = m_transform * D2D1::Matrix3x2F::Translation(offsetX, offsetY);
        gra->renderTarget->SetTransform(m_transform);
    }

    void Transformations::reset() {
        m_transform = D2D1::Matrix3x2F::Identity();
        gra->renderTarget->SetTransform(m_transform);
    }
}