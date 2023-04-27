#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

class Exceptions
{
    std::string err_text;
public:
    explicit Exceptions(std::string str) {err_text = std::move(str);}   //ключевое слово explicit сообщает компилятору что указанное преобразование
                                                                        //нельзя использовать для выполнения неявных преобразований

    //The friend declaration appears in a class body and grants a function or another class access
    //to private and protected members of the class where the friend declaration appears.

    friend std::ostream& operator << (std::ostream &os, Exceptions &exc);
    //Чтобы cout принимал объект Date после оператора вставки, перегрузите оператор вставки для распознавания объектов
    //ostream слева и Date справа. Перегруженная функция оператора << затем должна быть объявлена как друг класса Date,
    //он может получить доступ к личных данных в пределах Date объекта.
    //Данные из Exceptions попадают в поток вывода
};

#endif // EXCEPTIONS_H
