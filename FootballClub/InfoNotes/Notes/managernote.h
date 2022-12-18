#ifndef MANAGERNOTE_H
#define MANAGERNOTE_H

#include "BaseNote.h"

class ManagerNote : public BaseNote
{
public:
    ManagerNote(QSqlQuery* query = nullptr, QWidget* parent = nullptr);


private:
    QLabel* titleLbl;
    QLabel* nameLbl;
    QLabel* teamTypeLbl;
    QLabel* countryLbl;
    QLabel* birthdayLbl;
    QLabel* inClubSinceLbl;
    QLabel* contractEndslbl;
    QLabel* salarylbl;

    QBoxLayout* titleInfoLay;
    QBoxLayout* titleLay;

    QBoxLayout* teamTypeInfoLay;
    QBoxLayout* teamTypeLay;

    QBoxLayout* personInfoLay;
    QBoxLayout* personNameLay;
    QBoxLayout* personCountryLay;
    QBoxLayout* personBirthdayLay;

    QBoxLayout* clubInfoLay;
    QBoxLayout* clubInfoSinceLay;
    QBoxLayout* clubInfoLeftAtLay;
    QBoxLayout* clubInfoSalary;

    TextField* title;
    TextField* teamType;
    TextField* name;
    TextField* country;
    TextField* birthdayDate;
    TextField* sinceInClub;
    TextField* contractEndsAt;
    TextField* salary;


    void setNoteViewType(const NOTE_VIEW_TYPE type) override;
    void extend() override;
    void setStyles() override;
    QString deleteNotNeedSymbolsInSalaryValue(QString salaryValue) const;

    void saveDataBeforeAction() override;
    void setAllDataOnLayout() override;
    void insertFieldsInMap() override;
    void transformNoteInLabelView() override;

    void setTeamTypesComboList(QSqlQuery& query) override;
    void setManagerTitleComboList(QSqlQuery& query) override;
    void setCountryComboList(QSqlQuery& query) override;

private slots:
    void modifyNoteView() override;
    void onSaveChangesClicked();
    void onCancelModifyingClicked();
    void onDeleteButtonClicked();
};

#endif // MANAGERNOTE_H
