#ifndef LOTBASE_H
#define LOTBASE_H

#include <QEnableSharedFromThis>
#include <QVariant>

template <typename To, typename From>
QList<To> qlist_cast(const QList<From> &from)
{
    QList<To> to;

    QListIterator<From> iter(from);
    while (iter.hasNext()) {
        to << dynamic_cast<To>(iter.next());
    }

    return to;
}

template<bool>
struct ToVariantImpl;

template <>
struct ToVariantImpl<0> {
    template <typename T>
    static T toType(const QVariant& value) {
        return qvariant_cast<T>(value);
    }
};

template <>
struct ToVariantImpl<1> {
    template <typename T>
    static T toType(const QVariant& value) {
        return T::fromVariant(value);
    }
};

template <typename T>
T variantToType(const QVariant& value)
{
    return ToVariantImpl<QTypeInfo<T>::isComplex>::template toType<T>(value);
}

template <typename T>
QList<T> listFromVariant(const QVariant &variant)
{
    QList<T> lst;

    foreach (const QVariant &entry, variant.toList())
    {
        lst.append(variantToType<T>(entry));
    }

    return lst;
}

class LOTBase : public QEnableSharedFromThis<LOTBase>
{
public:
    LOTBase();
    virtual ~LOTBase();
};

class LOTShapeItem : public LOTBase
{
public:
};

#endif // LOTBASE_H
