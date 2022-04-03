#pragma once

#include "Product.hpp"

#include <QList>
#include <QString>


class Warehouse
{
public:
    Warehouse(int priority, const QString& description);

    int priority() const;
    void setPriority(int newPriority);

    const QString& description() const;
    void setDescription(const QString& newDescription);

    /// Состав склада (только для чтения)
    const QList<ProductCount>& products() const;

    /**
     * @brief Поставить продукт на склад
     * @param product Продукт для поставки
     *
     * @note Условие: product.count() > 0
     */
    void deliver(const ProductCount& product);

    /**
     * @brief Взять продукт со склада
     * @param product Продукт
     * @return false если на складе недостаточное количество
     *
     * @note Условие: product.count() > 0
     */
    bool fetch(const ProductCount& product);

    /**
     * @brief Можно ли взять продукт со склада
     * @param product Продукт
     * @return true если количество на складе позволяет
     *
     * @note Условие: product.count() > 0
     */
    bool canFetch(const ProductCount& product) const;

private:
    int _priority;                 ///< Приоритет
    QString _description;          ///< Описание
    QList<ProductCount> _products; ///< Состав склада
};

