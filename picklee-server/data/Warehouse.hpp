#pragma once

#include "Product.hpp"

#include <QString>
#include <vector>


class Convertor;


class Warehouse
{
public:
    static inline const QString className = "Warehouse";

    Warehouse(int id, int priority, const QString& description);

    int priority() const;
    void setPriority(int newPriority);

    const QString& description() const;
    void setDescription(const QString& newDescription);

    /// Состав склада (только для чтения)
    const std::vector<ProductCount>& products() const;

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

    int id() const;

    void convert(Convertor& conv);

private:
    int _id;                             ///< Идентификатор
    int _priority;                       ///< Приоритет
    QString _description;                ///< Описание
    std::vector<ProductCount> _products; ///< Состав склада
};
