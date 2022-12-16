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


protected:
    QList<InterfaceObserver*> observers;
    std::map<TextField**, QString> valuesBeforeAction;
    void notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) override;
    unsigned recordId = 0;
    QBoxLayout* globalLay = nullptr;
    QPushButton* modifyButton = nullptr;
    QPushButton* saveChangesButton = nullptr;
    QPushButton* cancelSaving = nullptr;
    QPushButton* deleteNoteButton = nullptr;
    NOTE_VIEW_TYPE noteViewType = READ;
    virtual void extend() = 0;
    virtual void modifyNoteView() = 0;
    virtual void saveDataBeforeAction() = 0;
    void setSaveCancelButtonsVisability(const bool visability);

    void fromDataWidgetToLabel(TextField*& textField, const QString& value);
    void fromLabelToDateTimeText(TextField*& textField);
    void fromLabelToComboList(QSqlQuery& query, const QString columnName,
                              TextField*& textField);
    void fromLabelToLineEdit(TextField*& textField, QValidator* validator=nullptr);
};


