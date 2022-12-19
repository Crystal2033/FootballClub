/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.12.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "BaseNote.h"
#include "InfoNotes/DataWidgets/label.h"
#include "InfoNotes/DataWidgets/combobox.h"
#include <QValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include "InfoNotes/DataWidgets/lineedit.h"
#include "InfoNotes/DataWidgets/datetimetext.h"
#include <QMessageBox>

BaseNote::BaseNote(QWidget *parent)
    :QWidget(parent)
{
    modifyButton = new QPushButton;

    modifyButton->setIcon(QIcon(":/pictures/Pics/modifyData.png"));
    modifyButton->setFixedSize(75, 75);
    modifyButton->setIconSize(modifyButton->size());
    modifyButton->setStyleSheet("QPushButton{"
                                "border: none;"
                                "border-radius:10px;"
                                "}"
                                "QPushButton:hover{"
                                "background-color: #212e3c;"
                                "}"
                                ""
                                "");

    saveChangesButton = new QPushButton("Save");
    saveChangesButton->setStyleSheet("background-color: darkgreen;"
                                     "color:white;"
                                     "font-size: 20px;"
                                     "font-weight: bold;"
                                     "");

    cancelSaving = new QPushButton("Cancel");
    cancelSaving->setStyleSheet("background-color: darkred;"
                                "color:white;"
                                "font-size: 20px;"
                                "font-weight: bold;"
                                "");

    deleteNoteButton = new QPushButton();
    deleteNoteButton->setIcon(QIcon(":/pictures/Pics/closeIcon.png"));
    deleteNoteButton->setFixedSize(50, 50);
    deleteNoteButton->setIconSize(deleteNoteButton->size());
    deleteNoteButton->setStyleSheet("QPushButton{"
                                    "border: none;"
                                    "border-radius:20px;"
                                    "}"
                                    "QPushButton:hover{"
                                    "background-color: #212e3c;"
                                    "}"
                                    ""
                                    "");

//    deleteNoteButton->setStyleSheet("background-color: #D54B7F;"
//                                    "color:white;"
//                                    "font-size: 15px;"
//                                    "font-weight: bold;"
//                                    "");
}

void BaseNote::setNoteViewType(const NOTE_VIEW_TYPE type)
{
    noteViewType = type;
}

NOTE_VIEW_TYPE BaseNote::getNoteViewTytpe() const
{
    return noteViewType;
}

BaseNote::~BaseNote()
{

}


void BaseNote::addObserver(InterfaceObserver *observer)
{
    this->observers.append(observer);
}

void BaseNote::removeObserver(InterfaceObserver *observer)
{
    QList<InterfaceObserver*>::ConstIterator it = observers.constBegin();
    for (; it != observers.constEnd(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void BaseNote::removeObservers()
{
    observers.clear();
}

void BaseNote::setRecordId(const unsigned value)
{
    recordId = value;
    qInfo() << "New ID: " << recordId;
}

unsigned BaseNote::getRecordId() const
{
    return recordId;
}

std::map<QString, TextField*> BaseNote::getFieldsMap() const{
    return fieldsMap;
}

std::map<TextField **, QString> BaseNote::getValuesBeforeAction() const
{
    return valuesBeforeAction;
}

void BaseNote::setIsLastRequestSucess(const bool isSuccess)
{
    this->isLastRequestSuccess = isSuccess;
}

bool BaseNote::getIsLastRequestSuccess() const
{
    return isLastRequestSuccess;
}

REQUEST_TYPE BaseNote::getLastRequestType() const
{
    return lastRequestType;
}

void BaseNote::setLastRequestType(const REQUEST_TYPE newType)
{
    lastRequestType = newType;
}

void BaseNote::setDeleteButtonVisability(const bool isVisible)
{
    deleteNoteButton->setVisible(isVisible);
}


void BaseNote::notifyObservers(const REQUEST_TYPE requestStatus, BaseNote *note)
{
    for (auto obs : observers) {
        obs->updateByObserver(requestStatus, note);
    }
}

void BaseNote::setSavedDataBack()
{
    if(!valuesBeforeAction.empty()){
        for(auto textField : valuesBeforeAction){
            (*textField.first)->setText(textField.second);
        }
    }
}

void BaseNote::setSaveCancelButtonsVisability(const bool visability)
{
    cancelSaving->setVisible(visability);
    saveChangesButton->setVisible(visability);
}

void BaseNote::fromDataWidgetToLabel(TextField *&textField, const QString& value)
{
    delete textField;
    textField = new Label(value);
}

void BaseNote::fromLabelToDateTimeText(TextField *&textField)
{
    Label* lbl = (Label*)textField;
    QString lastValue = lbl->getText();
    delete textField;
    textField= new DateTimeText(lastValue);
}

void BaseNote::fromLabelToComboList(QSqlQuery &query, const QString columnName,
                                    TextField *&textField)
{
    QSqlRecord record = query.record();
    std::map<QString, unsigned> valueAndIdMap;
    while(query.next()){
        valueAndIdMap.insert(std::make_pair(query.value(record.indexOf(columnName)).toString(),
                                            query.value(record.indexOf("id")).toInt()));
    }

    Label* lbl = (Label*) textField;

    QString lastValue = lbl->getText();
    delete textField;

    textField = new ComboBox(valueAndIdMap);
    ComboBox* temp = (ComboBox*) textField;

    temp->setCurrentItem(lastValue);
}


void BaseNote::fromLabelToLineEdit(TextField *&textField, QValidator* validator)
{
    Label* lbl = (Label*)textField;
    QString lastValue = lbl->getText();
    delete textField;
    textField= new LineEdit(lastValue, validator);
}

void BaseNote::setTournamentComboList(QSqlQuery &query)
{Q_UNUSED(query);}

void BaseNote::setManagerTitleComboList(QSqlQuery &query)
{Q_UNUSED(query);}

void BaseNote::setStagesComboList(QSqlQuery &query)
{Q_UNUSED(query);}

void BaseNote::setTeamTypesComboList(QSqlQuery &query)
{Q_UNUSED(query);}

void BaseNote::setClubsComboList(QSqlQuery &query)
{Q_UNUSED(query);}

void BaseNote::setStadiumsComboList(QSqlQuery &query)
{Q_UNUSED(query);}

void BaseNote::setCountryComboList(QSqlQuery &query)
{Q_UNUSED(query);}

void BaseNote::setPlayerPositionComboList(QSqlQuery &query)
{Q_UNUSED(query);}

