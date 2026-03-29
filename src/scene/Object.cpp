#include "Object.h"

// Definition and initialization of static member
int Object::objectCount = 0;


int Object::GetObjectId()
{
    return this->objectId;
}
