namespace Blu {
	bool colliderect(Rect rect1, Rect rect2) {
		return (rect1.x < rect2.x + rect2.width &&
			rect1.x + rect1.width > rect2.x &&
			rect1.y < rect2.y + rect2.height &&
			rect1.y + rect1.height > rect2.y);
	}
	bool collidespot(Spot spot, Rect rect2) {
		return (spot.x < rect2.x + rect2.width &&
			spot.x > rect2.x &&
			spot.y < rect2.y + rect2.height &&
			spot.y > rect2.y);
	}
	int collidelist(Rect rect, std::vector<Rect> rects) {
		for (float rec = 0; rec < rects.size(); rec++) {
			if (colliderect(rect, rects[rec])) {
				return rec;
			}
		}
		return -1;
	}
    float dotProduct(const Spot& a, const Spot& b) {
        return a.x * b.x + a.y * b.y;
    }
    Spot subtract(const Spot& a, const Spot& b) {
        return { a.x - b.x, a.y - b.y };
    }
    std::pair<float, float> projectPolygon(const std::vector<Spot>& polygon, const Spot& axis) {
        float min = dotProduct(polygon[0], axis);
        float max = min;
        for (size_t i = 1; i < polygon.size(); ++i) {
            float projection = dotProduct(polygon[i], axis);
            if (projection < min) min = projection;
            if (projection > max) max = projection;
        }
        return { min, max };
    }
    bool overlap(const std::pair<float, float>& range1, const std::pair<float, float>& range2) {
        return range1.first <= range2.second && range2.first <= range1.second;
    }
    bool PolygonCollision(const std::vector<Spot>& polygon1, const std::vector<Spot>& polygon2) {
        std::vector<Spot> axes;

        // Get axes from polygon1
        for (size_t i = 0; i < polygon1.size(); ++i) {
            Spot p1 = polygon1[i];
            Spot p2 = polygon1[(i + 1) % polygon1.size()];
            Spot edge = subtract(p2, p1);
            axes.push_back({ -edge.y, edge.x }); // Normal vector
        }

        // Get axes from polygon2
        for (size_t i = 0; i < polygon2.size(); ++i) {
            Spot p1 = polygon2[i];
            Spot p2 = polygon2[(i + 1) % polygon2.size()];
            Spot edge = subtract(p2, p1);
            axes.push_back({ -edge.y, edge.x }); // Normal vector
        }

        // Check for separation on every axis
        for (const Spot& axis : axes) {
            std::pair<float, float> projection1 = projectPolygon(polygon1, axis);
            std::pair<float, float> projection2 = projectPolygon(polygon2, axis);
            if (!overlap(projection1, projection2)) {
                return false; // Separated on this axis
            }
        }
        return true; // No separating axis found, polygons are colliding
    }
}