#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class GameObject
{
    long mx, my;
    int mwidth, mheight;
public:
    virtual bool CheckCollision();
    GameObject();
};

#endif // GAMEOBJECT_H
