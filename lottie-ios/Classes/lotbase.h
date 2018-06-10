#ifndef LOTBASE_H
#define LOTBASE_H

#include <QEnableSharedFromThis>

class LOTBase : public QEnableSharedFromThis<LOTBase>
{
public:
    LOTBase();
    virtual ~LOTBase();
};

#endif // LOTBASE_H
