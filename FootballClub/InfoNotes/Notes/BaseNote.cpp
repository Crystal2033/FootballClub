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
    modifyButton->setFixedSize(75, 55);
    modifyButton->setIconSize(QSize(0.75 * modifyButton->size().width(), 0.75 * modifyButton->size().height()));
    modifyButton->setIcon(QIcon(":/pictures/Pics/modifyData.png"));
    modifyButton->setStyleSheet("background-color: grey;"
                                );

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

    deleteNoteButton = new QPushButton("X");
    deleteNoteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    deleteNoteButton->setStyleSheet("background-color: #D54B7F;"
                                    "color:white;"
                                    "font-size: 15px;"
                                    "font-weight: bold;"
                                    "");
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


void BaseNote::notifyObservers(const REQUEST_TYPE requestStatus, BaseNote *note)
{
    for (auto obs : observers) {
        obs->updateByObserver(requestStatus, note);
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
        //stringList << query.value(record.indexOf(columnName)).toString();
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

