namespace Blu {
    void ClearScreen(u32 color) {
        gra->clear(color);
    }
    void DrawRect(Rect rect, u32 color) {
        gra->filledrect(rect, color);
    }
    void DrawPoint(Spot p, u32 color, int thickness) {
        if (1280 / render_state.width < 1)thickness *= 1280 / render_state.width;
        if (720 / render_state.height < 1)thickness *= 720 / render_state.height;
        DrawRect({ p.x - thickness, p.y - thickness, thickness * 2, thickness * 2 }, color);
    }
    void DrawLine(Spot start, Spot end, u32 color, int thickness) {
        gra->line(start, end, color, thickness);
    }
    void DrawCircle(Spot center, int radius, u32 color, float thickness) {
        gra->ovalperim(center, radius, radius, color, thickness);
    }
    void DrawOval(Spot center, int radiusX, int radiusY, u32 color, float thickness) {
        gra->ovalperim(center, radiusX, radiusY, color, thickness);
    }
    void DrawFilledCircle(Spot center, int radius, u32 color) {
        gra->oval(center, radius, radius, color);
    }
    void DrawFilledOval(Spot center, int radiusX, int radiusY, u32 color) {
        gra->oval(center, radiusX, radiusY, color);
    }
    void DrawPolygon(const std::vector<Spot>& points, u32 color) {
        gra->poly(points, color);
    }
    void DrawArc(Spot center, float rx, float ry, int startangle, int endangle, int color, int thickness) {
        gra->arc(center, rx, ry, startangle, endangle, color, thickness);
    }
    void DrawFilledArc(Spot center, float rx, float ry, int startangle, int endangle, int color) {
        gra->fillarc(center, rx, ry, startangle, endangle, color);
    }
        Shape::Shape() {
            gra->factory->CreatePathGeometry(&Path);
            Path->Open(&Sink);
        }
        Shape::~Shape() {
            if (Sink) {
                Sink->Release();
            }
            if (Path) {
                Path->Release();
            }
        }
        void Shape::Begin(Spot start) {
            Sink->BeginFigure(
                D2D1::Point2F(start.x, start.y),
                D2D1_FIGURE_BEGIN_FILLED
            );
        }
        void Shape::AddLine(Spot end) {
            Sink->AddLine({ (float)end.x, (float)end.y });
        }
        void Shape::AddBigArc(Spot center, int rx, int ry) {
            Sink->AddArc(
                D2D1::ArcSegment(
                    D2D1::Point2F(
                        center.x,
                        center.y
                    ),
                    D2D1::SizeF(
                        rx,
                        ry
                    ),
                    0,
                    D2D1_SWEEP_DIRECTION_CLOCKWISE,
                    D2D1_ARC_SIZE_LARGE
                )
            );
        }
        void Shape::AddLittleArc(Spot center, int rx, int ry) {
            Sink->AddArc(
                D2D1::ArcSegment(
                    D2D1::Point2F(
                        center.x,
                        center.y
                    ),
                    D2D1::SizeF(
                        rx,
                        ry
                    ),
                    0,
                    D2D1_SWEEP_DIRECTION_CLOCKWISE,
                    D2D1_ARC_SIZE_SMALL
                )
            );
        }
        void Shape::AddBezier(Spot p1, Spot p2, Spot p3) {
            Sink->AddBezier(
                D2D1::BezierSegment(
                    { (float)p1.x, (float)p1.y },
                    { (float)p2.x, (float)p2.y },
                    { (float)p3.x, (float)p3.y }
                )
            );
        }
        void Shape::DrawFilled(int color) {
            Sink->EndFigure(D2D1_FIGURE_END_OPEN);
            Sink->Close();
            gra->fillgeometry(Path, color);
        }
        void Shape::DrawOutline(int color, int thickness) {
            Sink->EndFigure(D2D1_FIGURE_END_OPEN);
            Sink->Close();
            gra->drawgeometry(Path, color, thickness);
        }
}