#include "metaobject.h"

namespace Qx::prv
{

std::set<MetaObject::SizeKey> MetaObject::sizeSet = {};
std::vector<MetaRecord>     MetaObject::records = {};
x_count MetaObject::itemCounter = 0;

}
