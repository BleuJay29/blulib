namespace Blu {
    Button::Button(Rect HITBOX) {
        hitbox = HITBOX;
    }

    bool Button::IsClicked(Input* input) {
        if (colliderect({ GetMousePos().x, GetMousePos().y, 1, 1 }, hitbox)) {
            if (IsDown(LMOUSE)) {
                return true;
            }
        }
        return false;
    }

    bool Button::IsRightClicked(Input* input) {
        if (colliderect({ GetMousePos().x, GetMousePos().y, 1, 1 }, hitbox)) {
            if (IsDown(RMOUSE)) {
                return true;
            }
        }
        return false;
    }

    bool Button::IsOver() {
        if (colliderect({ GetMousePos().x, GetMousePos().y, 1, 1 }, hitbox)) {
            return true;
        }
        return false;
    }

    void Button::draw(u32 color) {
        DrawRect(hitbox, color);
    }
}