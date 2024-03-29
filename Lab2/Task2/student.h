#ifndef STUDENT_H
#define STUDENT_H

#include <QString>


class Student {
private:
    QString name;
    QString speciality;
    QString group;
    int oaip_mark;
    int ma_mark;
    int agila_mark;
    int ml_mark;
    int hist_mark;

public:
    Student(QString, QString, QString, int, int, int, int, int);
    Student();
    bool isNameCorrect();
    bool isSpecCorrect();
    bool isGroupCorrect();
    double averageMark();
    QString getInitials();

    QString getName();
    QString getSpec();
    QString getGroup();
    int getOaip();
    int getMa();
    int getAgila();
    int getMl();
    int getHist();

};

#endif // STUDENT_H
