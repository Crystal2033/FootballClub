#pragma once
#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "PatternObserver/subject.h"
#include "Enums/Enums.h"


class BaseNote : public QWidget, public InterfaceSubject {
    Q_OBJECT
public:
    BaseNote(QWidget *parent = nullptr);
    void setNoteViewType(const NOTE_VIEW_TYPE type);
    NOTE_VIEW_TYPE getNoteViewTytpe() const;
    virtual ~BaseNote();
    void addObserver(InterfaceObserver* observer) override;
    void removeObserver(InterfaceObserver* observer) override;
    void removeObservers() override;


protected:
    QList<InterfaceObserver*> observers;
    void notifyObservers(const REQUEST_TYPE requestStatus, BaseNote* note = nullptr) override;
    unsigned recordId;
    QBoxLayout* globalLay = nullptr;
    QPushButton* modifyButton = nullptr;
    QPushButton* saveChangesButton = nullptr;
    QPushButton* cancelSaving = nullptr;
    NOTE_VIEW_TYPE noteViewType = READ;
    virtual void extend() = 0;
    virtual void modifyNoteView() = 0;
    void setSaveCancelButtonsVisability(const bool visability);
};


