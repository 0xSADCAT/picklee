#pragma once

#include <QString>
#include <list>


/// Конвертор данных в строку
class Convertor
{
public:
    Convertor() = default;
    virtual ~Convertor() = default;

    /**
     * @brief Начать именованный блок данных
     * @param Имя блока данных
     */
    virtual void beginBlock(const QString& blockName) = 0;

    /**
     * @brief Закончить именованный блок данных
     * @param Имя блока данных
     */
    virtual void endBlock(const QString& blockName) = 0;

    /**
     * @brief Добавить поле с данными
     * @param Название поля данных
     * @param Данные
     */
    virtual void field(const QString& fieldName, const QString& fieldData) = 0;

    /**
     * @brief Собрать буфер в результирующею строку
     * @return Результирующая строка
     */
    virtual QString result() = 0;

    /**
     * @brief Очистить буфер
     */
    virtual void clear() = 0;
};


/// Конвертор данных в SJON
class JsonConvertor : public Convertor
{
public:
    JsonConvertor(const QString indentType = "    ");

    virtual void beginBlock(const QString& blockName) override;
    virtual void endBlock(const QString&) override;

    virtual void field(const QString& fieldName, const QString& fieldData) override;

    virtual QString result() override;
    virtual void clear() override;

private:
    int _indent = 1;
    QString _indentType;

    std::list<QString> _buffer;

    void addIndent();
};
