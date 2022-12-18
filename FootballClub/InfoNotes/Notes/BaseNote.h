#pragma once
#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "InfoNotes/DataWidgets/textfield.h"
#include "PatternObserver/subject.h"
#include "Enums/Enums.h"
#include <QtSql>


class BaseNote : public QWidget, public InterfaceSubject {
    Q_OBJECT
public:
    BaseNote(QWidget *parent = nullptr);
    virtual void setNoteViewType(const NOTE_VIEW_TYPE type) = 0;
    NOTE_VIEW_TYPE getNoteViewTytpe() const;
    virtual ~BaseNote();
    void addObserver(InterfaceObserver* observer) override;
    void removeObserver(InterfaceObserver* observer) override;
    void removeObservers() override;
    void setRecordId(const unsigned value);
    unsigned getRecordId() const;
    std::map<QString, TextField*> getFieldsMap() const;

protected:
    std::map<QString, TextField*> fieldsMap;
    QList<InterfaceObserver*> observers;
    std::map<TextField**, QString> valuesBeforeAction;
    void notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) override;
    unsigned recordId = 0;
    QBoxLayout* globalLay = nullptr;
    QBoxLayout* modifyButtonsLay = nullptr;
    QBoxLayout* deleteNoteButtonLay = nullptr;
    QPushButton* modifyButton = nullptr;
    QPushButton* saveChangesButton = nullptr;
    QPushButton* cancelSaving = nullptr;
    QPushButton* deleteNoteButton = nullptr;
    NOTE_VIEW_TYPE noteViewType = READ;
    virtual void extend() = 0;
    virtual void setStyles() = 0;
    virtual void modifyNoteView() = 0;
    virtual void saveDataBeforeAction() = 0;
    virtual void setAllDataOnLayout() = 0;
    virtual void insertFieldsInMap() = 0;
    virtual void setSavedDataBack();
    void setSaveCancelButtonsVisability(const bool visability);

    virtual void transformNoteInLabelView() = 0;
    void fromDataWidgetToLabel(TextField*& textField, const QString& value);
    void fromLabelToDateTimeText(TextField*& textField);
    void fromLabelToComboList(QSqlQuery& query, const QString columnName,
                              TextField*& textField);
    void fromLabelToLineEdit(TextField*& textField, QValidator* validator=nullptr);

    virtual void setTournamentComboList(QSqlQuery& query);
    virtual void setStagesComboList(QSqlQuery& query);
    virtual void setTeamTypesComboList(QSqlQuery& query);
    virtual void setClubsComboList(QSqlQuery& query);
    virtual void setStadiumsComboList(QSqlQuery& query);
    virtual void setCountryComboList(QSqlQuery& query);
    virtual void setPlayerPositionComboList(QSqlQuery& query);
    friend class WindowManager;
};


